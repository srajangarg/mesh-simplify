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

/**
 * \file
 * This file <b>must</b> be included in <em>every</em> file in the project, <em>before</em> any other include.
 */

#ifndef __DGP_Platform_hpp__
#define __DGP_Platform_hpp__

#define WIN32_LEAN_AND_MEAN

#if !defined(DGP_DEBUG_BUILD) && (!defined(NDEBUG) || defined(_DEBUG))
#  define DGP_DEBUG_BUILD
#endif

// NDEBUG needed for assert to be deactivated on release builds
#if !defined(DGP_DEBUG_BUILD) && !defined(NDEBUG)
#  define NDEBUG
#endif

#ifdef _MSC_VER
#  define DGP_WINDOWS 1
   // NOMINMAX required to stop windows.h messing up std::min
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif

   // Disable pesky warnings of the type: "class <member-classname> needs to have dll-interface to be used by clients of class"
   // and "non dll-interface class <subclass> used as base for dll-interface class <superclass>."
#  pragma warning( disable: 4251 )
#  pragma warning( disable: 4275 )

   // Disable numerical type conversion "possible loss of precision" warnings
#  pragma warning( disable: 4244 )

   // Disable deprecation of C/C++ standard library functions (fopen, strcpy etc)
   // TODO: A more future-proof solution would be useful.
#  define _CRT_SECURE_NO_WARNINGS
#  define _SCL_SECURE_NO_WARNINGS

#elif defined(__FreeBSD__)
#  define DGP_FREEBSD 1
#elif defined(__OpenBSD__)
#  define DGP_OPENBSD 1
#elif defined(__linux__)
#  define DGP_LINUX 1
#elif defined(__APPLE__)
#  define DGP_OSX 1
   // Prevent OS X fp.h header from being included; it defines pi as a constant, which creates a conflict with G3D
#  define __FP__
#else
#  error Unknown platform
#endif

#if defined(DGP_FREEBSD) || defined(DGP_OPENBSD)
#  define DGP_BSD 1
#endif

// http://nadeausoftware.com/articles/2012/02/c_c_tip_how_detect_processor_type_using_compiler_predefined_macros
// http://sourceforge.net/p/predef/wiki/Architectures/
#if defined(_M_X64) || defined(__x86_64__) || defined(__amd_64__)
#  define DGP_64BIT 1
#  define DGP_X64 1
#elif defined(_M_IA64) || defined(__ia64) || defined(__ia64__)
#  define DGP_64BIT 1
#  define DGP_ITANIUM 1
#elif defined(__i386) || defined(_M_IX86)
#  define DGP_32BIT 1
#  define DGP_X86 1
#elif defined(__aarch64__) || defined(__aarch64)
#  define DGP_64BIT 1
#  define DGP_ARM 1
#elif defined(_M_ARM) || defined(__arm) || defined(__arm__)
#  define DGP_32BIT 1
#  define DGP_ARM 1
#elif defined(__powerpc__) || defined(__PPC__) || defined(__POWERPC__)
#  if defined(__ppc64__) || defined(__powerpc64__) || defined(__64BIT__) || defined(_LP64)
#    define DGP_64BIT 1
#  else
#    define DGP_32BIT 1
#  endif
#  define DGP_POWERPC 1
#endif

// Symbol visibility flags
#include "SymbolVisibility.hpp"

#ifndef _MSC_VER
#  define __cdecl
#endif

/** Use tight alignment for a class. Useful for small classes that must be packed into an array. */
#ifdef _MSC_VER
#  define DGP_BEGIN_PACKED_CLASS(byte_align)  PRAGMA( pack(push, byte_align) )
#else
#  define DGP_BEGIN_PACKED_CLASS(byte_align)
#endif

/**
 * @def PRAGMA(expression)
 * \#pragma may not appear inside a macro, so this uses the pragma operator to create an equivalent statement.
 */
#ifdef _MSC_VER
// Microsoft's version http://msdn.microsoft.com/en-us/library/d9x1s805.aspx
#  define PRAGMA(x) __pragma(x)
#else
// C99 standard http://www.delorie.com/gnu/docs/gcc/cpp_45.html
#  define PRAGMA(x) _Pragma(#x)
#endif

/** Mark end of class that uses tight alignment. */
#ifdef _MSC_VER
#  define DGP_END_PACKED_CLASS(byte_align)  ; PRAGMA( pack(pop) )
#elif defined(__GNUC__)
#  define DGP_END_PACKED_CLASS(byte_align)  __attribute((aligned(byte_align))) ;
#else
#  define DGP_END_PACKED_CLASS(byte_align)  ;
#endif

#endif
