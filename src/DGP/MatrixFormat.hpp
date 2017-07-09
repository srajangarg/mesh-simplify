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

#ifndef __DGP_MatrixFormat_hpp__
#define __DGP_MatrixFormat_hpp__

#include "Common.hpp"

namespace DGP {

/** %Matrix format (enum class). */
struct DGP_API MatrixFormat
{
  /** Supported values. */
  enum Value
  {
    UNKNOWN,              ///< Unknown matrix format.
    DENSE_ROW_MAJOR,      ///< Dense row-major format.
    DENSE_COLUMN_MAJOR,   ///< Dense column-major format.
    SPARSE_ROW_MAJOR,     ///< Sparse row-major format.
    SPARSE_COLUMN_MAJOR,  ///< Sparse column-major format.
  };

  DGP_ENUM_CLASS_BODY(MatrixFormat)
};

} // namespace DGP

#endif
