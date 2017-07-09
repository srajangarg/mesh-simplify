//============================================================================
//
// DGP: Digital Geometry Processing toolkit
// Copyright (C) 2016, Siddhartha Chaudhuri
//
// This software is covered by a BSD license. Portions derived from other
// works are covered by their respective licenses. For full licensing
// information see the LICENSE.txt file.
//
//============================================================================

#ifndef __DGP_AddressableMatrix_hpp__
#define __DGP_AddressableMatrix_hpp__

#include "IteratableMatrix.hpp"

namespace DGP {

/**
 * Interface for a 2D matrix with elements that may be directly accessed via a (row, column) pair. The type T should be a
 * well-ordered field, pipeable to a <code>std::ostream</code>.
 */
template <typename T>
class /* DGP_API */ AddressableMatrix : public virtual IteratableMatrix<T>
{
  public:
    typedef std::pair<long, long> IndexPair;  ///< A (row, column) index pair.
    typedef std::pair<IndexPair, T> Entry;    ///< An entry in the matrix, mapping a (row, column) pair to a value.

    /** Generic read-only iterator for an addressable matrix. */
    class ConstIterator
    {
      public:
        /** Constructor. */
        ConstIterator(AddressableMatrix const & m_, long r = 0, long c = 0)
        : m(m_), nrows(m_.numRows()), ncols(m_.numColumns()), entry(IndexPair(r, c), 0)
        {}

        /** Get the row of the current element. */
        long getRow() const { return entry.first.first; }

        /** Get the column of the current element. */
        long getColumn() const { return entry.first.second; }

        /** Dereference to the current element. */
        Entry const & operator*() const
        {
          entry.second = m.get(entry.first.first, entry.first.second);
          return entry;
        }

        /** Arrow operator for dereferencing. */
        Entry const * operator->() const
        {
          return &(this->operator*());
        }

        /** Pre-increment. */
        ConstIterator & operator++()
        {
          if (++entry.first.second >= ncols)
          {
            ++entry.first.first;
            entry.first.second = 0;
          }

          return *this;
        }

        /** Post-increment. */
        ConstIterator operator++(int)
        {
          ConstIterator old = *this;
          this->operator++();
          return old;
        }

        /** Test for equality. */
        bool operator==(ConstIterator const & rhs) const
        {
          return !(*this != rhs);
        }

        /** Test for inequality. */
        bool operator!=(ConstIterator const & rhs) const
        {
          debugAssertM(&m == &rhs.m, "Matrix: Comparing iterators from different matrices for equality");
          return (entry.first != rhs.entry.first);
        }

      private:
        AddressableMatrix const & m;
        long nrows, ncols;
        mutable Entry entry;

    }; // class ConstIterator

    /** Get an iterator pointing to the beginning of the matrix. */
    ConstIterator begin() const { return ConstIterator(*this, 0, 0); }

    /** Get an iterator pointing to the end of the matrix. */
    ConstIterator end() const { return ConstIterator(*this, (this->numColumns() > 0 ? this->numRows() : 0), 0); }

    /**
     * Get element. Most derived classes define operator() to access an element quicker, without the virtual function overhead.
     * Use this function only in generic algorithms that need polymorphic access to matrices without using templates.
     */
    virtual T const & get(long row, long col) const = 0;

    /**
     * Get an element that can be directly modified. Most derived classes define operator() to access an element quicker,
     * without the virtual function overhead. Use this function only in generic algorithms that need polymorphic access to
     * matrices without using templates.
     */
    virtual T & getMutable(long row, long col) = 0;

    /**
     * Set element. Most derived classes define operator() to access an element quicker, without the virtual function overhead.
     * Use this function only in generic algorithms that need polymorphic access to matrices without using templates.
     */
    virtual void set(long row, long col, T const & value) = 0;

    void makeZero() { fill(static_cast<T>(0)); }

    /** Set all elements of the matrix to a given value. */
    virtual void fill(T const & value)
    {
      long nr = this->numRows(), nc = this->numColumns();

      for (long r = 0; r < nr; ++r)
        for (long c = 0; c < nc; ++c)
          set(r, c, value);
    }

    /** Get the minimum element (according to signed comparison) in the matrix. */
    virtual T const & min() const
    {
      long nr = this->numRows(), nc = this->numColumns();
      T const * m = NULL;

      for (long r = 0; r < nr; ++r)
        for (long c = 0; c < nc; ++c)
        {
          T const & e = get(r, c);
          if (!m || e < *m)
            m = &e;
        }

      debugAssertM(m, "AddressableMatrix: No minimum element found");
      return *m;
    }

    /** Get the maximum element (according to signed comparison) in the matrix. */
    virtual T const & max() const
    {
      long nr = this->numRows(), nc = this->numColumns();
      T const * m = NULL;

      for (long r = 0; r < nr; ++r)
        for (long c = 0; c < nc; ++c)
        {
          T const & e = get(r, c);
          if (!m || e > *m)
            m = &e;
        }

      debugAssertM(m, "AddressableMatrix: No maximum element found");
      return *m;
    }

    /** Get a row of the matrix. \a values must be preallocated with numColumns() elements. */
    virtual void getRow(long row, T * values) const
    {
      long nc = this->numColumns();
      for (long c = 0; c < nc; ++c)
        values[c] = get(row, c);
    }

    /** Set a row of the matrix. \a values must contain numColumns() elements. */
    virtual void setRow(long row, T const * values)
    {
      long nc = this->numColumns();
      for (long c = 0; c < nc; ++c)
        set(row, c, values[c]);
    }

    /** Get a column of the matrix. \a values must be preallocated with numRows() elements. */
    virtual void getColumn(long col, T * values) const
    {
      long nr = this->numRows();
      for (long r = 0; r < nr; ++r)
        values[r] = get(r, col);
    }

    /** Set a column of the matrix. \a values must contain numRows() elements. */
    virtual void setColumn(long col, T const * values)
    {
      long nr = this->numRows();
      for (long r = 0; r < nr; ++r)
        set(r, col, values[r]);
    }

    /** Get a string representing the matrix. */
    virtual std::string toString() const
    {
      std::ostringstream oss;
      oss << '[';

      long nr = this->numRows(), nc = this->numColumns();
      for (long r = 0; r < nr; ++r)
      {
        for (long c = 0; c < nc; ++c)
        {
          oss << get(r, c);
          if (c < nc - 1) oss << ", ";
        }

        if (r < nr - 1) oss << "; ";
      }

      oss << ']';
      return oss.str();
    }

    /**
     * Copy the contents of the matrix to another addressable matrix. The matrices must have the same dimensions, else an
     * assertion failure is generated.
     */
    template <typename U> void copyTo(AddressableMatrix<U> & dst) const
    {
      long nr = this->numRows(), nc = this->numColumns();
      alwaysAssertM(nr == dst.numRows() && nc == dst.numColumns(),
                    "AddressableMatrix: Copy destination has different dimensions");

      for (long r = 0; r < nr; ++r)
        for (long c = 0; c < nc; ++c)
          dst.set(r, c, get(r, c));
    }

}; // class AddressableMatrix

/** Pipe a textual representation of an addressable matrix to a <code>std::ostream</code>. */
template <typename T>
std::ostream &
operator<<(std::ostream & os, AddressableMatrix<T> const & m)
{
  return os << m.toString();
}

} // namespace DGP

#endif
