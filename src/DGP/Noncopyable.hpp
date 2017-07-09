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

#ifndef __DGP_Noncopyable_hpp__
#define __DGP_Noncopyable_hpp__

#include "Platform.hpp"

namespace DGP {

/**
 * A base class for objects that should never be copied. This is achieved by declaring the copy constructor and assignment
 * operator as private members. <b>Never ever</b> try to refer to an object of a derived class using a Noncopyable pointer or
 * reference (in any case this seems semantically weird) -- to ensure this class has zero runtime overhead, the destructor is
 * <b>not virtual</b>.
 */
class DGP_API Noncopyable
{
  protected:
    /** Constructor. */
    Noncopyable() {}

    /** Destructor. */
    ~Noncopyable() {}

  private:
    /**
     * Hidden copy constructor. No body provided since this should never be accessible -- if a linker error occurs then
     * something is seriously wrong.
     */
    DGP_DLL_LOCAL Noncopyable(const Noncopyable &);

    /**
     * Hidden assignment operator. No body provided since this should never be accessible -- if a linker error occurs then
     * something is seriously wrong.
     */
    DGP_DLL_LOCAL Noncopyable const & operator=(Noncopyable const &);

}; // class Noncopyable

} // namespace DGP

#endif
