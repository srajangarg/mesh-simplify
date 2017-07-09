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

 @file ColorRGBA8.cpp

 @author Morgan McGuire, http://graphics.cs.williams.edu

 @created 2003-04-07
 @edited  2006-01-07
*/

#include "ColorRGBA8.hpp"
#include "ColorRGBA.hpp"
#include "Math.hpp"

namespace DGP {

ColorRGBA8::ColorRGBA8(ColorRGBA const & src)
{
  c[0] = (uint8)Math::clamp((Real)Math::round(src.r() * 255), (Real)0, (Real)255);
  c[1] = (uint8)Math::clamp((Real)Math::round(src.g() * 255), (Real)0, (Real)255);
  c[2] = (uint8)Math::clamp((Real)Math::round(src.b() * 255), (Real)0, (Real)255);
  c[3] = (uint8)Math::clamp((Real)Math::round(src.a() * 255), (Real)0, (Real)255);
}

ColorRGBA8
ColorRGBA8::fromARGB(uint32 argb)
{
  return ColorRGBA8((uint8)((argb >> 16) & 0xFF),
                    (uint8)((argb >>  8) & 0xFF),
                    (uint8)( argb        & 0xFF),
                    (uint8)((argb >> 24) & 0xFF));
}

} // namespace DGP
