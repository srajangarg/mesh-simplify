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
  // Update both quadric_collapse_error and quadric_collapse_position, using the existing endpoint quadrics and the method of
  // Garland/Heckbert.
  //
  // NOTE: Remember to check if the quadric Q' is invertible. If not, you will have to use a fallback option such as the
  // midpoint of the edge (or in the worst case, set the error to a negative value to indicate this edge should not be
  // collapsed).

  DMat4 q = endpoints[0]->getQuadric() + endpoints[1]->getQuadric();

  DMat4 w(q(0,0), q(0,1), q(0,2), q(0,3),
          q(0,1), q(1,1), q(1,2), q(1,3),
          q(0,2), q(1,2), q(2,2), q(2,3),
          0     , 0     , 0     , 1);

  Vector4 v;
  if (w.determinant() > 1e-3)
  {
    v = w.inverse() * Vector4(0, 0, 0, 1);
  }
  else
  {
    v = Vector4(endpoints[0]->getPosition() + endpoints[1]->getPosition()/2.0, 1);
  }

  quadric_collapse_position = Vector3(v[0], v[1], v[2]);
  quadric_collapse_error = v.dot((q * v));
}
