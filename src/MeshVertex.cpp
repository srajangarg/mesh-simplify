#include "MeshVertex.hpp"
#include "MeshEdge.hpp"
#include "MeshFace.hpp"

void
MeshVertex::updateQuadric()
{
  quadric = DMat4::zero();
  for (FaceConstIterator fi = facesBegin(); fi != facesEnd(); ++fi)
  {
    Face const * face = *fi;
    if (face->numVertices() <= 0)
      continue;

    Vector3 abc = face->getNormal().unit();
    Real a = abc[0], b = abc[1], c = abc[2];
    Real d = -abc.dot((*face->verticesBegin())->getPosition());

    quadric += DMat4(a*a, a*b, a*c, a*d,
                     b*a, b*b, b*c, b*d,
                     c*a, c*b, c*c, c*d,
                     d*a, d*b, d*c, d*d);
  }
}

MeshEdge *
MeshVertex::getEdgeTo(MeshVertex const * v)
{
  if (v == this) return NULL;

  for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
  {
    Edge * e = *ei;
    if (e->hasEndpoint(v)) return e;
  }

  return NULL;
}

bool
MeshVertex::isBoundary() const
{
  if (edges.empty()) return true;

  for (EdgeConstIterator ei = edgesBegin(); ei != edgesEnd(); ++ei)
    if ((*ei)->isBoundary()) return true;

  return false;
}

void
MeshVertex::addFace(Face * face, bool update_normal)
{
  faces.push_back(face);
  if (update_normal && !has_precomputed_normal)
    addFaceNormal(face->getNormal());
}

void
MeshVertex::removeFace(Face * face)
{
  for (FaceIterator fi = facesBegin(); fi != facesEnd(); )
  {
    if (*fi == face)
    {
      fi = faces.erase(fi);
      if (!has_precomputed_normal) removeFaceNormal(face->getNormal());

      // Keep going, just in case the face somehow got added twice
    }
    else
      ++fi;
  }
}

void
MeshVertex::updateNormal()
{
  if (!faces.empty())
  {
    Vector3 sum_normals = Vector3::zero();
    for (FaceConstIterator fi = faces.begin(); fi != faces.end(); ++fi)
      sum_normals += (*fi)->getNormal();  // weight by face area?

    normal_normalization_factor = sum_normals.length();
    setNormal(normal_normalization_factor < 1e-20f ? Vector3::zero() : sum_normals / normal_normalization_factor);
  }
  else
  {
    setNormal(Vector3::zero());
    normal_normalization_factor = 0;
  }

  has_precomputed_normal = false;
}
