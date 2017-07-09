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

#ifndef __DGP_CompressedSparseMatrix_hpp__
#define __DGP_CompressedSparseMatrix_hpp__

#include "Common.hpp"
#include "AddressableMatrix.hpp"
#include "IteratableMatrix.hpp"
#include "ResizableMatrix.hpp"
#include "FastCopy.hpp"
#include <type_traits>
#include <map>

namespace DGP {

namespace CompressedSparseMatrixInternal {

struct Base {};

} // namespace CompressedSparseMatrixInternal

/**
 * A matrix stored in the Compressed Row/Column format (http://www.cs.utk.edu/~dongarra/etemplates/node373.html). Significant
 * space savings are possible if the matrix is sparse, but the representation is not amenable to most matrix operations, except
 * multiplication which is efficient.
 *
 * This class has hidden constructors and cannot be used directly. Instead use the CompressedRowMatrix and
 * CompressedColumnMatrix derivatives.
 *
 * <b>Implementation-specific:</b> The subscripts 1 and 2 stand for row and column respectively if the matrix is interpreted as
 * being in row-major format, and column and row if the matrix is interpreted as being in column-major format. This <b>NOT</b>
 * the same as the Boost.uBLAS convention, where 1 always stands for rows and 2 for columns.
 */
template <typename T, MatrixLayout::Value L, typename Index2DT = int, typename Index1DT = long>
class /* DGP_API */ CompressedSparseMatrix : public virtual IteratableMatrix<T>, public CompressedSparseMatrixInternal::Base
{
  public:
    static MatrixLayout::Value const Layout = L;  ///< The layout of the matrix (row-major or column-major).
    typedef Index2DT  Index2D;                    ///< The type of 2D element indices.
    typedef Index1DT  Index1D;                    ///< The type of 1D (flat) element indices.

    typedef std::pair<long, long> IndexPair;      ///< A (row, column) index pair.
    typedef std::pair<IndexPair, T> Entry;        ///< An entry in the matrix, mapping a (row, column) pair to a value.

    /** Read-only iterator for a compressed sparse matrix. */
    class ConstIterator
    {
      public:
        /** Constructor. */
        ConstIterator(CompressedSparseMatrix const & m_,
                      long i1_ = 0,  // index of current element in indices1
                      long i2_ = 0)  // index of current element in indices2/values
        : m(m_), i1(i1_), i2(i2_)
        {}

        /** Get the row of the current element. */
        long getRow() const { return (L == MatrixLayout::ROW_MAJOR ? (long)i1 : (long)m.indices2[i2]); }

        /** Get the column of the current element. */
        long getColumn() const { return (L == MatrixLayout::COLUMN_MAJOR ? (long)i1 : (long)m.indices2[i2]); }

        /** Get the value of the current element. */
        Entry const & operator*() const
        {
          if (L == MatrixLayout::ROW_MAJOR)
            entry = Entry(IndexPair((long)i1, (long)m.indices2[i2]), m.values[i2]);
          else
            entry = Entry(IndexPair((long)m.indices2[i2], (long)i1), m.values[i2]);

          return entry;
        }

        Entry const * operator->() const
        {
          return &(this->operator*());
        }

        /** Pre-increment. */
        ConstIterator & operator++()
        {
          ++i2;
          while ((long)i1 + 1 < m.size1 && m.indices1[i1 + 1] <= (Index1D)i2)
            ++i1;

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
          debugAssertM(&m == &rhs.m, "CompressedSparseMatrix: Comparing iterators from different matrices for equality");
          return (i1 != rhs.i1 || i2 != rhs.i2);
        }

      private:
        CompressedSparseMatrix const & m;
        size_t i1, i2;
        mutable Entry entry;

    }; // class ConstIterator

    // Since this class can't be directly instantiated (protected constructors), we might as well make these public, to avoid
    // access issues for some templated constructors
    long                  size1;
    long                  size2;
    std::vector<Index1D>  indices1;
    std::vector<Index2D>  indices2;
    std::vector<T>        values;

