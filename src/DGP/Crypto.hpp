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

#ifndef __DGP_Crypto_hpp__
#define __DGP_Crypto_hpp__

#include "Common.hpp"

namespace DGP {

/** Cryptographic functions. */
class DGP_API Crypto
{
  public:
    /** Get the CRC32 hash of a sequence of bytes. */
    static uint32 crc32(void const * byte, size_t num_bytes);

}; // class Crypto

} // namespace DGP

#endif
