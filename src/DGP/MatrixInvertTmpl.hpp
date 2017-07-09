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

#include "Common.hpp"
#include "AddressableMatrix.hpp"
#include <algorithm>
#include <cmath>
#include <type_traits>

namespace DGP {
namespace Internal {

/**
 * <b>[Internal]</b> Invert a square matrix in place. This function is called by various matrix classes and should not be used
 * directly. Code borrowed from G3D::Matrix::inverseInPlaceGaussJordan(), originally from Numerical Recipes in C (gaussj). The
 * integer arrays \a pivot, \a row_index, and \a col_index are used for bookkeeping on the pivoting and must be
 * preallocated to n elements each, where n is the size (number of rows or number of columns) in the matrix to be inverted.
 *
 * Depending on which preprocessor flags are defined, this function inverts addressable matrices (in which case it uses virtual
 * accessors), or matrices with non-virtual element access via operator(). The latter is expected to be faster.
 *
 * @param mat Input matrix.
 * @param col_index A book-keeping array. Should be preallocated to n elements.
 * @param row_index A book-keeping array. Should be preallocated to n elements.
 * @param pivot A book-keeping array. Should be preallocated to n elements.
 */
template <typename DGP_INVERT_MATRIX_TEMPLATE_TYPE> /* DGP_DLL_LOCAL */
void
DGP_INVERT_MATRIX_FN( DGP_INVERT_MATRIX_TEMPLATE_TYPE & mat, long * col_index, long * row_index, long * pivot )
{
  typedef typename DGP_INVERT_MATRIX_TEMPLATE_TYPE::Value Value;

  alwaysAssertM(mat.isSquare(), "Can't invert non-square matrices");
  alwaysAssertM(!std::is_integral<Value>::value, "Can't invert integer matrices");

  long n = mat.numRows();

  // Initialize the pivot array to default values.
  static long const NO_PIVOT = -1;
  for (long i = 0; i < n; ++i)
    pivot[i] = NO_PIVOT;

  long col = 0, row = 0;

  // This is the main loop over the columns to be reduced
  //
  // Loop over the columns
  for (long c = 0; c < n; ++c)
  {
    // Find the largest element and use that as a pivot
    Value largest_magnitude = 0;

    // This is the outer loop of the search for a pivot element
    for (long r = 0; r < n; ++r)
    {
      // Unless we've already found the pivot, keep going
      if (pivot[r] != 0)
      {
        // Find the largest pivot
        for (long k = 0; k < n; ++k)
        {
          if (pivot[k] == NO_PIVOT)
          {
            Value mag = std::abs(DGP_MATRIX_GET(mat, r, k));
            if (mag >= largest_magnitude)
            {
              largest_magnitude = mag;
              row = r; col = k;
            }
          }
        }
      }
    }

    pivot[col]++;

    // Interchange columns so that the pivot element is on the diagonal (we'll have to undo this at the end)
    if (row != col)
      for (long k = 0; k < n; ++k)
        std::swap(DGP_MATRIX_GET_MUTABLE(mat, row, k), DGP_MATRIX_GET_MUTABLE(mat, col, k));

    // The pivot is now at [row, col]
    row_index[c] = row;
    col_index[c] = col;

    Value piv = DGP_MATRIX_GET(mat, col, col);
    if (piv == 0)  // FIXME: A more robust comparison?
      throw Error("invertMatrix: Matrix is singular");

    // Divide everything by the pivot (avoid computing the division multiple times).
    Value pivot_inverse = 1 / piv;
    DGP_MATRIX_SET(mat, col, col, 1);

    for (long k = 0; k < n; ++k)
      DGP_MATRIX_GET_MUTABLE(mat, col, k) *= pivot_inverse;

    // Reduce all rows
    for (long r = 0; r < n; ++r)
    {
      // Skip over the pivot row
      if (r != col)
      {
        Value old_value = DGP_MATRIX_GET(mat, r, col);
        DGP_MATRIX_SET(mat, r, col, 0);

        for (long k = 0; k < n; ++k)
          DGP_MATRIX_GET_MUTABLE(mat, r, k) -= DGP_MATRIX_GET(mat, col, k) * old_value;
      }
    }
  }

  // Put the columns back in the correct locations
  for (int i = (int)(n - 1); i >= 0; --i)  // int to handle case when i is -1
    if (row_index[i] != col_index[i])
      for (long k = 0; k < n; ++k)
        std::swap(DGP_MATRIX_GET_MUTABLE(mat, k, row_index[i]), DGP_MATRIX_GET_MUTABLE(mat, k, col_index[i]));
}

} // namespace Internal
} // namespace DGP
