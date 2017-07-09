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

#ifndef __DGP_TransposedMatrix_hpp__
#define __DGP_TransposedMatrix_hpp__

#include "AddressableMatrix.hpp"

namespace DGP {

/**
 * A matrix class that acts as the transpose of another matrix, without actually copying data. An object of this class holds a
 * pointer to another addressable matrix. Element (r, c) of this matrix corresponds to element (c, r) of the wrapped matrix. The
 * wrapped matrix must persist until this matrix is destroyed.
 */
template <typename T>
class /* DGP_API */ TransposedMatrix : public AddressableMatrix<T>
{
  public:
    /** Constructor. Stores the passed pointer to a matrix, which should remain valid until this object is destroyed. */
    TransposedMatrix(AddressableMatrix<T> * m_) : m(m_)
    {
      alwaysAssertM(m_, "TransposedMatrix: The wrapped matrix must exist");
    }

    long numRows() const { return m->numColumns(); }
    long numColumns() const { return m->numRows(); }

    T const & get(long row, long col) const { return m->get(col, row); }
    T & getMutable(long row, long col) { return m->getMutable(col, row); }
    void set(long row, long col, T const & value) { m->set(col, row, value); }

  private:
    AddressableMatrix<T> * m;

}; // class TransposedMatrix

} // namespace DGP

#endif
