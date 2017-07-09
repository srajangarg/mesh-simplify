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

 @file ColorL.cpp

 Color class.

 @author Morgan McGuire, http://graphics.cs.williams.edu

 @created 2007-01-30
 @edited  2009-03-27
 */

#include "ColorL.hpp"
#include "ColorL8.hpp"

namespace DGP {

ColorL::ColorL(ColorL8 const & other)
: val(other.value() / 255.0f)
{}

std::string
ColorL::toString() const
{
  return format("L(%g)", val);
}

} // namespace DGP
