//============================================================================
//
// DGP: Digital Geometry Processing toolkit
// Copyright (C) 2016, Siddhartha Chaudhuri
//
// This software is covered by a BSD license. Portions derived from other
// works are covered by their respective licenses. For full licensing
// information see the LICENSE.txt file.
//
//=================================== Original header ========================
//
// COTD Entry submitted by John W. Ratcliff [jratcliff@verant.com]
//
// ** THIS IS A CODE SNIPPET WHICH WILL EFFICIEINTLY TRIANGULATE ANY
// ** POLYGON/CONTOUR (without holes) AS A STATIC CLASS.  THIS SNIPPET
// ** IS COMPRISED OF 3 FILES, TRIANGULATE.H, THE HEADER FILE FOR THE
// ** TRIANGULATE BASE CLASS, TRIANGULATE.CPP, THE IMPLEMENTATION OF
// ** THE TRIANGULATE BASE CLASS, AND TEST.CPP, A SMALL TEST PROGRAM
// ** DEMONSTRATING THE USAGE OF THE TRIANGULATOR.  THE TRIANGULATE
// ** BASE CLASS ALSO PROVIDES TWO USEFUL HELPER METHODS, ONE WHICH
// ** COMPUTES THE AREA OF A POLYGON, AND ANOTHER WHICH DOES AN EFFICENT
// ** POINT IN A TRIANGLE TEST.
// ** SUBMITTED BY JOHN W. RATCLIFF (jratcliff@verant.com) July 22, 2000
//
// Static class to triangulate any contour/polygon efficiently
// You should replace Vector2d with whatever your own Vector
// class might be.  Does not support polygons with holes.
// Uses STL vectors to represent a dynamic array of vertices.
// This code snippet was submitted to FlipCode.com by
// John W. Ratcliff (jratcliff@verant.com) on July 22, 2000
// I did not write the original code/algorithm for this
// this triangulator, in fact, I can't even remember where I
// found it in the first place.  However, I did rework it into
// the following black-box static class so you can make easy
// use of it in your own code.  Simply replace Vector2d with
// whatever your own Vector implementation might be.
//
//============================================================================

#ifndef __DGP_Polygon3_hpp__
#define __DGP_Polygon3_hpp__

#include "Common.hpp"
#include "AxisAlignedBox3.hpp"
#include "Math.hpp"
#include "Vector3.hpp"

namespace DGP {

/** A polygon in 3-space. Original code due to John W. Ratcliff. */
class DGP_API Polygon3
{
  public:
    /** A vertex plus an index. */
    struct DGP_API IndexedVertex
    {
      /** Default constructor. */
      IndexedVertex() {}

      /** Initializing constructor. */
      IndexedVertex(Vector3 const & position_, long index_) : position(position_), index(index_) {}

      Vector3 position;  ///< The position of the vertex.
      long index;  ///< The index of the vertex.
    };

    /** Construct an empty polygon. */
    Polygon3();

    /**
     * Add a vertex to the polygon. The vertex is inserted at the end of the current sequence of vertices, and by default is
     * assigned an index that is one more than the maximum index in the polygon so far (or zero if this is the first vertex).
     * For efficiency the polygon <b>is not checked for planarity</b>, the caller should ensure that all vertices are coplanar.
     */
    void addVertex(Vector3 const & p);

    /**
     * Add an indexed vertex to the polygon. The vertex is inserted at the end of the current sequence of vertices. For
     * efficiency the polygon <b>is not checked for planarity</b>, the caller should ensure that all vertices are coplanar.
     */
    void addVertex(Vector3 const & p, long index);

    /** Get the number of vertices in the polygon. */
    long numVertices() const;

    /**
     * Get the vertex at position \a poly_index in the sequence of vertices around the polygon boundary.
     *
     * @note \a poly_index is determined by the sequence of addVertex() calls, <b>NOT</b> by the index supplied in
     *   addVertex(Vector2 const &, long)!
     */
    IndexedVertex const & getVertex(long poly_index) const;

    /** Delete all vertices from the polygon. */
    void clear();

    /**
     * Triangulate the polygon and return the set of triangle indices (in successive groups of 3). All prior data in the
     * supplied array are cleared.
     *
     * @return The number of triangles created.
     */
    long triangulate(std::vector<long> & tri_indices) const;

    /** Compute the area of the polygon. */
    Real area() const;

    /** Compute the unit normal of the polygon. */
    Vector3 getNormal() const;

    /** Get the bounding box of the polygon. */
    AxisAlignedBox3 const & getBounds();

