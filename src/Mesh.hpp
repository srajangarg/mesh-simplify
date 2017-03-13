#ifndef __A2_Mesh_hpp__
#define __A2_Mesh_hpp__

#include "Common.hpp"
#include "DGP/Graphics/RenderSystem.hpp"
#include "DGP/AxisAlignedBox3.hpp"
#include "DGP/Colors.hpp"
#include "DGP/NamedObject.hpp"
#include "DGP/Noncopyable.hpp"
#include "DGP/Vector3.hpp"
#include "MeshFace.hpp"
#include "MeshVertex.hpp"
#include "MeshEdge.hpp"
#include <list>
#include <type_traits>
#include <vector>
#include <set>

/** A class for storing meshes with arbitrary topologies. */
class Mesh : public virtual NamedObject, private Noncopyable
{
  public:
    typedef MeshVertex Vertex;  ///< Vertex of the mesh.
    typedef MeshEdge Edge;      ///< Edge of the mesh.
    typedef MeshFace Face;      ///< Face of the mesh.

  private:
    typedef std::list<Vertex>  VertexList;
    typedef std::list<Edge>    EdgeList;
    typedef std::list<Face>    FaceList;

  public:
    typedef typename VertexList::iterator        VertexIterator;       ///< Iterator over vertices.
    typedef typename VertexList::const_iterator  VertexConstIterator;  ///< Const iterator over vertices.
    typedef typename EdgeList::iterator          EdgeIterator;         ///< Iterator over edges.
    typedef typename EdgeList::const_iterator    EdgeConstIterator;    ///< Const iterator over edges.
    typedef typename FaceList::iterator          FaceIterator;         ///< Iterator over faces.
    typedef typename FaceList::const_iterator    FaceConstIterator;    ///< Const iterator over faces.

    /** Constructor. */
    Mesh(std::string const & name = "AnonymousMesh") : NamedObject(name) {}

    /** Get an iterator pointing to the first vertex. */
    VertexConstIterator verticesBegin() const { return vertices.begin(); }

    /** Get an iterator pointing to the first vertex. */
    VertexIterator verticesBegin() { return vertices.begin(); }

    /** Get an iterator pointing to the position beyond the last vertex. */
    VertexConstIterator verticesEnd() const { return vertices.end(); }

    /** Get an iterator pointing to the position beyond the last vertex. */
    VertexIterator verticesEnd() { return vertices.end(); }

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

    /** Deletes all data in the mesh. */
    void clear()
    {
      vertices.clear();
      edges.clear();
      faces.clear();
      bounds = AxisAlignedBox3();
    }

    /** True if and only if the mesh contains no objects. */
    bool isEmpty() const { return vertices.empty() && faces.empty() && edges.empty(); }

    /** Get the number of vertices. */
    long numVertices() const { return (long)vertices.size(); };

    /** Get the number of edges. */
    long numEdges() const { return (long)edges.size(); };

    /** Get the number of faces. */
    long numFaces() const { return (long)faces.size(); };

    /**
     * Add a vertex to the mesh, with a given location.
     *
     * @return A pointer to the newly created vertex on success, null on failure.
     */
    Vertex * addVertex(Vector3 const & point)
    {
      vertices.push_back(Vertex(point));
      bounds.merge(point);
      return &vertices.back();
    }

    /**
     * Add a vertex to the mesh, with precomputed normal and color.
     *
     * @return A pointer to the newly created vertex on success, null on failure.
     */
    Vertex * addVertex(Vector3 const & point, Vector3 const & normal, ColorRGBA const & color = ColorRGBA(1, 1, 1, 1))
    {
      vertices.push_back(Vertex(point, normal, color));
      bounds.merge(point);
      return &vertices.back();
    }

    /**
     * Add a face to the mesh, specified by the sequence of vertices obtained by dereferencing [vbegin, vend).
     * VertexInputIterator must dereference to a pointer to a Vertex. Unless the mesh is already in an inconsistent state,
     * failure to add the face will not affect the mesh.
     *
     * @return A pointer to the newly created face, or null on error.
     */
    template <typename VertexInputIterator>
    Face * addFace(VertexInputIterator vbegin, VertexInputIterator vend)
    {
      // Check for errors and compute normal
      size_t num_verts = 0;
      Vector3 v[3];
      for (VertexInputIterator vi = vbegin; vi != vend; ++vi, ++num_verts)
      {
        debugAssertM(*vi, getNameStr() + ": Null vertex pointer specified for new face");
        if (num_verts < 3) v[num_verts] = (*vi)->getPosition();
      }

      if (num_verts < 3)
      {
        DGP_WARNING << getName() << ": Skipping face -- too few vertices (" << num_verts << ')';
        return NULL;
      }

      // Create the (initially empty) face
      faces.push_back(Face());
      Face * face = &(*faces.rbegin());

      // Add the loop of vertices to the face
      VertexInputIterator next = vbegin;
      for (VertexInputIterator vi = next++ ; vi != vend; ++vi, ++next)
      {
        if (next == vend) next = vbegin;

        face->addVertex(*vi);
        (*vi)->addFace(face, false);  // we'll update the normals later

        Edge * edge = (*vi)->getEdgeTo(*next);
        if (!edge)
        {
          edges.push_back(Edge(*vi, *next));
          edge = &(*edges.rbegin());

          (*vi)->addEdge(edge);
          (*next)->addEdge(edge);
        }

        edge->addFace(face);
        face->addEdge(edge);
      }

      // Update the face and vertex normals;
      face->updateNormal();
      for (typename Face::VertexIterator fvi = face->verticesBegin(); fvi != face->verticesEnd(); ++fvi)
        (*fvi)->addFaceNormal(face->getNormal());  // weight by face area?

      return face;
    }

