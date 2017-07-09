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

#ifndef __DGP_Polygon2_hpp__
#define __DGP_Polygon2_hpp__

#include "Common.hpp"
#include "Vector2.hpp"

namespace DGP {

class Polygon3;

/** A polygon in 2-space. */
class DGP_API Polygon2
{
  public:
    /** %Options controlling interior triangulation. */
    struct DGP_API TriangulationOptions
    {
      Real area_bound;  ///< The maximum area of any output triangle (default -1, indicating no upper bound).
      long max_steiner_points;  /**< The maximum number of Steiner points that can be inserted (default -1, indicating no
                                     limit). */

      /** Constructor. */
      TriangulationOptions();

      /** Get the default set of triangulation options. */
      static TriangulationOptions const & defaults() { static TriangulationOptions const def; return def; }

    }; // struct TriangulationOptions

    /** A vertex plus an index. */
    struct DGP_API IndexedVertex
    {
      /** Default constructor. */
      IndexedVertex() {}

      /** Initializing constructor. */
      IndexedVertex(Vector2 const & position_, long index_) : position(position_), index(index_) {}

      Vector2 position;  ///< The position of the vertex.
      long index;  ///< The index of the vertex.
    };

    /** Construct an empty polygon. */
    Polygon2();

    /** Destructor. */
    ~Polygon2();

    /**
     * Add a vertex to the polygon. The vertex is inserted at the end of the current sequence of vertices, and by default is
     * assigned an index that is one more than the maximum index in the polygon so far (or zero if this is the first vertex).
     */
    void addVertex(Vector2 const & p);

    /** Add an indexed vertex to the polygon. The vertex is inserted at the end of the current sequence of vertices. */
    void addVertex(Vector2 const & p, long index);

    /** Get the number of vertices in the polygon. */
    long numVertices() const;

    /**
     * Get the vertex at position \a poly_index in the sequence of vertices around the polygon boundary.
     *
     * @note \a poly_index is determined by the sequence of addVertex() calls, <b>NOT</b> by the index supplied in
     *   addVertex(Vector2 const &, long)!
     */
    IndexedVertex getVertex(long poly_index) const;

    /** Delete all vertices from the polygon. */
    void clear();

    /**
     * Triangulate the polygon and return the set of triangle indices (in successive groups of 3). All prior data in the
     * supplied array are cleared.
     *
     * @return The number of triangles created.
     */
    long triangulate(std::vector<long> & tri_indices) const;

    /**
     * Triangulate the polygon, inserting Steiner vertices as necessary in the interior of the polygon for a well-conditioned
     * result. All prior data in the supplied arrays are cleared.
     *
     * @param tri_verts Used to return the vertices of the output triangulation.
     * @param tri_indices Used to return the vertex indices of output triangles (w.r.t. \a tri_verts), in successive groups of
     *   3.
     * @param tri_vert_is_boundary If not-null, used to return a flag for each output vertex indicating whether it's on the
     *   boundary of the triangulated domain or not.
     * @param options %Options controlling the quality of the triangulation.
     *
     * @return The number of triangles created.
     */
    long triangulateInterior(std::vector<Vector2> & tri_verts, std::vector<long> & tri_indices,
                             std::vector<bool> * tri_vert_is_boundary = NULL,
                             TriangulationOptions const & options = TriangulationOptions::defaults()) const;

    /** Compute the area of the polygon. */
    Real area() const;

  private:
    Polygon3 * impl;

}; // class Polygon2

} // namespace DGP

#endif
