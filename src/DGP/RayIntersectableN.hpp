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

#ifndef __DGP_RayIntersectableN_hpp__
#define __DGP_RayIntersectableN_hpp__

#include "Common.hpp"
#include "RayN.hpp"

namespace DGP {

/**
 * A description of the intersection point of a ray with an object. Specifies the hit time and the normal at the intersection
 * point.
 */
template <long N, typename T>
class /* DGP_API */ RayIntersectionN
{
  public:
    typedef VectorN<N, T> VectorT;  ///< N-dimensional vector.

  private:
    T time;
    bool has_normal;
    VectorT normal;

  public:
    /** Constructor. */
    RayIntersectionN(T time_ = -1, VectorT const * normal_ = NULL)
    : time(time_), has_normal(normal_ != NULL), normal(normal_ ? *normal_ : VectorT::zero())
    {}

    /** Check if the intersection is valid. */
    bool isValid() const { return time >= 0; }

    /** Get the intersection time. */
    T getTime() const { return time; }

    /** Set the intersection time. */
    void setTime(T time_) { time = time_; }

    /** Check if the normal at the intersection point is known. */
    bool hasNormal() const { return has_normal; }

    /** Get the normal at the intersection point. The return value is undefined if hasNormal() returns false. */
    VectorT const & getNormal() const { return normal; }

    /** Set the normal at the intersection point. hasNormal() will subsequently return true. */
    void setNormal(VectorT const & normal_) { normal = normal_; has_normal = true; }

}; // class RayIntersectionN

/** Interface for an object that supports ray intersection queries in 3-space. */
template <long N, typename T>
class /* DGP_API */ RayIntersectableN
{
  public:
    /** Destructor. */
    virtual ~RayIntersectableN() {}

    /**
     * Check if a ray intersects the object in the forward direction.
     *
     * @param ray The ray to test for intersection.
     * @param max_time Maximum allowable hit time, ignored if negative.
     */
    virtual bool rayIntersects(RayN<N, T> const & ray, T max_time = -1) const
    { return rayIntersectionTime(ray, max_time) >= 0; }

    /**
     * Get the time taken for a ray to intersect the object, or a negative value if there was no intersection in the forward
     * direction. All subclasses must reimplement this method. If the return value is negative, it should be at least
     *
     * @param ray The ray to test for intersection.
     * @param max_time Maximum allowable hit time, ignored if negative.
     */
    virtual T rayIntersectionTime(RayN<N, T> const & ray, T max_time = -1) const = 0;

    /**
     * Get the intersection of a ray with the object, including the hit time and the normal at the intersection point. A
     * negative time is returned if there was no intersection in the forward direction. If the normal cannot be computed, the
     * zero vector is returned.
     *
     * @param ray The ray to test for intersection.
     * @param max_time Maximum allowable hit time, ignored if negative.
     *
     * @note The returned normal need not have unit length.
     */
    virtual RayIntersectionN<N, T> rayIntersection(RayN<N, T> const & ray, T max_time = -1) const
    { return RayIntersectionN<N, T>(rayIntersectionTime(ray, max_time)); }

}; // class RayIntersectableN

} // namespace DGP

#include "RayIntersectable3.hpp"

#endif
