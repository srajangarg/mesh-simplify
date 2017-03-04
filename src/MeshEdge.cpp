#include "MeshEdge.hpp"
#include "MeshFace.hpp"
#include "MeshVertex.hpp"
#include "DGP/Vector4.hpp"

MeshEdge *
MeshEdge::nextAroundEndpoint(int i)
{
  debugAssertM(i == 0 || i == 1, "MeshEdge: Invalid endpoint index");

  if (numFaces() > 2)  // non-manifold
    return NULL;

  // Find which incident face has this endpoint as the origin of the edge when stepping round the face. The required edge
  // is then the predecessor of this edge around the face.
  for (FaceIterator fi = facesBegin(); fi != facesEnd(); ++fi)
  {
    Face * face = *fi;
    MeshEdge * prev = face->getPredecessor(this);
    if (prev->hasEndpoint(endpoints[i]))  // found it!
      return prev;
  }

  return NULL;
}

void
MeshEdge::updateQuadricCollapseError()
{
  // TODO

  // Update both quadric_collapse_error and quadric_collapse_position, using the existing endpoint quadrics and the method of
  // Garland/Heckbert.
  //
  // NOTE: Remember to check if the quadric Q' is invertible. If not, you will have to use a fallback option such as the
  // midpoint of the edge (or in the worst case, set the error to a negative value to indicate this edge should not be
  // collapsed).
}
