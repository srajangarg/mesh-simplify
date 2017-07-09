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

#ifndef __DGP_RayN_hpp__
#define __DGP_RayN_hpp__

#include "Common.hpp"
#include "CoordinateFrameN.hpp"
#include "VectorN.hpp"

namespace DGP {

/** A ray in N-dimensional space, having an originating point and a direction vector (not necessarily unit length). */
template <long N, typename T>
class /* DGP_API */ RayN
{
  public:
    typedef VectorN<N, T> VectorT;  ///< N-dimensional vector.

    /** Default constructor. Does not initialize anything. */
    RayN() {}

    /** Initialize with an origin and a direction. The direction will <b>NOT</b> be normalized. */
    RayN(VectorT const & origin_, VectorT direction_) : origin(origin_), direction(direction_) {}

    /** Copy constructor. */
    RayN(RayN const & src) : origin(src.origin), direction(src.direction) {}

    /** Get the origin of the ray. */
    VectorT const & getOrigin() const { return origin; }

    /** Set the origin of the ray. */
    void setOrigin(VectorT const & origin_) { origin = origin_; }

    /** Get the direction of the ray. */
    VectorT const & getDirection() const { return direction; }

    /** Set the direction of the ray. The direction will <b>NOT</b> be normalized. */
    void setDirection(VectorT const & direction_) { direction = direction_; }

    /** Make the direction vector unit length. */
    void normalizeDirection() { direction.unitize(); }

    /** Transform the ray out of a local frame to world space. */
    RayN toWorldSpace(CoordinateFrameN<N, T> const & frame) const
    {
      return RayN(frame.pointToWorldSpace(origin), frame.vectorToWorldSpace(direction));
    }

    /** Transform the ray from world space into a local frame. */
    RayN toObjectSpace(CoordinateFrameN<N, T> const & frame) const
    {
      return RayN(frame.pointToObjectSpace(origin), frame.vectorToObjectSpace(direction));
    }

    /**
     * Get a parametrized point on the ray.
     *
     * @return getOrigin() + \a t * getDirection()
     */
    VectorT getPoint(T const & t) const { return origin + t * direction; }

    /** Get the distance of a point from the ray. */
    T distance(VectorT const & p) const { return (closestPoint(p) - p).length(); }

    /** Get the square of the distance of a point from the ray. */
    T squaredDistance(VectorT const & p) const { return (closestPoint(p) - p).squaredLength(); }

    /** Get the the point on the ray closest to a given point. */
    VectorT closestPoint(VectorT const & p) const
    {
      T t = (p - origin).dot(direction);  // we'll normalize direction later
      if (t < 0)
        return origin;
      else
      {
        T dir_sqlen = direction.squaredLength();
        if (Math::fuzzyEq(dir_sqlen, static_cast<T>(0)))
          return origin;

        // Direction has to be normalized twice -- once during the dot product above and once in the scaling below. We can
        // combine the two divisions and avoid the square roots.
        return origin + (t / dir_sqlen) * direction;
      }
    }

    /** Get a textual representation of the ray. */
    std::string toString() const
    {
      return std::string("[origin: ") + origin.toString() + ", direction: " + direction.toString() + ']';
    }

  private:
    VectorT origin;     ///< Origin of the ray.
    VectorT direction;  ///< Direction of the ray.

}; // class RayN

} // namespace DGP

#include "Ray3.hpp"

#endif