    /** Assignment operator. */
    CompressedSparseMatrix & operator=(CompressedSparseMatrix const & src)
    {
      size1 = src.size1;
      size2 = src.size2;
      indices1 = src.indices1;
      indices2 = src.indices2;
      values = src.values;

      return *this;
    }

    /** Get an iterator pointing to the beginning of the matrix. */
    ConstIterator begin() const
    {
      // Find the first non-zero row/column
      size_t i1 = 0;
      while ((long)i1 + 1 < size1 && indices1[i1 + 1] <= 0)
        ++i1;

      return ConstIterator(*this, i1, 0);
    }

    /** Get an iterator pointing to the end of the matrix. */
    ConstIterator end() const { return ConstIterator(*this, (size1 > 0 ? size1 - 1 : 0), indices2.size()); }

    /** Get the layout of the matrix (row or column major) */
    static MatrixLayout getLayout() { return L; }

    /** Get the set of logically non-zero values in the matrix. */
    std::vector<T> const & getValues() const { return values; }

    /** Get the set of logically non-zero values in the matrix. Assert isValid() if you modify this array. */
    std::vector<T> & getValues() { return values; }

    /** Get the number of logically non-zero entries in the matrix. */
    long numSetElements() const { return (long)values.size(); }

    /**
     * Check that the matrix is internally consistent. You should assert this after externally modifying the underlying arrays.
     */
    bool isValid() const
    {
      return (indices2.size() == values.size()
           && indices1.size() == (size_t)size1 + 1
           && (long)indices1[indices1.size() - 1] == numSetElements());
    }

    void makeZero()
    {
      indices2.clear();
      values.clear();
      for (typename std::vector<Index1D>::iterator i = indices1.begin(); i != indices1.end(); ++i)
        *i = static_cast<Index1D>(0);
    }

  protected:
    /**
     * Constructs a zero matrix of the specified size. If the number of columns is omitted or zero, a square matrix is created.
     */
    CompressedSparseMatrix(int size1_ = 0, int size2_ = 0)
    : size1(size1_), size2(size2_ > 0 ? size2_ : size1_), indices1((size1_ >= 0 ? (size_t)size1_ + 1 : 0), 0)
    {
      alwaysAssertM(size1_ >= 0 && size2_ >= 0, "CompressedSparseMatrix: Dimensions must be non-negative");
    }

    /** Copy constructor. */
    CompressedSparseMatrix(CompressedSparseMatrix const & src)
    : size1(src.size1), size2(src.size2), indices1(src.indices1), indices2(src.indices2), values(src.values)
    {}

    /** Initialize from another compressed sparse matrix with the same layout. */
    template <typename S, typename Index2DS, typename Index1DS> explicit
    CompressedSparseMatrix(CompressedSparseMatrix<S, L, Index1DS, Index2DS> const & src)
    : size1(0), size2(0)
    {
      size1 = src.size1;
      size2 = src.size2;

      indices1.resize(src.indices1.size());
      fastCopy(src.indices1.begin(), src.indices1.end(), indices1.begin());

      indices2.resize(src.indices2.size());
      fastCopy(src.indices2.begin(), src.indices2.end(), indices2.begin());

      values.resize(src.values.size());
      fastCopy(src.values.begin(), src.values.end(), values.begin());
    }

