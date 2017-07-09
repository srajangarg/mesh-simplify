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

#ifndef __DGP_BasicMatrix_hpp__
#define __DGP_BasicMatrix_hpp__

#include "Common.hpp"

namespace DGP {

/** %Matrix layouts (enum class). */
struct DGP_API MatrixLayout
{
  /** Supported values. */
  enum Value
  {
    ROW_MAJOR,    ///< Row-major layout.
    COLUMN_MAJOR  ///< Column-major layout.
  };

  DGP_ENUM_CLASS_BODY(MatrixLayout)
};

/** Basic interface for a 2D matrix. */
template <typename T>
class /* DGP_API */ BasicMatrix
{
  public:
    typedef T Value;  ///< Type of values stored in the matrix.
    typedef T value_type;  ///< Type of values stored in the matrix (STL convention).

    /** Destructor. */
    virtual ~BasicMatrix() {}

    /** Get the number of rows. */
    virtual long numRows() const = 0;

    /** Get the number of columns. */
    virtual long numColumns() const = 0;

    /** Set all elements to zero. */
    virtual void makeZero() = 0;

    /** Check if the matrix has non-zero size or not. */
    bool isEmpty() const { return numRows() <= 0 || numColumns() <= 0; }

    /** Check if the matrix is square or not. */
    bool isSquare() const { return numRows() == numColumns(); }

}; // class BasicMatrix

} // namespace DGP

#endif
