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

#ifndef __DGP_ResizableMatrix_hpp__
#define __DGP_ResizableMatrix_hpp__

#include "BasicMatrix.hpp"

namespace DGP {

/** Interface for a 2D matrix whose dimensions can be changed at runtime. */
template <typename T>
class /* DGP_API */ ResizableMatrix : public virtual BasicMatrix<T>
{
  public:
    /** Resize the matrix to the specified dimensions. All existing data will be discarded. */
    virtual void resize(long num_rows, long num_cols) = 0;

}; // class ResizableMatrix

} // namespace DGP

#endif