    /**
     * Utility function to split a (possibly non-convex) quadrilateral into a pair of triangles. The quadrilateral is assumed to
     * be planar and a default tolerance threshold is used for checking degeneracy.
     *
     * @param p0 Position of the first vertex of the quadrilateral.
     * @param p1 Position of the second vertex of the quadrilateral.
     * @param p2 Position of the third vertex of the quadrilateral.
     * @param p3 Position of the fourth vertex of the quadrilateral.
     *
     * @param i0 Used to return the index of the first vertex of the first triangle.
     * @param j0 Used to return the index of the second vertex of the first triangle.
     * @param k0 Used to return the index of the third vertex of the first triangle.
     *
     * @param i1 Used to return the index of the first vertex of the second triangle.
     * @param j1 Used to return the index of the second vertex of the second triangle.
     * @param k1 Used to return the index of the third vertex of the second triangle.
     *
     * @return The number of triangles produced (can be < 2 if the quadrilateral is degenerate).
     *
     * @note Might break in very very degenerate cases (not fully tested).
     * @note Have to have two versions of this function -- one with a default tolerance and one with a caller-specified
     *   tolerance, since Visual Studio (and other compilers?) has some problems with template resolution of default arguments.
     */
    template <typename T>
    static int triangulateQuad(VectorN<3, T> const & p0, VectorN<3, T> const & p1,
                               VectorN<3, T> const & p2, VectorN<3, T> const & p3,
                               int & i0, int & j0, int & k0,
                               int & i1, int & j1, int & k1)
    {
      // Tolerance a bit smaller than for linear quantities, we're comparing area^2
      return triangulateQuad(p0, p1, p2, p3, i0, j0, k0, i1, j1, k1, Math::eps<T>() * Math::eps<T>());
    }

    /**
     * Utility function to split a (possibly non-convex) quadrilateral into a pair of triangles. The quadrilateral is assumed to
     * be planar.
     *
     * @param p0 Position of the first vertex of the quadrilateral.
     * @param p1 Position of the second vertex of the quadrilateral.
     * @param p2 Position of the third vertex of the quadrilateral.
     * @param p3 Position of the fourth vertex of the quadrilateral.
     *
     * @param i0 Used to return the index of the first vertex of the first triangle.
     * @param j0 Used to return the index of the second vertex of the first triangle.
     * @param k0 Used to return the index of the third vertex of the first triangle.
     *
     * @param i1 Used to return the index of the first vertex of the second triangle.
     * @param j1 Used to return the index of the second vertex of the second triangle.
     * @param k1 Used to return the index of the third vertex of the second triangle.
     *
     * @param epsilon A tolerance threshold for checking degeneracy.
     *
     * @return The number of triangles produced (can be < 2 if the quadrilateral is degenerate).
     *
     * @note Might break in very very degenerate cases (not fully tested).
     */
    template <typename T>
    static int triangulateQuad(VectorN<3, T> const & p0, VectorN<3, T> const & p1,
                               VectorN<3, T> const & p2, VectorN<3, T> const & p3,
                               int & i0, int & j0, int & k0,
                               int & i1, int & j1, int & k1,
                               T const & epsilon)
    {
      typedef VectorN<3, T> VectorT;

      // We have two diagonals to split along. Try one and if it produces a triangle outside the polygon, pick the other one

      // First diagonal is p0-p2
      VectorT n0 = (p1 - p0).cross(p2 - p0);
      VectorT n1 = (p2 - p0).cross(p3 - p0);

      if (n0.dot(n1) < 0)
      {
        // Flip to diagonal p1-p3
        n0 = (p2 - p1).cross(p3 - p1);
        n1 = (p3 - p1).cross(p0 - p1);

        i0 = 1; j0 = 2; k0 = 3;
        i1 = 1; j1 = 3; k1 = 0;
      }
      else
      {
        i0 = 0; j0 = 1; k0 = 2;
        i1 = 0; j1 = 2; k1 = 3;
      }

      // Check for degenerate triangles
      if (n0.squaredLength() < epsilon)
      {
        if (n1.squaredLength() < epsilon)
          return 0;
        else
        {
          i0 = i1; j0 = j1; k0 = k1;  // the second triangle is the only non-degenerate one
          return 1;
        }
      }
      else if (n1.squaredLength() < epsilon)
        return 1;
      else
        return 2;
    }

  private:
    /** Signed area of projection onto primary coordinate plane. */
    Real projArea() const;

    /** Check if a triangle can be removed. */
    bool snip(size_t u, size_t v, size_t w, size_t n, std::vector<size_t> const & indices) const;

    std::vector<IndexedVertex> vertices;
    long max_index;
    AxisAlignedBox3 bounds;
    mutable std::vector<Vector2> proj_vertices;

    friend class Polygon2;

}; // class Polygon3

} // namespace DGP

#endif
