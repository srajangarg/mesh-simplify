#ifndef __A2_MeshFace_hpp__
#define __A2_MeshFace_hpp__

#include "Common.hpp"
#include "DGP/Colors.hpp"
#include "DGP/Vector3.hpp"
#include <list>

// Forward declarations
class MeshVertex;
class MeshEdge;

/** Face of a mesh. */
class MeshFace
{
  public:
    typedef MeshVertex  Vertex;  ///< Vertex of the mesh.
    typedef MeshEdge    Edge;    ///< Edge of the mesh.

  private:
    typedef std::list<Vertex *>  VertexList;
    typedef std::list<Edge *  >  EdgeList;

  public:
    typedef typename VertexList::iterator                VertexIterator;              ///< Iterator over vertices.
    typedef typename VertexList::const_iterator          VertexConstIterator;         ///< Const iterator over vertices.
    typedef typename VertexList::reverse_iterator        VertexReverseIterator;       ///< Reverse iterator over vertices.
    typedef typename VertexList::const_reverse_iterator  VertexConstReverseIterator;  ///< Const reverse iterator over vertices.
    typedef typename EdgeList::iterator                  EdgeIterator;                ///< Iterator over edges.
    typedef typename EdgeList::const_iterator            EdgeConstIterator;           ///< Const iterator over edges.
    typedef typename EdgeList::reverse_iterator          EdgeReverseIterator;         ///< Reverse iterator over edges.
    typedef typename EdgeList::const_reverse_iterator    EdgeConstReverseIterator;    ///< Const reverse iterator over edges.

    /** Construct with the given normal. */
    MeshFace(Vector3 const & normal_ = Vector3::zero()) : normal(normal_) {}

    /** Check if the face has a given vertex. */
    bool hasVertex(Vertex const * vertex) const
    {
      for (VertexConstIterator vi = verticesBegin(); vi != verticesEnd(); ++vi)
        if (*vi == vertex)
          return true;

      return false;
    }

    /** Check if the face has a given edge. */
    bool hasEdge(Edge const * edge) const
    {
      for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
        if (*ei == edge)
          return true;

      return false;
    }

    /** Get the predecessor of a vertex around the face. Assumes the iterator points to a valid vertex of the face. */
    Vertex const * getPredecessor(VertexConstIterator vertex) const
    {
      return const_cast<MeshFace *>(this)->getPredecessor(vertex);
    }

    /** Get the predecessor of a vertex around the face. Assumes the iterator points to a valid vertex of the face. */
    Vertex * getPredecessor(VertexConstIterator vertex)
    {
      if (vertices.empty())
        return NULL;
      else if (vertex == vertices.begin())
        return vertices.back();
      else
      {
        --vertex;
        return *vertex;
      }
    }

    /** Get the predecessor of a vertex around the face. Returns null if the vertex does not belong to the face. */
    Vertex const * getPredecessor(Vertex const * vertex) const
    {
      return const_cast<MeshFace *>(this)->getPredecessor(vertex);
    }

    /** Get the predecessor of a vertex around the face. Returns null if the vertex does not belong to the face. */
    Vertex * getPredecessor(Vertex const * vertex)
    {
      for (VertexConstIterator vi = verticesBegin(); vi != verticesEnd(); ++vi)
        if (*vi == vertex)
          return getPredecessor(vi);

      return NULL;
    }

    /** Get the successor of a vertex around the face. Assumes the iterator points to a valid vertex of the face. */
    Vertex const * getSuccessor(VertexConstIterator vertex) const
    {
      return const_cast<MeshFace *>(this)->getSuccessor(vertex);
    }

    /** Get the successor of a vertex around the face. Assumes the iterator points to a valid vertex of the face. */
    Vertex * getSuccessor(VertexConstIterator vertex)
    {
      if (vertices.empty())
        return NULL;
      else
      {
        ++vertex;
        return vertex == vertices.end() ? vertices.front() : *vertex;
      }
    }

