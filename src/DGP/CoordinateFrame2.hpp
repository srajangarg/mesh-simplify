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

#ifndef __DGP_CoordinateFrame2_hpp__
#define __DGP_CoordinateFrame2_hpp__

#include "Common.hpp"
#include "CoordinateFrameN.hpp"

namespace DGP {

/** A coordinate frame in 2-space, defined by two orthonormal vectors. */
template <typename T>
class /* DGP_API */ CoordinateFrameN<2, T> : public Internal::CoordinateFrameNBase<2, T>
{
  private:
    typedef Internal::CoordinateFrameNBase<2, T> BaseT;

  public:
    typedef typename BaseT::RigidTransformT  RigidTransformT;
    typedef typename BaseT::VectorT          VectorT;
    typedef typename BaseT::MatrixT          MatrixT;

    /** Default constructor. Constructs the identity frame. */
    CoordinateFrameN() {}

    /** Construct from a rigid transform. */
    CoordinateFrameN(RigidTransformT const & src) : BaseT(src) {}

    /** Construct from a viewing position (\a eye) and a look-at position (\a center). */
    CoordinateFrameN(VectorT const & eye, VectorT const & center)
    {
      set(eye, center);
    }

    /** Initialize from a viewing position (\a eye) and a look-at position (\a center). */
    void set(VectorT const & eye, VectorT const & center)
    {
      VectorT f = (center - eye).unit();
      this->_setRotation(MatrixT(f[0], -f[1], f[1], f[0]));
      this->setTranslation(eye);
    }

  private:
    // Hide these functions from the default interface
    static RigidTransformT rotation(Real radians) { return RigidTransformT(); }

}; // class CoordinateFrameN<2, T>

/** The default coordinate frame class in real 2-space. */
typedef CoordinateFrameN<2, Real> CoordinateFrame2;

} // namespace DGP

#endif
