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

#ifndef __DGP_MatrixInvert_hpp__
#define __DGP_MatrixInvert_hpp__

// Direct element access via operator()
#define DGP_INVERT_MATRIX_FN              invertMatrix
#define DGP_INVERT_MATRIX_TEMPLATE_TYPE   MatrixT
#define DGP_INVERT_MATRIX_TYPE            MatrixT
#define DGP_MATRIX_GET(m, r, c)           (m)((r), (c))
#define DGP_MATRIX_GET_MUTABLE(m, r, c)   (m)((r), (c))
#define DGP_MATRIX_SET(m, r, c, v)        (m)((r), (c)) = (v)

#include "MatrixInvertTmpl.hpp"

#undef DGP_MATRIX_SET
#undef DGP_MATRIX_GET_MUTABLE
#undef DGP_MATRIX_GET
#undef DGP_INVERT_MATRIX_TYPE
#undef DGP_INVERT_MATRIX_TEMPLATE_TYPE
#undef DGP_INVERT_MATRIX_FN

// Virtual get/set accessors
#define DGP_INVERT_MATRIX_FN              invertAddressableMatrix
#define DGP_INVERT_MATRIX_TEMPLATE_TYPE   T
#define DGP_INVERT_MATRIX_TYPE            AddressableMatrix<T>
#define DGP_MATRIX_GET(m, r, c)           (m).get((r), (c))
#define DGP_MATRIX_GET_MUTABLE(m, r, c)   (m).getMutable((r), (c))
#define DGP_MATRIX_SET(m, r, c, v)        (m).set((r), (c), (v))

#include "MatrixInvertTmpl.hpp"

#undef DGP_MATRIX_SET
#undef DGP_MATRIX_GET_MUTABLE
#undef DGP_MATRIX_GET
#undef DGP_INVERT_MATRIX_TYPE
#undef DGP_INVERT_MATRIX_TEMPLATE_TYPE
#undef DGP_INVERT_MATRIX_FN

#endif
