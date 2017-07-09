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

#ifndef __DGP_RigidTransform2_hpp__
#define __DGP_RigidTransform2_hpp__

#include "Common.hpp"
#include "AffineTransform2.hpp"
#include "RigidTransformN.hpp"

namespace DGP {

/**
 * A rigid transformation in 2-space, consisting of a rotation followed by a translation.
 *
 * @note While this is technically an affine transform, it restricts enough functionality to make a separate implementation
 * preferable. It can be trivially converted to an AffineTransform2 using the implicit conversion operator or toAffine().
 */
template <typename T>
class /* DGP_API */ RigidTransformN<2, T> : public Internal::RigidTransformNBase<2, T>
{
  private:
    typedef Internal::RigidTransformNBase<2, T> BaseT;

  public:
    typedef typename BaseT::AffineTransformT  AffineTransformT;
    typedef typename BaseT::VectorT           VectorT;
    typedef typename BaseT::MatrixT           MatrixT;

    /** Default constructor. Constructs the identity transform. */
    RigidTransformN() {}

    using BaseT::translation;

    /** Construct a translation. */
    static RigidTransformN translation(T const & tx, T const & ty)
    {
      return BaseT::translation(VectorT(tx, ty));
    }

    /** Construct a rotation specified by an angle (in radians) around the origin. */
    static RigidTransformN rotation(Real radians)
    {
      return BaseT::_fromAffine(AffineTransformT::rotation(radians));
    }

}; // class RigidTransformN<2, T>

/** The default rigid transform class in real 2-space. */
typedef RigidTransformN<2, Real> RigidTransform2;

} // namespace DGP

#endif
