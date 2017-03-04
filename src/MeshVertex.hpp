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

#ifndef __A2_MeshVertex_hpp__
#define __A2_MeshVertex_hpp__

#include "Common.hpp"
#include "DGP/Colors.hpp"
#include "DGP/Vector3.hpp"
#include <list>

// Forward declarations
class MeshEdge;
class MeshFace;

/** Vertex of a mesh. */
class MeshVertex
{
  public:
    typedef MeshEdge Edge;  ///< Edge of the mesh.
    typedef MeshFace Face;  ///< Face of the mesh.

  private:
    typedef std::list<Edge *> EdgeList;
    typedef std::list<Face *> FaceList;

  public:
    typedef typename EdgeList::iterator        EdgeIterator;       ///< Iterator over edges.
    typedef typename EdgeList::const_iterator  EdgeConstIterator;  ///< Const iterator over edges.
    typedef typename FaceList::iterator        FaceIterator;       ///< Iterator over faces.
    typedef typename FaceList::const_iterator  FaceConstIterator;  ///< Const iterator over faces.

    /** Default constructor. */
    MeshVertex()
    : position(Vector3::zero()), normal(Vector3::zero()), color(ColorRGBA(1, 1, 1, 1)), has_precomputed_normal(false),
      normal_normalization_factor(0), quadric(DMat4::zero()) {}

    /** Sets the vertex to have a given location. */
    explicit MeshVertex(Vector3 const & p)
    : position(p), normal(Vector3::zero()), color(ColorRGBA(1, 1, 1, 1)), has_precomputed_normal(false),
      normal_normalization_factor(0), quadric(DMat4::zero())
    {}

    /** Sets the vertex to have a location, normal and color. */
    MeshVertex(Vector3 const & p, Vector3 const & n, ColorRGBA const & c = ColorRGBA(1, 1, 1, 1))
    : position(p), normal(n), color(c), has_precomputed_normal(true), normal_normalization_factor(0), quadric(DMat4::zero())
    {}

    /**
     * Get the number of edges incident on the vertex. Equivalent to degree().
     *
     * @see degree();
     */
    int numEdges() const { return (int)edges.size(); }

    /**
     * Get the degree of the vertex, i.e. number of edges incident on it. Equivalent to numEdges().
     *
     * @see numEdges();
     */
    int degree() const { return (int)edges.size(); }

    /** Get the number of faces incident on the vertex. */
    int numFaces() const { return (int)faces.size(); }

    /** Get the edge from this vertex to another, if it exists, else return null. */
    Edge const * getEdgeTo(MeshVertex const * v) const
    { return const_cast<MeshVertex *>(this)->getEdgeTo(v); }

    /** Get the edge from this vertex to another, if it exists, else return null. */
    Edge * getEdgeTo(MeshVertex const * v);

    /** Check if the vertex is adjacent to a given edge. */
    bool hasEdgeTo(MeshVertex const * v) const { return getEdgeTo(v) != NULL; }

    /** Check if the edge is adjacent to a given face. */
    bool hasIncidentEdge(Edge const * edge) const
    {
      for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
        if (*ei == edge)
          return true;

      return false;
    }

    /** Check if the edge is adjacent to a given face. */
    bool hasIncidentFace(Face const * face) const
    {
      for (FaceConstIterator fi = facesBegin(); fi != facesEnd(); ++fi)
        if (*fi == face)
          return true;

      return false;
    }

    /** Get an iterator pointing to the first edge. */
    EdgeConstIterator edgesBegin() const { return edges.begin(); }

    /** Get an iterator pointing to the first edge. */
    EdgeIterator edgesBegin() { return edges.begin(); }

    /** Get an iterator pointing to the position beyond the last edge. */
    EdgeConstIterator edgesEnd() const { return edges.end(); }

    /** Get an iterator pointing to the position beyond the last edge. */
    EdgeIterator edgesEnd() { return edges.end(); }

    /** Get an iterator pointing to the first face. */
    FaceConstIterator facesBegin() const { return faces.begin(); }

    /** Get an iterator pointing to the first face. */
    FaceIterator facesBegin() { return faces.begin(); }

