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

#ifndef __DGP_AffineTransform3_hpp__
#define __DGP_AffineTransform3_hpp__

#include "Common.hpp"
#include "AffineTransformN.hpp"

namespace DGP {

/** An affine transformation in 3-space, consisting of a linear transformation (3x3 matrix) plus a translation. */
template <typename T>
class /* DGP_API */ AffineTransformN<3, T> : public Internal::AffineTransformNBase<3, T>
{
  private:
    typedef Internal::AffineTransformNBase<3, T> BaseT;

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
     * Construct from 3 basis vectors, specifying the linear transform, and a translation. The four arguments form the columns
     * of the 3x4 matrix specifying the transform.
     */
    AffineTransformN(VectorT const & x, VectorT const & y, VectorT const & z, VectorT const & translation_)
    : BaseT(MatrixT(x[0], y[0], z[0], x[1], y[1], z[1], x[2], y[2], z[2]), translation_) {}

    /** Construct from a 3x4 array. */
    AffineTransformN(T const &  m00, T const &  m01, T const &  m02, T const & m03,
                     T const &  m10, T const &  m11, T const &  m12, T const & m13,
                     T const &  m20, T const &  m21, T const &  m22, T const & m23)
    : BaseT(MatrixT(m00, m01, m02, m10, m11, m12, m20, m21, m22), VectorT(m03, m13, m23)) {}

    using BaseT::scaling;

    /** Construct a scaling transform. */
    static AffineTransformN scaling(T const & sx, T const & sy, T const & sz)
    {
      return BaseT::scaling(VectorT(sx, sy, sz));
    }

    using BaseT::translation;

    /** Construct a translation. */
    static AffineTransformN translation(T const & tx, T const & ty, T const & tz)
    {
      return BaseT::translation(VectorT(tx, ty, tz));
    }

    /** Construct a rotation specified by an angle (in radians) around an axis. */
    static AffineTransformN rotationAxisAngle(VectorT const & axis, Real radians)
    {
      return AffineTransformN(MatrixT::rotationAxisAngle(axis, radians), VectorT::zero());
    }

    /**
     * Rotate about the Z axis by the roll angle, then the Y axis by the pitch angle, and finally the X axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesXYZ(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesXYZ(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Rotate about the Y axis by the roll angle, then the Z axis by the pitch angle, and finally the X axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesXZY(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesXZY(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Rotate about the Z axis by the roll angle, then the X axis by the pitch angle, and finally the Y axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesYXZ(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesYXZ(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Rotate about the X axis by the roll angle, then the Z axis by the pitch angle, and finally the Y axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesYZX(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesYZX(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Rotate about the Y axis by the roll angle, then the X axis by the pitch angle, and finally the Z axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesZXY(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesZXY(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Rotate about the X axis by the roll angle, then the Y axis by the pitch angle, and finally the Z axis by the yaw angle.
     */
    static AffineTransformN rotationEulerAnglesZYX(Real yaw_radians, Real pitch_radians, Real roll_radians)
    {
      return AffineTransformN(MatrixT::rotationEulerAnglesZYX(yaw_radians, pitch_radians, roll_radians), VectorT::zero());
    }

    /**
     * Return the transformation corresponding to the rotation from one direction vector to another.
     *
     * @param start_dir The vector to rotate from.
     * @param end_dir The vector to rotate to.
     * @param unitize_dirs If false, the directions will be assumed to have been pre-normalized to unit length before being
     *   passed to this function.
     */
    static AffineTransformN rotationArc(VectorT const & start_dir, VectorT const & end_dir, bool unitize_dirs = true)
    {
      return AffineTransformN(MatrixT::rotationArc(start_dir, end_dir, unitize_dirs), VectorT::zero());
    }

}; // class AffineTransformN<3, T>

/** The default affine transform class in real 3-space. */
typedef AffineTransformN<3, Real> AffineTransform3;

} // namespace DGP

#endif
