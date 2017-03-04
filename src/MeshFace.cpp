#include "MeshFace.hpp"
#include "MeshVertex.hpp"

void
MeshFace::updateNormal()
{
  // Assume the face is planar.
  VertexConstIterator vi2 = vertices.begin();
  VertexConstIterator vi0 = vi2++;
  VertexConstIterator vi1 = vi2++;

  if (vertices.size() > 3)
  {
    // vi1 might be a concave corner -- we need to add up the cross products at all vertices
    Vector3 sum_cross = Vector3::zero();
    for ( ; vi0 != vertices.end(); ++vi0, ++vi1, ++vi2)
    {
      if (vi1 == vertices.end()) vi1 = vertices.begin();
      if (vi2 == vertices.end()) vi2 = vertices.begin();

      Vector3 e1 = (*vi0)->getPosition() - (*vi1)->getPosition();
      Vector3 e2 = (*vi2)->getPosition() - (*vi1)->getPosition();
      sum_cross += e2.cross(e1);
    }

    setNormal(sum_cross.unit());
  }
  else
  {
    Vector3 e1 = (*vi0)->getPosition() - (*vi1)->getPosition();
    Vector3 e2 = (*vi2)->getPosition() - (*vi1)->getPosition();
    setNormal(e2.cross(e1).unit());  // counter-clockwise
  }
}

bool
MeshFace::contains(Vector3 const & p) const
{
  if (vertices.empty()) return false;

  // Generate a ray for the even-odd test, from p to the midpoint of the first halfedge. Ignore degenerate situations for
  // now.
  VertexConstIterator vi    =  verticesBegin();
  VertexConstIterator last  =  vi++;
  Vector3 u = 0.5 * ((*last)->getPosition() + (*vi)->getPosition()) - p;

  long count = 1;  // first halfedge is obviously intersected, since we generated the ray through its midpoint
  for ( ; last != verticesEnd(); ++vi)
  {
    if (vi == verticesEnd()) vi = verticesBegin();

    Vector3 v0 = (*last)->getPosition() - p;
    Vector3 v1 = (*vi)->getPosition()   - p;

    // If winding order is: vector to first vertex, ray, vector to second vertex, then intersects
    Vector3 c0 = v0.cross(u);
    Vector3 c1 = u.cross(v1);
    if (c0.dot(c1) > 0)  // intersects, now check forward or reverse
    {
      // Forward if the vector to the point nearest to p on the line containing the edge makes an acute angle with u.
      //
      // The point p' on line v + t * e closest to point p is v + t0 * e, where t0 = e.dot(p - v) / e.dot(e)
      // (see www.geometrictools.com/Documentation/DistancePointLine.pdf).
      //
      // We translate p to the origin for simpler computations.
      Vector3 edge = v1 - v0;
      Real t0 = -edge.dot(v0) / edge.dot(edge);
      Vector3 u0 = v0 + t0 * edge;

      if (u0.dot(u) > 0)
        count++;
    }

    last = vi;
  }

  return (count % 2 == 1);
}
