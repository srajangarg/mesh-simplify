#ifndef __A2_MeshEdge_hpp__
#define __A2_MeshEdge_hpp__

#include "Common.hpp"
#include <list>

// Forward declarations
class MeshVertex;
class MeshFace;

/** Edge of a mesh. */
class MeshEdge
{
  public:
    typedef MeshVertex  Vertex;  ///< Vertex of the mesh.
    typedef MeshFace    Face;    ///< Face of the mesh.

  private:
    typedef std::list<Face *> FaceList;

  public:
    typedef typename FaceList::iterator        FaceIterator;       ///< Iterator over faces.
    typedef typename FaceList::const_iterator  FaceConstIterator;  ///< Const iterator over faces.

    /** Construct from two endpoints. */
    MeshEdge(Vertex * v0 = NULL, Vertex * v1 = NULL) : quadric_collapse_error(-1)
    {
      endpoints[0] = v0;
      endpoints[1] = v1;
    }

    /** Get an endpoint of the edge. \a i = 0 returns the first endpoint and \a i = 1 the second. */
    Vertex const * getEndpoint(int i) const
    {
      debugAssertM(i == 0 || i == 1, "MeshEdge: Invalid endpoint index");
      return endpoints[i];
    }

    /** Get an endpoint of the edge. \a i = 0 returns the first endpoint and \a i = 1 the second. */
    Vertex * getEndpoint(int i)
    {
      debugAssertM(i == 0 || i == 1, "MeshEdge: Invalid endpoint index");
      return endpoints[i];
    }

    /**
     * Given one endpoint of the edge, get the other one. This function assumes the supplied vertex is indeed a valid endpoint
     * of the edge, and (in release mode) does not check that this is so.
     */
    Vertex const * getOtherEndpoint(Vertex const * endpoint) const
    {
      debugAssertM(hasEndpoint(endpoint), "MeshEdge: Vertex is not an endpoint of the edge");
      return endpoints[0] == endpoint ? endpoints[1] : endpoints[0];
    }

    /**
     * Given one endpoint of the edge, get the other one. This function assumes the supplied vertex is indeed a valid endpoint
     * of the edge, and (in release mode) does not check that this is so.
     */
    Vertex * getOtherEndpoint(Vertex const * endpoint)
    {
      debugAssertM(hasEndpoint(endpoint), "MeshEdge: Vertex is not an endpoint of the edge");
      return endpoints[0] == endpoint ? endpoints[1] : endpoints[0];
    }

    /** Get the index (0 or 1) of an endpoint given a pointer to it, or a negative value if the neither endpoint matches. */
    int getEndpointIndex(Vertex const * endpoint) const
    {
      return endpoints[0] == endpoint ? 0 : (endpoints[1] == endpoint ? 1 : -1);
    }

    /** Check if the edge has a given vertex as an endpoint. */
    bool hasEndpoint(Vertex const * v) const { return endpoints[0] == v || endpoints[1] == v; }

    /** Check if the edge is adjacent to a given face. */
    bool hasIncidentFace(Face const * face) const
    {
      for (FaceConstIterator fi = facesBegin(); fi != facesEnd(); ++fi)
        if (*fi == face)
          return true;

      return false;
    }

    /** Check if two edges share the same endpoints. */
    bool isCoincidentTo(MeshEdge const & other) const
    {
      return (endpoints[0] == other.endpoints[0] && endpoints[1] == other.endpoints[1])
          || (endpoints[0] == other.endpoints[1] && endpoints[1] == other.endpoints[0]);
    }

    /** Check if this edge shares an endpoint with another. */
    bool isConnectedTo(MeshEdge const & other) const
    {
      return (endpoints[0] == other.endpoints[0] || endpoints[1] == other.endpoints[1]
           || endpoints[0] == other.endpoints[1] || endpoints[1] == other.endpoints[0]);
    }

    /**
     * Get the next edge when stepping counter-clockwise (when viewed from the "outside" of the mesh) around a specified
     * endpoint, assuming the neighborhood is manifold. This also assumes that face vertices/edges have consistent
     * counter-clockwise winding order when viewed from the outside. On error, returns null.
     */
    MeshEdge const * nextAroundEndpoint(int i) const
    { return const_cast<MeshEdge *>(this)->nextAroundEndpoint(i); }

