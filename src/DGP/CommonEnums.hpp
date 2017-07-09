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

#ifndef __DGP_CommonEnums_hpp__
#define __DGP_CommonEnums_hpp__

#include "Platform.hpp"
#include "EnumClass.hpp"
#include "NumericTypes.hpp"

namespace DGP {

/** %Endianness values (little-endian and big-endian) (enum class). Also has a function to check the machine endianness. */
struct DGP_API Endianness
{
  /** Supported values. */
  enum Value
  {
    BIG,
    LITTLE
  };

  DGP_ENUM_CLASS_BODY(Endianness)

  DGP_ENUM_CLASS_STRINGS_BEGIN(Endianness)
    DGP_ENUM_CLASS_STRING(BIG,    "big-endian")
    DGP_ENUM_CLASS_STRING(LITTLE, "little-endian")
  DGP_ENUM_CLASS_STRINGS_END(Endianness)

  /** Get the machine endian-ness. */
  static Endianness machine()
  {
    union
    {
      uint32 i;
      char c[4];
    } b = { 0x01020304 };

    return (b.c[0] == 1 ? BIG : LITTLE);
  }
};

} // namespace DGP

#endif
