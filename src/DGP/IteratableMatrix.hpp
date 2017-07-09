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

#ifndef __DGP_IteratableMatrix_hpp__
#define __DGP_IteratableMatrix_hpp__

#include "BasicMatrix.hpp"

namespace DGP {

/**
 * Base class for a 2D matrix with an iterator that visits (at least) all the non-zero entries in the matrix. The iterator
 * is assumed to be read-only, and <b>cannot</b> in general be used to change the visited elements. Any class that inherits this
 * should have the following members.
 *
 * \code
 *  // Supporting types
 *  typedef std::pair<integer-type, integer-type> IndexPair;  ///< A (row, column) index pair.
 *  typedef std::pair<IndexPair, T> Entry;  ///< An entry in the matrix, mapping a (row, column) pair to a value.
 *
 *  // Read-only iterator
 *  typedef <type> ConstIterator;
 *
 *  // Access the beginning and end of the matrix
 *  ConstIterator begin() const;
 *  ConstIterator end() const;
 * \endcode
 *
 * <tt>ConstIterator</tt> should dereference to Entry.
 */
template <typename T>
class /* DGP_API */ IteratableMatrix : public virtual BasicMatrix<T>
{
  private:
    typedef BasicMatrix<T> BaseType;

  public:
}; // class IteratableMatrix

} // namespace DGP

#endif
