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

#ifndef __DGP_RayIntersectable3_hpp__
#define __DGP_RayIntersectable3_hpp__

#include "Common.hpp"
#include "RayIntersectableN.hpp"

namespace DGP {

// The default ray intersection class in real 3-space.
typedef RayIntersectionN<3, Real> RayIntersection3;

// The default ray intersectable interface in real 3-space.
typedef RayIntersectableN<3, Real> RayIntersectable3;

} // namespace DGP

#endif