    /** Get the successor of a vertex around the face. Returns null if the vertex does not belong to the face. */
    Vertex const * getSuccessor(Vertex const * vertex) const
    {
      return const_cast<MeshFace *>(this)->getSuccessor(vertex);
    }

    /** Get the successor of a vertex around the face. Returns null if the vertex does not belong to the face. */
    Vertex * getSuccessor(Vertex const * vertex)
    {
      for (VertexConstIterator vi = verticesBegin(); vi != verticesEnd(); ++vi)
        if (*vi == vertex)
          return getSuccessor(vi);

      return NULL;
    }

    /** Get the predecessor of an edge around the face. Assumes the iterator points to a valid edge of the face. */
    Edge const * getPredecessor(EdgeConstIterator edge) const
    {
      return const_cast<MeshFace *>(this)->getPredecessor(edge);
    }

    /** Get the predecessor of an edge around the face. Assumes the iterator points to a valid edge of the face. */
    Edge * getPredecessor(EdgeConstIterator edge)
    {
      if (edges.empty())
        return NULL;
      else if (edge == edges.begin())
        return edges.back();
      else
      {
        --edge;
        return *edge;
      }
    }

    /** Get the predecessor of an edge around the face. Returns null if the edge does not belong to the face. */
    Edge const * getPredecessor(Edge const * edge) const { return const_cast<MeshFace *>(this)->getPredecessor(edge); }

    /** Get the predecessor of an edge around the face. Returns null if the edge does not belong to the face. */
    Edge * getPredecessor(Edge const * edge)
    {
      for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
        if (*ei == edge)
          return getPredecessor(ei);

      return NULL;
    }

    /** Get the successor of an edge around the face. Assumes the iterator points to a valid edge of the face. */
    Edge const * getSuccessor(EdgeConstIterator edge) const { return const_cast<MeshFace *>(this)->getSuccessor(edge); }

    /** Get the successor of an edge around the face. Assumes the iterator points to a valid edge of the face. */
    Edge * getSuccessor(EdgeConstIterator edge)
    {
      if (edges.empty())
        return NULL;
      else
      {
        ++edge;
        return edge == edges.end() ? edges.front() : *edge;
      }
    }

    /** Get the successor of an edge around the face. Returns null if the edge does not belong to the face. */
    Edge const * getSuccessor(Edge const * edge) const { return const_cast<MeshFace *>(this)->getSuccessor(edge); }

    /** Get the successor of an edge around the face. Returns null if the edge does not belong to the face. */
    Edge * getSuccessor(Edge const * edge)
    {
      for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
        if (*ei == edge)
          return getSuccessor(ei);

      return NULL;
    }

    /** Get an iterator pointing to the first vertex. */
    VertexConstIterator verticesBegin() const { return vertices.begin(); }

    /** Get an iterator pointing to the first vertex. */
    VertexIterator verticesBegin() { return vertices.begin(); }

    /** Get an iterator pointing to the position beyond the last vertex. */
    VertexConstIterator verticesEnd() const { return vertices.end(); }

    /** Get an iterator pointing to the position beyond the last vertex. */
    VertexIterator verticesEnd() { return vertices.end(); }

    /** Get a reverse iterator pointing to the last vertex. */
    VertexConstReverseIterator verticesReverseBegin() const { return vertices.rbegin(); }

    /** Get a reverse iterator pointing to the last vertex. */
    VertexReverseIterator verticesReverseBegin() { return vertices.rbegin(); }

    /** Get a reverse iterator pointing to the position before the first vertex. */
    VertexConstReverseIterator verticesReverseEnd() const { return vertices.rend(); }

    /** Get a reverse iterator pointing to the position before the first vertex. */
    VertexReverseIterator verticesReverseEnd() { return vertices.rend(); }