    /** Get an iterator pointing to the position beyond the last face. */
    FaceConstIterator facesEnd() const { return faces.end(); }

    /** Get an iterator pointing to the position beyond the last face. */
    FaceIterator facesEnd() { return faces.end(); }

    /** Check if the vertex lies on a mesh boundary. */
    bool isBoundary() const;

    /** Get the position of the vertex. */
    Vector3 const & getPosition() const { return position; }

    /** Set the position of the vertex. */
    void setPosition(Vector3 const & position_) { position = position_; }

    /** Get the normal at the vertex. */
    Vector3 const & getNormal() const { return normal; }

    /** Set the normal at the vertex. */
    void setNormal(Vector3 const & normal_) { normal = normal_; }

    /** Check if the vertex has a precomputed normal. */
    bool hasPrecomputedNormal() const { return has_precomputed_normal; }

    /**
     * Update the vertex normal by recomputing it from face data. Useful when the faces have been modified externally. Destroys
     * any prior precomputed normal.
     */
    void updateNormal();

    /** Get the color of the vertex. */
    ColorRGBA const & getColor() const { return color; }

    /** Set the color of the vertex. */
    void setColor(ColorRGBA const & color_) { color = color_; }

    /** Get the quadric error matrix for this vertex. */
    DMat4 const & getQuadric() const { return quadric; }

    /** Manually set the quadric error matrix for this vertex. */
    void setQuadric(DMat4 const & q) { quadric = q; }

    /** Recompute the quadric error matrix for this vertex. */
    void updateQuadric();

  private:
    friend class Mesh;

    /** Add a reference to an edge incident at this vertex. */
    void addEdge(Edge * edge) { edges.push_back(edge); }

    /** Remove a reference to an edge incident at this vertex. */
    EdgeIterator removeEdge(EdgeIterator loc) { return edges.erase(loc); }

    /** Remove a reference to an edge incident at this vertex. */
    void removeEdge(Edge * edge)
    {
      for (EdgeIterator ei = edgesBegin(); ei != edgesEnd(); )
      {
        if (*ei == edge)
          ei = edges.erase(ei);
        else
          ++ei;
      }
    }

    /** Replace all references to an edge with references to another edge. */
    void replaceEdge(Edge * old_edge, Edge * new_edge)
    {
      for (EdgeIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
        if (*ei == old_edge)
          *ei = new_edge;
    }

    /** Add a reference to a face incident at this vertex. */
    void addFace(Face * face, bool update_normal = true);

    /** Remove all references to a face incident at this vertex. */
    void removeFace(Face * face);

    /** Replace all references to a face with references to another face. */
    void replaceFace(Face * old_face, Face * new_face)
    {
      for (FaceIterator fi = facesBegin(); fi != facesEnd(); ++fi)
        if (*fi == old_face)
          *fi = new_face;
    }

    /**
     * Add (accumulate) normal information from a new face at this vertex, unless the vertex has a precomputed normal.
     *
     * @param n Unit (or weighted) normal of the new face.
     */
    void addFaceNormal(Vector3 const & n)
    {
      if (!has_precomputed_normal)
      {
        Vector3 sum_normals = normal_normalization_factor * getNormal() + n;
        normal_normalization_factor = sum_normals.length();
        setNormal(normal_normalization_factor < 1e-20f ? Vector3::zero() : sum_normals / normal_normalization_factor);
      }
    }

    /**
     * Remove (subtract) normal information from a new face at this vertex, unless the vertex has a precomputed normal.
     *
     * @param n Unit (or weighted) normal of the face to be removed.
     */
    void removeFaceNormal(Vector3 const & n)
    {
      if (!has_precomputed_normal)
      {
        Vector3 sum_normals = normal_normalization_factor * getNormal() - n;
        normal_normalization_factor = sum_normals.length();
        setNormal(normal_normalization_factor < 1e-20f ? Vector3::zero() : sum_normals / normal_normalization_factor);
      }
    }

    Vector3 position;
    Vector3 normal;
    ColorRGBA color;
    EdgeList edges;
    FaceList faces;
    bool has_precomputed_normal;
    float normal_normalization_factor;

    // Quadric error-specific
    DMat4 quadric;

}; // class MeshVertex

#endif
