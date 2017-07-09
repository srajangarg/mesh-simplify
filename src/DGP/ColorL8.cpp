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

/*
 ORIGINAL HEADER

 @file ColorL8.cpp

 @author Morgan McGuire, http://graphics.cs.williams.edu

 @created 2007-01-30
 @edited  2007-01-30
 */

#include "ColorL8.hpp"
#include "ColorL.hpp"
#include "Math.hpp"

namespace DGP {

ColorL8::ColorL8(ColorL const & c)
: val((uint8)Math::clamp((Real)Math::round(c.value() * 255), (Real)0, (Real)255))
{}

std::string
ColorL8::toString() const
{
  return format("L8(%u)", val);
}

} // namespace DGP