    /** Get an iterator pointing to the first edge. */
    EdgeConstIterator edgesBegin() const { return edges.begin(); }

    /** Get an iterator pointing to the first edge. */
    EdgeIterator edgesBegin() { return edges.begin(); }

    /** Get an iterator pointing to the position beyond the last edge. */
    EdgeConstIterator edgesEnd() const { return edges.end(); }

    /** Get an iterator pointing to the position beyond the last edge. */
    EdgeIterator edgesEnd() { return edges.end(); }

    /** Get a reverse iterator pointing to the last edge. */
    EdgeConstReverseIterator edgesReverseBegin() const { return edges.rbegin(); }

    /** Get a reverse iterator pointing to the last edge. */
    EdgeReverseIterator edgesReverseBegin() { return edges.rbegin(); }

    /** Get a reverse iterator pointing to the position before the first edge. */
    EdgeConstReverseIterator edgesReverseEnd() const { return edges.rend(); }

    /** Get a reverse iterator pointing to the position before the first edge. */
    EdgeReverseIterator edgesReverseEnd() { return edges.rend(); }

    /** Get the number of vertices of the face. */
    int numVertices() const
    {
      debugAssertM(vertices.size() == edges.size(), "MeshFace: Numbers of edges != number of vertices");
      return (int)vertices.size();
    }

    /** Get the number of edges bordering the face. */
    int numEdges() const
    {
      debugAssertM(vertices.size() == edges.size(), "MeshFace: Numbers of edges != number of vertices");
      return (int)edges.size();
    }

    /** Check if the face is a triangle. */
    bool isTriangle() const { return  vertices.size() == 3; }

    /** Check if the face is a quad. */
    bool isQuad() const { return vertices.size() == 4; }

    /** Reverse the order in which vertices and edges wind around the face. The face normal is <b>not</b> modified. */
    void reverseWinding()
    {
      vertices.reverse();
      edges.reverse();
    }

    /** Get the face normal. */
    Vector3 const & getNormal() const { return normal; }

    /** Set the face normal. */
    void setNormal(Vector3 const & normal_) { normal = normal_; }

    /** Update the face normal by recomputing it from vertex data. */
    void updateNormal();

    /** Get the color of the face. */
    ColorRGBA const & getColor() const { return color; }

    /** Set the color of the face. */
    void setColor(ColorRGBA const & color_) { color = color_; }

    /**
     * Test if the face contains a point (which is assumed to lie on the plane of the face -- for efficiency the function does
     * <b>not</b> explicitly verify that this holds).
     */
    bool contains(Vector3 const & p) const;

  private:
    friend class Mesh;
    friend class MeshEdge;

    /** Add a reference to a vertex of this face. */
    void addVertex(Vertex * vertex) { vertices.push_back(vertex); }

    /** Remove a reference to a vertex. */
    VertexIterator removeVertex(VertexIterator loc) { return vertices.erase(loc); }

    /** Remove all references to a vertex. */
    void removeVertex(Vertex * vertex)
    {
      for (VertexIterator vi = verticesBegin(); vi != verticesEnd(); )
      {
        if (*vi == vertex)
          vi = vertices.erase(vi);
        else
          ++vi;
      }
    }

    /** Replace all references to an vertex with references to another vertex. */
    void replaceVertex(Vertex * old_vertex, Vertex * new_vertex)
    {
      for (VertexIterator vi = verticesBegin(); vi != verticesEnd(); ++vi)
        if (*vi == old_vertex)
          *vi = new_vertex;
    }

    /** Add a reference to an edge of this face. */
    void addEdge(Edge * edge) { edges.push_back(edge); }

    /** Remove a reference to an edge. */
    EdgeIterator removeEdge(EdgeIterator loc) { return edges.erase(loc); }

    /** Remove all references to an edge. */
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

    Vector3 normal;
    ColorRGBA color;
    VertexList vertices;
    EdgeList edges;

}; // class MeshFace

#endif
