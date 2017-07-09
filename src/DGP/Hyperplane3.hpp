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

#ifndef __DGP_Hyperplane3_hpp__
#define __DGP_Hyperplane3_hpp__

#include "Common.hpp"
#include "HyperplaneN.hpp"
#include "Math.hpp"

namespace DGP {

/** A plane (2-flat) in 3-dimensional space. */
template <typename T>
class /* DGP_API */ HyperplaneN<3, T> : public Internal::HyperplaneNBase<3, T>
{
  private:
    typedef Internal::HyperplaneNBase<3, T> BaseT;

  public:
    typedef typename BaseT::VectorT VectorT;

    static HyperplaneN fromThreePoints(VectorT const & point1, VectorT const & point2, VectorT const & point3)
    {
      HyperplaneN hyperplane;

      hyperplane.normal = (point2 - point1).cross(point3 - point1).unit();
      hyperplane.dist = hyperplane.normal.dot(point1);
      return hyperplane;
    }

    /** Construct a hyperplane given coefficients a, b, c, d of the plane equation a * x + b * y + c * z + d = 0. */
    static HyperplaneN fromEquation(T const & a, T const & b, T const & c, T const & d)
    {
      HyperplaneN hyperplane;

      hyperplane.normal = VectorT(a, b, c);
      T sqlen = hyperplane.normal.squaredLength();
      if (Math::fuzzyEq(sqlen, static_cast<T>(0)))
      {
        hyperplane.normal = VectorT::zero();
        hyperplane.dist = 0;
      }
      else
      {
        T len = std::sqrt(sqlen);
        hyperplane.normal /= len;
        hyperplane.dist = -d / len;
      }

      return hyperplane;
    }

    using BaseT::getEquation;

    /** Get the coefficients a, b, c, d of the plane equation a * x + b * y + c * z + d = 0. */
    void getEquation(T & a, T & b, T & c, T & d) const
    {
      a = this->normal.x();
      b = this->normal.y();
      c = this->normal.z();
      d = -this->dist;
    }

}; // class HyperplaneN<3, T>

/** The default plane class in 3-dimensional real space. */
typedef HyperplaneN<3, Real> Plane3;

} // namespace DGP

#endif
