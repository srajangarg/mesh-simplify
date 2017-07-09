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

#ifndef __DGP_AffineTransform2_hpp__
#define __DGP_AffineTransform2_hpp__

#include "Common.hpp"
#include "AffineTransformN.hpp"

namespace DGP {

/** An affine transformation in 2-space, consisting of a linear transformation (2x2 matrix) plus a translation. */
template <typename T>
class /* DGP_API */ AffineTransformN<2, T> : public Internal::AffineTransformNBase<2, T>
{
  private:
    typedef Internal::AffineTransformNBase<2, T> BaseT;

  public:
    typedef typename BaseT::VectorT  VectorT;
    typedef typename BaseT::MatrixT  MatrixT;

    /** Default constructor. Does not initialize anything. */
    AffineTransformN() {}

    /** Construct from a linear transform, followed by a translation. */
    AffineTransformN(MatrixT const & linear_, VectorT const & translation_ = VectorT::zero()) : BaseT(linear_, translation_) {}

    /** Copy constructor. */
    AffineTransformN(AffineTransformN const & src) : BaseT(src) {}

    /**
     * Construct from 2 basis vectors, specifying the linear transform, and a translation. The three arguments form the columns
     * of the 2x3 matrix specifying the transform.
     */
    AffineTransformN(VectorT const & x, VectorT const & y, VectorT const & translation_)
    : BaseT(MatrixT(x[0], y[0], x[1], y[1]), translation_) {}

    /** Construct from a 2x3 array. */
    AffineTransformN(T const &  m00, T const &  m01, T const &  m02,
                     T const &  m10, T const &  m11, T const &  m12)
    : BaseT(MatrixT(m00, m01, m10, m11), VectorT(m02, m12)) {}

    using BaseT::scaling;

    /** Construct a scaling transform. */
    static AffineTransformN scaling(T const & sx, T const & sy)
    {
      return BaseT::scaling(VectorT(sx, sy));
    }

    using BaseT::translation;

    /** Construct a translation. */
    static AffineTransformN translation(T const & tx, T const & ty)
    {
      return BaseT::translation(VectorT(tx, ty));
    }

    /** Construct a rotation specified by an angle (in radians) around the origin. */
    static AffineTransformN rotation(Real radians)
    {
      return AffineTransformN(MatrixT::rotation(radians), VectorT::zero());
    }

}; // class AffineTransformN<2, T>

/** The default affine transform class in real 2-space. */
typedef AffineTransformN<2, Real> AffineTransform2;

} // namespace DGP

#endif
