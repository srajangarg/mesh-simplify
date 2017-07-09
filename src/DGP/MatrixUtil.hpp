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

#ifndef __DGP_MatrixUtil_hpp__
#define __DGP_MatrixUtil_hpp__

#include "Common.hpp"
#include "CompressedSparseMatrix.hpp"
#include "Matrix.hpp"
#include "MatrixFormat.hpp"
#include <type_traits>

namespace DGP {

/** Utility functions for matrices. */
namespace MatrixUtil {

namespace MatrixUtilInternal {

// isSquare helper classes

// Default
template <typename MatrixT, typename Enable = void>
struct IsSquareImpl { static bool isSquare(MatrixT const & m) { return m.size1() == m.size2(); } };

// Check if a standard matrix is square
template <typename MatrixT>
struct IsSquareImpl< MatrixT, typename std::enable_if< std::is_base_of< BasicMatrix<typename MatrixT::Value>,
                                                                        MatrixT >::value >::type >
{ static bool isSquare(MatrixT const & m) { return m.isSquare(); } };

// getFormat helper classes

// Default
template <typename MatrixT, typename Enable = void>
struct GetFormatImpl { static MatrixFormat getFormat(MatrixT const & m) { return MatrixFormat::UNKNOWN; } };

// Get the format of a dense matrix. */
template <typename MatrixT>
struct GetFormatImpl< MatrixT, typename std::enable_if< std::is_base_of< Matrix<typename MatrixT::Value, MatrixT::Layout>,
                                                                         MatrixT >::value >::type >
{
  static MatrixFormat getFormat(MatrixT const & m)
  { return m.getLayout() == MatrixLayout::ROW_MAJOR ? MatrixFormat::DENSE_ROW_MAJOR : MatrixFormat::DENSE_COLUMN_MAJOR; }
};

// Get the format of a sparse matrix. */
template <typename MatrixT>
struct GetFormatImpl< MatrixT, typename std::enable_if< std::is_base_of< CompressedSparseMatrix<typename MatrixT::Value,
                                                                                                MatrixT::Layout,
                                                                                                typename MatrixT::Index2D,
                                                                                                typename MatrixT::Index1D>,
                                                                         MatrixT >::value >::type >
{
  static MatrixFormat getFormat(MatrixT const & m)
  { return m.getLayout() == MatrixLayout::ROW_MAJOR ? MatrixFormat::SPARSE_ROW_MAJOR : MatrixFormat::SPARSE_COLUMN_MAJOR; }
};

} // namespace MatrixUtilInternal

/** Test if a matrix is square. */
template <typename MatrixT>
bool
isSquare(MatrixT const & m)
{
  return MatrixUtilInternal::IsSquareImpl<MatrixT>::isSquare(m);
}

/** Get the format of a matrix. */
template <typename MatrixT>
MatrixFormat
getFormat(MatrixT const & m)
{
  return MatrixUtilInternal::GetFormatImpl<MatrixT>::getFormat(m);
}

} // namespace MatrixUtil

} // namespace DGP

#endif