    /** Initialize from an iteratable matrix. */
    template <typename MatrixT> explicit
    CompressedSparseMatrix(MatrixT const & src,
                           typename std::enable_if< std::is_base_of< IteratableMatrix<typename MatrixT::Value>,
                                                                     MatrixT >::value >::type * dummy = NULL)
    {
      if (L == MatrixLayout::ROW_MAJOR)
      {
        size1 = src.numRows();
        size2 = src.numColumns();
      }
      else
      {
        size1 = src.numColumns();
        size2 = src.numRows();
      }

      typedef std::map<typename MatrixT::IndexPair, typename MatrixT::Value> EntryMap;
      EntryMap src_entries;

      for (typename MatrixT::ConstIterator si = src.begin(); si != src.end(); ++si)
      {
        if (si->second != 0)
        {
          typename MatrixT::IndexPair indices =
              (L == MatrixLayout::ROW_MAJOR ? si->first : typename MatrixT::IndexPair(si->first.second, si->first.first));

          src_entries[indices] = si->second;
        }
      }

      indices1.resize(size1 + 1);
      std::fill(indices1.begin(), indices1.end(), 0);

      indices2.resize((size_t)src_entries.size());
      values.resize((size_t)src_entries.size());

      // Now read back the values in lexicographic order
      long i, last_index1 = -1;
      size_t curr_pos = 0;
      for (typename EntryMap::const_iterator ei = src_entries.begin(); ei != src_entries.end(); ++ei, ++curr_pos)
      {
        i = (long)ei->first.first;
        if (i != last_index1)  // change of primary index since last iteration
        {
          for (long k = last_index1 + 1; k <= i; ++k)
            indices1[(size_t)k] = static_cast<Index1D>(curr_pos);

          last_index1 = i;
        }

        indices2[curr_pos] = static_cast<Index2D>(ei->first.second);
        values  [curr_pos] = static_cast<T>(ei->second);
      }

      // One beyond last position, stores number of non-zeros
      indices1[(size_t)size1] = curr_pos;
    }

