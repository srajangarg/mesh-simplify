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

#ifndef __DGP_AxisAlignedBox3_hpp__
#define __DGP_AxisAlignedBox3_hpp__

#include "Common.hpp"
#include "AxisAlignedBoxN.hpp"

namespace DGP {

/** A 3-dimensional axis-aligned box. */
template <typename T>
class /* DGP_API */ AxisAlignedBoxN<3, T> : public Internal::AxisAlignedBoxNBase<3, T>
{
  private:
    typedef Internal::AxisAlignedBoxNBase<3, T> BaseT;

  public:
    typedef typename BaseT::VectorT VectorT;

    /** Default constructor, creates a null box. */
    AxisAlignedBoxN() : BaseT() {}

    /** Constructor. Sets the box to be a single point. */
    AxisAlignedBoxN(VectorT const & v) : BaseT(v) {}

    /** Constructor. Sets the extents of the box. */
    AxisAlignedBoxN(VectorT const & lo_, VectorT const & hi_) : BaseT(lo_, hi_) {}

    /**
     * Transform the box and return a new axis-aligned box which tightly encloses the result.
     *
     * Algorithm taken from the Ogre source code, http://www.ogre3d.org.
     */
    template <typename TransformT> AxisAlignedBoxN transformAndBound(TransformT const & tr) const
    {
      Vector3 const & lo_ = this->getLow();
      Vector3 const & hi_ = this->getHigh();

      // We sequentially compute the corners in the following order:
      // 0, 6, 5, 1, 2, 4, 7, 3
      // This sequence allows us to only change one member at a time to get at all corners. For each one, we transform it and
      // merge the resulting point.

      // min min min
      Vector3 current_corner = lo_;
      AxisAlignedBoxN result = AxisAlignedBoxN(tr * current_corner);

      // min min max
      current_corner.z() = hi_.z();
      result.merge(tr * current_corner);

      // min max max
      current_corner.y() = hi_.y();
      result.merge(tr * current_corner);

      // min max min
      current_corner.z() = lo_.z();
      result.merge(tr * current_corner);

      // max max min
      current_corner.x() = hi_.x();
      result.merge(tr * current_corner);

      // max max max
      current_corner.z() = hi_.z();
      result.merge(tr * current_corner);

      // max min max
      current_corner.y() = lo_.y();
      result.merge(tr * current_corner);

      // max min min
      current_corner.z() = lo_.z();
      result.merge(tr * current_corner);

      return result;
    }

    /**
     * Get edge number \a i of the box, where i is between 0 and 11.
     *
     * @param i Index of edge, between 0 and 11 inclusive.
     * @param start Used to return the starting point of the edge.
     * @param end Used to return the endpoint of the edge.
     */
    void getEdge(int i, Vector3 & start, Vector3 & end) const
    {
      static int const INDICES[12][6] = {
        { 0, 0, 0, 0, 0, 1 },
        { 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 1, 0, 0 },

        { 1, 1, 0, 1, 1, 1 },
        { 1, 1, 0, 1, 0, 0 },
        { 1, 1, 0, 0, 1, 0 },

        { 1, 0, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1 },
        { 1, 0, 1, 1, 0, 0 },

        { 0, 1, 1, 1, 1, 1 },
        { 0, 1, 1, 0, 0, 1 },
        { 0, 1, 1, 0, 1, 0 }
      };

      Vector3 const * v[2] = { &this->getLow(), &this->getHigh() };
      start  =  Vector3((*v[INDICES[i][0]])[0], (*v[INDICES[i][1]])[1], (*v[INDICES[i][2]])[2]);
      end    =  Vector3((*v[INDICES[i][3]])[0], (*v[INDICES[i][4]])[1], (*v[INDICES[i][5]])[2]);
    }

}; // class AxisAlignedBoxN<3, T>

/** The default axis-aligned box class in 3-dimensional real space. */
typedef AxisAlignedBoxN<3, Real> AxisAlignedBox3;

} // namespace DGP

#endif
