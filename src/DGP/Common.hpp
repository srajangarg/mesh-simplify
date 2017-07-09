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

#ifndef __DGP_Common_hpp__
#define __DGP_Common_hpp__

#include "Platform.hpp"
#include "AtomicInt32.hpp"
#include "CommonEnums.hpp"
#include "EnumClass.hpp"
#include "Error.hpp"
#include "Log.hpp"
#include "Noncopyable.hpp"
#include "NumericTypes.hpp"
#include <cassert>
#include <cstdlib>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#if defined(__GNUC__) && __GNUC__ >= 3
#  include <cxxabi.h>
#  define DGP_HAVE_CXA_DEMANGLE
#endif

#undef debugAssertM
#ifdef DGP_DEBUG_BUILD
#  define debugAssertM(test, msg)                                                                                             \
   {                                                                                                                          \
     if (!(test))                                                                                                             \
     {                                                                                                                        \
       DGP_ERROR << "Debug-mode assertion failed: " << (msg);                                                                \
       throw DGP::FatalError(msg);                                                                                           \
     }                                                                                                                        \
   }
#else
#  define debugAssertM(test, msg) {}
#endif

#define alwaysAssertM(test, msg)                                                                                              \
   {                                                                                                                          \
     if (!(test))                                                                                                             \
     {                                                                                                                        \
       DGP_ERROR << "Assertion failed: " << (msg);                                                                           \
       throw DGP::FatalError(msg);                                                                                           \
     }                                                                                                                        \
   }

// Visual Studio requires templates instantiations to be explicitly imported from DLL's to avoid conflicts like
// http://www.codesynthesis.com/~boris/blog/2010/01/18/dll-export-cxx-templates/
#ifdef _MSC_VER
#  define DGP_EXPORT_INSTANTIATION
#endif

/** Root namespace for the %DGP library. */
namespace DGP {

/**
 * Require an expression to evaluate to true at compile-time. Example usage:
 *
 * \code
 *   DGP_STATIC_ASSERT(sizeof(int) == 2)
 * \endcode
 *
 * From Ralf Holly, http://www.drdobbs.com/compile-time-assertions/184401873
 */
#define DGP_STATIC_ASSERT(e) \
do \
{ \
  enum { assert_static__ = 1/((int)(e)) }; \
} while (0)

/** Get the class of an object. */
template <typename T>
/* DGP_API */
std::string
getClass(T const & obj)
{
  // GCC doesn't demangle type_info::name(). New versions include a demangling function in the ABI.
#ifdef DGP_HAVE_CXA_DEMANGLE

  size_t length = 1024;
  int status;

  char const * class_name = typeid(obj).name();
  char * ret = abi::__cxa_demangle(class_name, NULL, &length, &status);
  if (ret)
  {
    std::string result(ret);
    std::free(ret);
    return result;
  }
  else
  {
    std::free(ret);
    return class_name;
  }

#else

  return typeid(obj).name();

#endif
}

} // namespace DGP

// Commonly-used but requires the stuff in Common.hpp to be declared first, so is included here.
#include "StringAlg.hpp"

#endif