    /**
     * Remove a face of the mesh. This does NOT remove any vertices or edges. Iterators to the face list remain valid unless the
     * iterator pointed to the removed face.
     *
     * This is a relatively slow operation since the face needs to be looked up in the face list
     * (linear in number of faces). For speed, use removeFace(FaceIterator).
     *
     * @return True if the face was found and removed, else false.
     */
    bool removeFace(Face * face)
    {
      for (FaceIterator fi = faces.begin(); fi != faces.end(); ++fi)
        if (&(*fi) == face)
          return removeFace(fi);

      return false;
    }

    /**
     * Remove a face of the mesh. This does NOT remove any vertices or edges. Iterators to the face list remain valid unless the
     * iterator pointed to the removed face.
     *
     * Use this version in preference to removeFace(Face const *) where possible.
     *
     * @return True if the face was found and removed, else false.
     */
    bool removeFace(FaceIterator face)
    {
      Face * fp = &(*face);

      for (typename Face::VertexIterator fvi = face->vertices.begin(); fvi != face->vertices.end(); ++fvi)
        (*fvi)->removeFace(fp);

      for (typename Face::EdgeIterator fei = face->edges.begin(); fei != face->edges.end(); ++fei)
        (*fei)->removeFace(fp);

      faces.erase(face);

      return true;
    }

    /**
     * Collapse an edge to one of its endpoints. The choice of endpoint is arbitrary. The collapsed edge and discarded endpoint
     * are completely removed from the mesh, and all relevant pointers in all adjacent elements are updated.
     *
     * @param edge The edge to collapse.
     *
     * @return The retained endpoint.
     */
    Vertex * collapseEdge(Edge * edge);

    /**
     * Decimate the mesh by collapsing a single edge, identified using a quadric error metric, as described in the
     * Garland/Heckbert paper. Assumes all vertices have had their quadrics initialized, and all edges their collapse errors and
     * positions initialized in advance (e.g. by load()).
     *
     * @return The vertex to which the edge has been collapsed.
     */
    Vertex * decimateQuadricEdgeCollapse();

    /**
     * Decimate the mesh to a target number of faces, using edge collapse decimation with a quadric error metric, as described
     * in the Garland/Heckbert paper. Assumes all vertices have had their quadrics initialized, and all edges their collapse
     * errors and positions initialized in advance (e.g. by load()).
     */
    void decimateQuadricEdgeCollapse(long target_num_faces);

    /** Draw the mesh on a render_system. */
    void draw(Graphics::RenderSystem & render_system, bool draw_edges = false, bool use_vertex_data = false,
              bool send_colors = false) const;

    /** Update the bounding box of the mesh. */
    void updateBounds()
    {
      bounds = AxisAlignedBox3();
      for (VertexConstIterator vi = verticesBegin(); vi != verticesEnd(); ++vi)
        bounds.merge(vi->getPosition());
    }

    /** Get the bounding box of the mesh. */
    AxisAlignedBox3 const & getAABB() const { return bounds; }

    /** Load the mesh from a disk file. */
    bool load(std::string const & path);

    /** Save the mesh to a disk file. */
    bool save(std::string const & path) const;

  private:
    /**
     * Utility function to draw a face. Must be enclosed in the appropriate
     * RenderSystem::beginPrimitive()/RenderSystem::endPrimitive() block.
     */
    void drawFace(Face const & face, Graphics::RenderSystem & render_system, bool use_vertex_data, bool send_colors) const
    {
      if (!use_vertex_data)
      {
        render_system.setNormal(face.getNormal());
        if (send_colors) render_system.setColor(face.getColor());
      }

      for (typename Face::VertexConstIterator vi = face.verticesBegin(); vi != face.verticesEnd(); ++vi)
      {
        Vertex const & vertex = **vi;

        if (use_vertex_data)
        {
          render_system.setNormal(vertex.getNormal());
          if (send_colors) render_system.setColor(vertex.getColor());
        }

        render_system.sendVertex(vertex.getPosition());
      }
    }

    struct EdgeComp
    {
      bool operator()(const Edge* lhs, const Edge* rhs) const
      {
        return lhs->getQuadricCollapseError() < rhs->getQuadricCollapseError();
      }
    };

    void remove_from_heap(std::multiset<Edge*, EdgeComp>& eh, Edge* e);

    /** If two edges of the mesh have the same endpoints, merge them into a single edge, which is returned by the function. */
    Edge * mergeEdges(Edge * e0, Edge * e1);

    /** Load the mesh from an OFF file. */
    bool loadOFF(std::string const & path);

    /** Save the mesh to an OFF file. */
    bool saveOFF(std::string const & path) const;

    FaceList         faces;     ///< Set of mesh faces.
    VertexList       vertices;  ///< Set of mesh vertices.
    EdgeList         edges;     ///< Set of mesh edges.
    AxisAlignedBox3  bounds;    ///< Mesh bounding box.

    mutable std::vector<Vertex *> face_vertices;  ///< Internal cache of vertex pointers for a face.

    std::multiset<Edge*, EdgeComp> edge_heap;
    bool heap_constructed = false;

}; // class Mesh

#endif
