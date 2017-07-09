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

#ifndef __DGP_SymbolVisibility_hpp__
#define __DGP_SymbolVisibility_hpp__

// Shared library support. See http://gcc.gnu.org/wiki/Visibility . Quoting loosely from that page, and assuming M is a library-
// specific prefix:
//
// - If M_DLL and M_DLL_EXPORTS are defined, we are building our library as a DLL and symbols should be exported. Something
//   ending with _EXPORTS is defined by MSVC by default in all projects.
//
// - If M_DLL_EXPORTS is not defined, we are importing our library and symbols should be imported.
//
// - If we're building with GCC and __GNUC__ >= 4 , then GCC supports the new features.
//
// - For every non-templated non-static function definition in your library (both headers and source files), decide if it is
//   publicly used or internally used:
//
//     - If it is publicly used, mark with M_API like this: extern M_API PublicFunc()
//
//     - If it is only internally used, mark with M_DLL_LOCAL like this: extern M_DLL_LOCAL PublicFunc(). Remember, static
//       functions need no demarcation, nor does anything which is templated.
//
// - For every non-templated class definition in your library (both headers and source files), decide if it is publicly used or
//   internally used:
//
//     - If it is publicly used, mark with M_API like this: class M_API PublicClass
//
//     - If it is only internally used, mark with M_DLL_LOCAL like this: class M_DLL_LOCAL PublicClass
//
// - Individual member functions of an exported class that are not part of the interface, in particular ones which are private,
//   and are not used by friend code, should be marked individually with M_DLL_LOCAL.
//
// - Remember to test your library thoroughly afterwards, including that all exceptions correctly traverse shared object
//   boundaries.
//
#ifdef _MSC_VER  // should be WIN32?
#    define DGP_IMPORT  __declspec(dllimport)
#    define DGP_EXPORT  __declspec(dllexport)
#    define DGP_DLL_LOCAL
#    define DGP_DLL_PUBLIC
#else
#    if (defined __GNUC__ && __GNUC__ >= 4)
#        define DGP_IMPORT      __attribute__ ((visibility("default")))
#        define DGP_EXPORT      __attribute__ ((visibility("default")))
#        define DGP_DLL_LOCAL   __attribute__ ((visibility("hidden")))
#        define DGP_DLL_PUBLIC  __attribute__ ((visibility("default")))
#    else
#        define DGP_IMPORT
#        define DGP_EXPORT
#        define DGP_DLL_LOCAL
#        define DGP_DLL_PUBLIC
#    endif
#endif

// Build flags for the DGP DLL (if any).
#ifdef DGP_DLL
#    ifdef DGP_DLL_EXPORTS
#        define DGP_API  DGP_EXPORT
#    else
#        define DGP_API  DGP_IMPORT
#    endif
#else
#    define DGP_API
#endif

#endif