    /**
     * Get the next edge when stepping counter-clockwise (when viewed from the "outside" of the mesh) around a specified
     * endpoint, assuming the neighborhood is manifold. This also assumes that face vertices/edges have consistent
     * counter-clockwise winding order when viewed from the outside. On error, returns null.
     */
    MeshEdge * nextAroundEndpoint(int i);

    /**
     * Get the next edge when stepping counter-clockwise (when viewed from the "outside" of the mesh) around a specified
     * endpoint, assuming the neighborhood is manifold. This also assumes that face vertices/edges have consistent
     * counter-clockwise winding order when viewed from the outside. On error, returns null.
     */
    MeshEdge const * nextAroundEndpoint(Vertex const * endpoint) const
    { return const_cast<MeshEdge *>(this)->nextAroundEndpoint(endpoint); }

    /**
     * Get the next edge when stepping counter-clockwise (when viewed from the "outside" of the mesh) around a specified
     * endpoint, assuming the neighborhood is manifold. This also assumes that face vertices/edges have consistent
     * counter-clockwise winding order when viewed from the outside. On error, returns null.
     */
    MeshEdge * nextAroundEndpoint(Vertex const * endpoint)
    {
      debugAssertM(hasEndpoint(endpoint), "MeshEdge: Vertex is not an endpoint of the edge");
      return nextAroundEndpoint(getEndpointIndex(endpoint));
    }

    /** Get the number of faces incident on the edge. */
    long numFaces() const { return (long)faces.size(); }

    /** Get an iterator pointing to the first face. */
    FaceConstIterator facesBegin() const { return faces.begin(); }

    /** Get an iterator pointing to the first face. */
    FaceIterator facesBegin() { return faces.begin(); }

    /** Get an iterator pointing to the position beyond the last face. */
    FaceConstIterator facesEnd() const { return faces.end(); }

    /** Get an iterator pointing to the position beyond the last face. */
    FaceIterator facesEnd() { return faces.end(); }

    /** Check if this is a boundary edge, i.e. if it is adjacent to at most one face. */
    bool isBoundary() const { return numFaces() <= 1; }

    /** Get the quadric error of collapsing this edge. */
    double getQuadricCollapseError() const { return quadric_collapse_error; }

    /** Get the optimal position to which to collapse this edge, according to a quadric error metric. */
    Vector3 const & getQuadricCollapsePosition() const { return quadric_collapse_position; }

    /**
     * Recompute the quadric error and optimal collapse position for this vertex. If these cannot be successfully calculated,
     * the error will be set to a negative value.
     */
    void updateQuadricCollapseError();

  private:
    friend class Mesh;

    /** Set an endpoint of the edge. */
    void setEndpoint(int i, Vertex * vertex)
    {
      debugAssertM(i == 0 || i == 1, "MeshEdge: Invalid endpoint index");
      endpoints[i] = vertex;
    }

    /** Replace all references to a vertex with references to another vertex. */
    void replaceVertex(Vertex * old_vertex, Vertex * new_vertex)
    {
      if (endpoints[0] == old_vertex) endpoints[0] = new_vertex;
      if (endpoints[1] == old_vertex) endpoints[1] = new_vertex;
    }

    /** Add a reference to a face incident at this vertex. */
    void addFace(Face * face) { faces.push_back(face); }

    /** Remove all references to a face incident on this edge. */
    void removeFace(Face * face)
    {
      for (FaceIterator fi = facesBegin(); fi != facesEnd(); )
      {
        if (*fi == face)
          fi = faces.erase(fi);
        else
          ++fi;
      }
    }

    /** Remove a face incident on this edge. */
    FaceIterator removeFace(FaceIterator loc) { return faces.erase(loc); }

    /** Replace all references to a face with references to another face. */
    void replaceFace(Face * old_face, Face * new_face)
    {
      for (FaceIterator fi = facesBegin(); fi != facesEnd(); ++fi)
        if (*fi == old_face)
          *fi = new_face;
    }

    /** Is the edge a self-loop (both endpoints same)? */
    bool isSelfLoop() const { return endpoints[0] == endpoints[1]; }

    Vertex * endpoints[2];
    FaceList faces;

    // Quadric error-specific
    double quadric_collapse_error;
    Vector3 quadric_collapse_position;

}; // class MeshEdge

#endif
