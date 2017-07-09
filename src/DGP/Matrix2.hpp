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

#ifndef __DGP_Matrix2_hpp__
#define __DGP_Matrix2_hpp__

#include "MatrixMN.hpp"
#include "VectorN.hpp"
#include <cmath>

namespace DGP {

/**
 * Square 2 x 2 matrices on a field T. The matrices are stored internally in row-major form, so row-major access is recommended.
 */
template <typename T>
class /* DGP_API */ MatrixMN<2, 2, T> : public Internal::SquareMatrixN<2, T>
{
  private:
    typedef Internal::SquareMatrixN<2, T> BaseT;

  public:
    /** Default constructor (does not initialize anything). */
    MatrixMN() {}

    /** Initialize all components to a single value. */
    explicit MatrixMN(T const & fill_value) : BaseT(fill_value) {}

    /** Initialize all 4 components of the matrix. */
    MatrixMN(T const & m00, T const & m01,
             T const & m10, T const & m11)
    {
      (*this)(0, 0) = m00; (*this)(0, 1) = m01;
      (*this)(1, 0) = m10; (*this)(1, 1) = m11;
    }

    /**
     * Create a matrix from its columns.
     *
     * @param cv0 First column of the matrix.
     * @param cv1 Second column of the matrix.
     */
    static MatrixMN fromColumns(VectorN<2, T> const & cv0, VectorN<2, T> const & cv1)
    {
      return MatrixMN(cv0[0], cv1[0],
                      cv0[1], cv1[1]);
    }

    /**
     * Create a matrix from its rows.
     *
     * @param rv0 First row of the matrix.
     * @param rv1 Second row of the matrix.
     */
    static MatrixMN fromRows(VectorN<2, T> const & rv0, VectorN<2, T> const & rv1)
    {
      return MatrixMN(rv0[0], rv0[1],
                      rv1[0], rv1[1]);
    }

    /** Matrix to rotate about the origin by an angle (in radians). */
    static MatrixMN rotation(Real radians)
    {
      T s = std::sin(radians);
      T c = std::cos(radians);
      return MatrixMN(c, -s, s, c);
    }

    /** Get the matrix of cofactors. */
    MatrixMN cofactor() const
    {
      return adjoint().transpose();
    }

    /** Get the adjoint of the matrix. */
    MatrixMN adjoint() const
    {
      return MatrixMN((*this)(1, 1), -(*this)(0, 1),
                     -(*this)(1, 0),  (*this)(0, 0));
    }

    /** Get the determinant of the matrix. */
    T determinant() const
    {
      return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
    }

    /**
     * Invert the matrix in-place.
     *
     * @param tolerance The numerical tolerance of the computation. If the determinant has smaller absolute value than the
     *   tolerance, the computation is aborted and false is returned.
     *
     * @return True if the computation succeeded with the given tolerance, else false.
     */
    bool invert(double tolerance = 1.0e-30)
    {
      // Invert a 2x2 matrix using cofactors.

      T det = determinant();
      if (std::abs(det) <= tolerance)
        return false;

      T inv_det = 1 / det;
      *this = MatrixMN(inv_det * (*this)(1, 1), -inv_det * (*this)(0, 1),
                      -inv_det * (*this)(1, 0),  inv_det * (*this)(0, 0));

      return true;
    }

    /**
     * Get the inverse of the matrix.
     *
     * @param tolerance The numerical tolerance of the computation. If the determinant has smaller absolute value than the
     *   tolerance, the computation is aborted and an error is thrown.
     */
    MatrixMN inverse(double tolerance = 1.0e-30) const
    {
      MatrixMN result = *this;
      if (!result.invert())
        throw Error("MatrixMN<2, 2, T>: Could not invert matrix " + this->toString() + " with given tolerance");

      return result;
    }

}; // class MatrixMN<2, 2, T>

/** The default 2x2 real matrix class. */
typedef MatrixMN<2, 2, Real> Matrix2;

} // namespace DGP

#endif
