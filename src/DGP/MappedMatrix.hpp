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

#ifndef __DGP_MappedMatrix_hpp__
#define __DGP_MappedMatrix_hpp__

#include "AddressableMatrix.hpp"
#include "IteratableMatrix.hpp"
#include "ResizableMatrix.hpp"
#include <map>
#include <utility>

namespace DGP {

/**
 * Interface for a sparse 2D matrix with elements that may be directly accessed via a (row, column) pair. The type T should be a
 * well-ordered field, pipeable to a <code>std::ostream</code>. The matrix is stored as a collection of "set" elements, which
 * are stored in a map that maps (row, column) pairs to values. All other elements are "unset" and assumed to be zero. Note that
 * set elements may have zero values as well. The map type MapT should have the interface of
 * <code>std::map<IndexPair, T></code>, but need not have any ordering of keys.
 */
template < typename T, typename MapT = std::map< std::pair<long, long>, T > >
class /* DGP_API */ MappedMatrix : public AddressableMatrix<T>, public ResizableMatrix<T>
{
  public:
    typedef MapT Map;  ///< The underlying map type used to store elements.
    typedef typename MapT::key_type IndexPair;  ///< A (row, column) index pair.
    typedef typename MapT::value_type Entry;  ///< An entry in the matrix, mapping a (row, column) pair to a value.
    typedef typename MapT::iterator Iterator;  ///< Iterator over elements.
    typedef typename MapT::const_iterator ConstIterator;  ///< Const iterator over elements (hides AddressableMatrix::Iterator).

    /** Constructor. */
    MappedMatrix(long num_rows = 0, long num_cols = 0) : nrows(0), ncols(0)
    {
      resize(num_rows, num_cols);
    }

    long numRows() const { return nrows; }
    long numColumns() const { return ncols; }

    /** Get the number of set (logically non-zero) elements in the matrix. */
    long numSetElements() const { return (long)m.size(); }

    /** Check if the matrix is null, i.e. has no set elements. */
    bool isNull() const
    {
      return m.empty();
    }

    void makeZero() { m.clear(); }

    void resize(long num_rows, long num_cols)
    {
      alwaysAssertM(num_rows >= 0 && num_cols >= 0, "MappedMatrix: Dimensions cannot be negative");

      if (nrows != num_rows || ncols != num_cols)
      {
        nrows = num_rows;
        ncols = num_cols;
        m.clear();
      }
    }

    /** Check if an element has an explicitly set value. */
    bool isSet(long row, long col) const
    {
      return m.find(IndexPair(row, col)) != m.end();
    }

    /** Element access. Use this whenever possible to avoid the virtual function overhead of get(). */
    T const & operator()(long row, long col) const
    {
      ConstIterator existing = m.find(IndexPair(row, col));
      if (existing == m.end())
        return ZERO;
      else
        return existing->second;
    }

    T const & get(long row, long col) const { return (*this)(row, col); }

    /**
     * {@inheritDoc}
     *
     * For mapped matrices, this function will always add the (row, col) element to the matrix if it doesn't yet exist, setting
     * it to an initial value of zero. This may destroy the sparsity of the matrix.
     */
    T & getMutable(long row, long col)
    {
      // See documentation of std::map::insert()
      return m.insert(typename Map::value_type(IndexPair(row, col), static_cast<T>(0))).first->second;
    }

    void set(long row, long col, T const & value)
    {
      m[IndexPair(row, col)] = value;
    }

    /** Unset an element by removing it from the underlying map. Its value is now identically zero. */
    void unset(long row, long col) { m.erase(IndexPair(row, col)); }

    /** Get an iterator to the first set element in the matrix. The iterator will skip over all unset (zero) elements. */
    ConstIterator begin() const { return m.begin(); }

    /** Get an iterator to the first set element in the matrix. The iterator will skip over all unset (zero) elements. */
    Iterator begin() { return m.begin(); }

    /** Get an iterator to the end of the matrix. */
    ConstIterator end() const { return m.end(); }

    /** Get an iterator to the end of the matrix. */
    Iterator end() { return m.end(); }

    T const & min() const
    {
      ConstIterator min_i = m.end();
      for (ConstIterator mi = m.begin(); mi != m.end(); ++mi)
        if (min_i == m.end() || mi->second < min_i->second)
          min_i = mi;

      return min_i == m.end() ? ZERO : min_i->second;
    }

    T const & max() const
    {
      ConstIterator max_i = m.end();
      for (ConstIterator mi = m.begin(); mi != m.end(); ++mi)
        if (max_i == m.end() || mi->second > max_i->second)
          max_i = mi;

      return max_i == m.end() ? ZERO : max_i->second;
    }

    std::string toString() const
    {
      std::ostringstream oss;
      oss << "[";

      for (ConstIterator mi = m.begin(); mi != m.end(); ++mi)
      {
        if (mi != m.begin()) oss << ", ";
        oss << '(' << mi->first.first << ", " << mi->first.second << ", " << mi->second << ')';
      }

      oss << ']';
      return oss.str();
    }

  private:
    static T const ZERO;  ///< Returned by accessors for unset elements.

    long nrows;  ///< Number of rows in the matrix.
    long ncols;  ///< Number of columns in the matrix.
    MapT m;  ///< The map storing set elements of the matrix.

}; // class MappedMatrix

template <typename T, typename MapT> T const MappedMatrix<T, MapT>::ZERO = static_cast<T>(0);

} // namespace DGP

#endif