    /** Resizes the matrix to the specified dimensions. All existing data is discarded and the matrix is set to zero. */
    void resize(long size1_, long size2_)
    {
      alwaysAssertM(size1_ >= 0 && size2_ >= 0, "CompressedSparseMatrix: Dimensions must be non-negative");

      size1 = size1_;
      size2 = size2_;
      indices1.resize((size_t)size1 + 1, 0);
      indices2.clear();
      values.clear();
    }

}; // class CompressedSparseMatrix

/** Row-major sparse matrix. Non-zero values are packed contiguously row-by-row. */
template <typename T, typename Index2DT = int, typename Index1DT = int>
class /* DGP_API */ CompressedRowMatrix : public CompressedSparseMatrix<T, MatrixLayout::ROW_MAJOR, Index2DT, Index1DT>,
                                          public ResizableMatrix<T>
{
  private:
    typedef CompressedSparseMatrix<T, MatrixLayout::ROW_MAJOR, Index2DT, Index1DT> BaseT;

  public:
    /**
     * Default constructor. Initializes a zero matrix of the specified size. If the number of columns is omitted or zero, a
     * square matrix is created.
     */
    CompressedRowMatrix(long num_rows = 0, long num_cols = 0) : BaseT(num_rows, num_cols) {}

    /** Copy contructor. */
    CompressedRowMatrix(CompressedRowMatrix const & src) : BaseT(src) {}

    /** Templated copy constructor. */
    template <typename MatrixT> explicit CompressedRowMatrix(MatrixT const & m) : BaseT(m) {}

    long numRows() const { return BaseT::size1; }
    long numColumns() const { return BaseT::size2; }

    void resize(long num_rows, long num_cols) { BaseT::resize(num_rows, num_cols); }

    // This is needed to avoid a Visual Studio warning about inheriting via dominance
    void makeZero() { BaseT::makeZero(); }

    /** Get the column index of each logically non-zero entry. */
    std::vector<Index2DT> const & getColumnIndices() const { return BaseT::indices2; }

    /** Get the column index of each logically non-zero entry. Assert isValid() if you modify this array. */
    std::vector<Index2DT> & getColumnIndices() { return BaseT::indices2; }

    /** Get the index (in the values array) of the starting element of each row. */
    std::vector<Index1DT> const & getRowIndices() const { return BaseT::indices1; }

    /** Get the index (in the values array) of the starting element of each row. Assert isValid() if you modify this array. */
    std::vector<Index1DT> & getRowIndices() { return BaseT::indices1; }

    /**
     * Multiply a vector \a v by this matrix (M), yielding the product \a result = M * \a v.
     *
     * @param v The vector to be multiplied, must contain numColumns() elements.
     * @param result The result vector, must be preallocated to numRows() elements.
     */
    template <typename U> void postmulVector(U const * v, U * result) const
    {
      size_t curr_pos = 0;
      U * rp = result;
      for (long row = 0; row < BaseT::size1; ++row, ++rp)
      {
        *rp = static_cast<U>(0);
        long num_elems = (long)(BaseT::indices1[row + 1] - BaseT::indices1[row]);
        for (long e = 0; e < num_elems; ++e, ++curr_pos)
        {
          Index2DT col = BaseT::indices2[curr_pos];
          *rp += static_cast<U>(BaseT::values[curr_pos] * v[col]);
        }
      }
    }

    /**
     * Utility function for efficiently computing  a matrix-vector product (w = M * v). This lets this matrix be passed directly
     * to ARPACK++. The implementation simply calls postmulVector().
     *
     * @see postmulVector()
     */
    template <typename U> void MultMv(U const * v, U * w) const { postmulVector(v, w); }

}; // class CompressedRowMatrix

/** Column-major sparse matrix. Non-zero values are packed contiguously column-by-column. */
template <typename T, typename Index2DT = int, typename Index1DT = int>
class /* DGP_API */ CompressedColumnMatrix : public CompressedSparseMatrix<T, MatrixLayout::COLUMN_MAJOR, Index2DT, Index1DT>,
                                             public ResizableMatrix<T>
{
  private:
    typedef CompressedSparseMatrix<T, MatrixLayout::COLUMN_MAJOR, Index2DT, Index1DT> BaseT;

  public:
    /**
     * Default constructor. Initializes a zero matrix of the specified size. If the number of columns is omitted or zero, a
     * square matrix is created.
     */
    CompressedColumnMatrix(long num_rows = 0, long num_cols = 0) : BaseT(num_cols, num_rows) {}

    /** Copy contructor. */
    CompressedColumnMatrix(CompressedColumnMatrix const & src) : BaseT(src) {}

    /** Templated copy constructor. */
    template <typename MatrixT> explicit CompressedColumnMatrix(MatrixT const & m) : BaseT(m) {}

    long numRows() const { return BaseT::size2; }
    long numColumns() const { return BaseT::size1; }

    void resize(long num_rows, long num_cols) { BaseT::resize(num_cols, num_rows); }

    // This is needed to avoid a Visual Studio warning about inheriting via dominance
    void makeZero() { BaseT::makeZero(); }

    /** Get the row index of each logically non-zero entry. */
    std::vector<Index2DT> const & getRowIndices() const { return BaseT::indices2; }

    /** Get the row index of each logically non-zero entry. Assert isValid() if you modify this array. */
    std::vector<Index2DT> & getRowIndices() { return BaseT::indices2; }

    /** Get the index (in the values array) of the starting element of each column. */
    std::vector<Index1DT> const & getColumnIndices() const { return BaseT::indices1; }

    /**
     * Get the index (in the values array) of the starting element of each column. Assert isValid() if you modify this array.
     */
    std::vector<Index1DT> & getColumnIndices() { return BaseT::indices1; }

    /**
     * Multiply a vector \a v by this matrix (M), yielding the product \a result = M * \a v.
     *
     * @param v The vector to be multiplied, must contain numColumns() elements.
     * @param result The result vector, must be preallocated to numRows() elements.
     */
    template <typename U> void postmulVector(U const * v, U * result) const
    {
      // Initialize output to zero
      U * r_end = result + BaseT::size2;
      for (U * rp = result; rp != r_end; ++rp) *rp = static_cast<U>(0);

      size_t curr_pos = 0;
      for (long col = 0; col < BaseT::size1; ++col)
      {
        long num_elems = (long)(BaseT::indices1[col + 1] - BaseT::indices1[col]);
        for (long e = 0; e < num_elems; ++e, ++curr_pos)
        {
          Index2DT row = BaseT::indices2[curr_pos];
          result[row] += static_cast<U>(BaseT::values[curr_pos] * v[col]);
        }
      }
    }

    /**
     * Utility function for efficiently computing  a matrix-vector product (w = M * v). This lets this matrix be passed directly
     * to ARPACK++. The implementation simply calls postmulVector().
     *
     * @see postmulVector()
     */
    template <typename U> void MultMv(U const * v, U * w) const { postmulVector(v, w); }

}; // class CompressedColumnMatrix

} // namespace DGP

#endif
