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

#ifndef __DGP_Vector2_hpp__
#define __DGP_Vector2_hpp__

#include "VectorN.hpp"

namespace DGP {

/** 2-dimensional vectors on a field T. */
template <typename T>
class /* DGP_API */ VectorN<2, T> : public Internal::VectorNBase<2, T>
{
  private:
    typedef Internal::VectorNBase<2, T> BaseT;

  public:
    /** Default constructor (does not initialize anything). */
    VectorN() {}

    /** Initialize all components to a single value. */
    explicit VectorN(T const & fill_value) : BaseT(fill_value) {}

    /** Copy constructor. */
    template <typename U> VectorN(VectorN<2, U> const & src) : BaseT(src) {}

    /** Initialize all components of the vector. */
    VectorN(T const & x_, T const & y_)
    {
      (*this)[0] = x_;
      (*this)[1] = y_;
    }

    /** Set all elements of the vector. */
    void set(T const & x_, T const & y_)
    {
      (*this)[0] = x_;
      (*this)[1] = y_;
    }

    /**
     * Get a unit vector perpendicular to this one, forming an orthonormal right-handed basis (u, this->unit()). In other words,
     * if this is the Y axis of the local frame, then the function returns the X axis.
     *
     * In 2D, the behavior of this function is identical to createOrthonormalBasis().
     */
    VectorN getOrthogonalDirection() const { return VectorN(y(), -x()); }

    /**
     * Get a unit vector perpendicular to this one, forming an orthonormal right-handed basis (u, this->unit()). In other words,
     * if this is the Y axis of the local frame, then the function returns the X axis.
     *
     * In 2D, the behavior of this function is identical to getOrthogonalDirection().
     */
    void createOrthonormalBasis(VectorN & u) const { u = getOrthogonalDirection(); }

    /** Get a unit vector along positive X. */
    static VectorN const & unitX() { static VectorN const ux(1, 0); return ux; }

    /** Get a unit vector along positive Y. */
    static VectorN const & unitY() { static VectorN const uy(0, 1); return uy; }

    /** Get the X coordinate. */
    T const & x() const { return (*this)[0]; }

    /** Get the X coordinate. */
    T & x() { return (*this)[0]; }

    /** Get the Y coordinate. */
    T const & y() const { return (*this)[1]; }

    /** Get the Y coordinate. */
    T & y() { return (*this)[1]; }

    /** Swizzle operator, returns XX. */
    VectorN xx() const { return VectorN   (x(), x()); }

    /** Swizzle operator, returns YX. */
    VectorN yx() const { return VectorN   (y(), x()); }

    /** Swizzle operator, returns XY. */
    VectorN xy() const { return VectorN   (x(), y()); }

    /** Swizzle operator, returns YY. */
    VectorN yy() const { return VectorN   (y(), y()); }

}; // class VectorN<2, T>

/** The default 2D real vector class. */
typedef VectorN<2, Real> Vector2;

} // namespace DGP

#endif
