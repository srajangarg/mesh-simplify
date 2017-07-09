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

#ifndef __DGP_CoordinateFrameN_hpp__
#define __DGP_CoordinateFrameN_hpp__

#include "Common.hpp"
#include "RigidTransformN.hpp"

namespace DGP {

// Forward declarations
template <long N, typename T> class CoordinateFrameN;

namespace Internal {

/**
 * <b>[Internal]</b> Base class for a coordinate frame in N-space, defined by N orthonormal vectors.
 *
 * @note This class is <b>INTERNAL</b>! Don't use it directly.
 */
template <long N, typename T>
class /* DGP_DLL_LOCAL */ CoordinateFrameNBase : public RigidTransformN<N, T>
{
  public:
    typedef CoordinateFrameN<N, T>             CoordinateFrameT;  ///< N-dimensional coordinate frame type.
    typedef RigidTransformN<N, T>              RigidTransformT;   ///< N-dimensional rigid transform.
    typedef AffineTransformN<N, T>             AffineTransformT;  ///< N-dimensional affine transform.
    typedef typename RigidTransformT::VectorT  VectorT;
    typedef typename RigidTransformT::MatrixT  MatrixT;

    /** Default constructor. Constructs the identity frame. */
    CoordinateFrameNBase() {}

    /** Construct from a rigid transform. */
    CoordinateFrameNBase(RigidTransformT const & src) : RigidTransformT(src) {}

    /**
     * Construct from an affine transform, assuming it is rigid (<b>use with caution</b> since it can break the orthonormality
     * guarantee).
     */
    static CoordinateFrameT _fromAffine(AffineTransformT const & aff_)
    {
      return CoordinateFrameT(RigidTransformT::_fromAffine(aff_));
    }

    /** Get an axis of the frame. */
    VectorT getAxis(long i) const { return this->getRotation().getColumn(i); }

    /** Get the inverse transform. */
    CoordinateFrameT inverse() const
    {
      return CoordinateFrameT(RigidTransformT::inverse());
    }

    /** Compose this frame, treated as a rigid transform, with another. The other is applied first. */
    CoordinateFrameT operator*(CoordinateFrameT const & rhs) const
    {
      return CoordinateFrameT(this->RigidTransformT::operator*(rhs));
    }

    /** Transform a point from the local space of the coordinate frame to world space. */
    VectorT operator*(VectorT const & p) const
    {
      return this->RigidTransformT::operator*(p);
    }

    /** Transform a point from the local space of the coordinate frame to world space. */
    VectorT pointToWorldSpace(VectorT const & p) const
    {
      return this->RigidTransformT::operator*(p);
    }

    /** Transform a point from world space to the local space of the coordinate frame. */
    VectorT pointToObjectSpace(VectorT const & p) const
    {
      return (p - this->getTranslation()) * this->getRotation();
    }

    /** Transform a direction vector from the local space of the coordinate frame to world space. */
    VectorT vectorToWorldSpace(VectorT const & v) const
    {
      return this->getRotation() * v;
    }

    /** Transform a direction vector from world space to the local space of the coordinate frame. */
    VectorT vectorToObjectSpace(VectorT const & v) const
    {
      return v * this->getRotation();
    }

    /** Transform a normal from the local space of the coordinate frame to world space. */
    VectorT normalToWorldSpace(VectorT const & n) const
    {
      return this->getRotation() * n;
    }

    /** Transform a normal from world space to the local space of the coordinate frame. */
    VectorT normalToObjectSpace(VectorT const & n) const
    {
      return n * this->getRotation();
    }

    /** Get the identity frame (same as the world frame). */
    static CoordinateFrameT const & identity()
    {
      static CoordinateFrameT const idty(RigidTransformT::identity());
      return idty;
    }

  private:
    // Hide these functions from the default interface
    RigidTransformT operator*(RigidTransformT const & rhs) const      { return RigidTransformT(); }
    static RigidTransformT translation(VectorT const & translation_)  { return RigidTransformT(); }

}; // class CoordinateFrameNBase

} // namespace Internal

/** A coordinate frame in N-space, defined by N orthonormal vectors. */
template <long N, typename T>
class /* DGP_API */ CoordinateFrameN : public Internal::CoordinateFrameNBase<N, T>
{
  private:
    typedef Internal::CoordinateFrameNBase<N, T> BaseT;

  public:
    typedef typename BaseT::RigidTransformT  RigidTransformT;
    typedef typename BaseT::VectorT          VectorT;
    typedef typename BaseT::MatrixT          MatrixT;

    /** Default constructor. Constructs the identity frame. */
    CoordinateFrameN() {}

    /** Construct from a rigid transform. */
    CoordinateFrameN(RigidTransformT const & src) : BaseT(src) {}

}; // class CoordinateFrameN

/** Pipe a textual representation of a coordinate frame to a <code>std::ostream</code>. */
template <long N, typename T>
std::ostream &
operator<<(std::ostream & os, CoordinateFrameN<N, T> const & cf)
{
  return os << cf.toString();
}

} // namespace DGP

#include "CoordinateFrame2.hpp"
#include "CoordinateFrame3.hpp"

#endif
