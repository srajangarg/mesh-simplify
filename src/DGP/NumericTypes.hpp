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

#ifndef __DGP_NumericTypes_hpp__
#define __DGP_NumericTypes_hpp__

#include "Platform.hpp"
#include <cstddef>
#include <cstdint>

namespace DGP {

typedef  std::int8_t         int8;
typedef  std::int16_t        int16;
typedef  std::int32_t        int32;
typedef  std::int64_t        int64;

typedef  std::uint8_t        uint8;
typedef  std::uint16_t       uint16;
typedef  std::uint32_t       uint32;
typedef  std::uint64_t       uint64;

using    std::               size_t;

typedef  float               Real;
typedef  float               float32;  // assume IEEE 754
typedef  double              float64;  // assume IEEE 754

} // namespace DGP

#endif
