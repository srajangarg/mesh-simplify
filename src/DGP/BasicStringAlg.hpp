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

/*
 ORIGINAL HEADER

 @file stringutils.h

 @maintainer Morgan McGuire, http://graphics.cs.williams.edu

 @author  2000-09-09
 @edited  2010-03-05
*/

#ifndef __DGP_BasicStringAlg_hpp_
#define __DGP_BasicStringAlg_hpp_

#include "Platform.hpp"
#include <cctype>
#include <cstdarg>
#include <string>

namespace DGP {

/** The newline character sequence for the current platform. LF for Unix (Linux, Mac OS X), CR-LF for Windows. */
extern DGP_API char const * NEWLINE;

/**
 * Finds the index of the first '\\' or '/' character, starting at index \a start.
 *
 * @return The index of the first slash if one is found, else a negative number.
 *
 * @see findLastSlash, isSlash
 */
inline long
findFirstSlash(std::string const & f, long start = 0)
{
  size_t pos = f.find_first_of("/\\", (size_t)start);
  return (pos == std::string::npos ? -1 : (long)pos);
}

/**
 * Finds the index of the last '\\' or '/' character, starting at index \a start (starts at the end of the string if \a start is
 * negative).
 *
 * @return The index of the last slash if one is found, else a negative number.
 *
 * @see findFirstSlash, isSlash
 */
inline long
findLastSlash(std::string const & f, long start = -1)
{
  if (start == -1)
    start = (long)f.length() - 1;

  size_t pos = f.find_last_of("/\\", (size_t)start);
  return (pos == std::string::npos ? -1 : (long)pos);
}

/** Check if the test string begins with the pattern string. */
DGP_API bool beginsWith(std::string const & test, std::string const & pattern);

/** Check if the test string ends with the pattern string. */
DGP_API bool endsWith(std::string const & test, std::string const & pattern);

/**
 * Produces a new string that is the input string wrapped at a certain number of columns (where the line is broken at the latest
 * space before the column limit). Platform specific newlines are inserted to wrap, or a specific "newline" character may be
 * specified.
 */
DGP_API std::string wordWrap(std::string const & input, long num_cols, char const * newline = NEWLINE);

/** Get the uppercase version of a string. */
DGP_API std::string toUpper(std::string const & s);

/** Get the lowercase version of a string. */
DGP_API std::string toLower(std::string const & s);

/** Strips whitespace from both ends of the string. */
DGP_API std::string trimWhitespace(std::string const & s);

/** Check if a character is a whitespace character. */
inline bool
isWhitespace(char c)
{
  return std::isspace(c) != 0;
}

/** Check if a character is a newline character. */
inline bool
isNewline(char c)
{
  return (c == '\n') || (c == '\r');
}

/** Check if a character is a digit. */
inline bool
isDigit(char c)
{
  return std::isdigit(c) != 0;
}

/** Check if a character is a letter of the alphabet. */
inline bool
isAlpha(char c)
{
  return std::isalpha(c) != 0;
}

/** Check if a character is a slash (forward or backward). */
inline bool
isSlash(char c)
{
  return (c == '\\') || (c == '/');
}

/** Check if a character is a quote (single or double). */
inline bool
isQuote(char c)
{
  return (c == '\'') || (c == '\"');
}

#ifdef __GNUC__
#  define DGP_CHECK_PRINTF_ARGS   __attribute__((__format__(__printf__, 1, 2)))
#  define DGP_CHECK_VPRINTF_ARGS  __attribute__((__format__(__printf__, 1, 0)))
#else
#  define DGP_CHECK_PRINTF_ARGS
#  define DGP_CHECK_VPRINTF_ARGS
#endif

/**
 * Produces a string from arguments in the style of printf. This avoids problems with buffer overflows when using sprintf and
 * makes it easy to use the result functionally.  This function is fast when the resulting string is under 160 characters (not
 * including terminator) and slower when the string is longer.
 */
DGP_API std::string __cdecl format(char const * fmt, ...) DGP_CHECK_PRINTF_ARGS;

/**
 * Produces a string from arguments in the style of printf, can be called with the argument list from a function that itself
 * takes variable arguments. This avoids problems with buffer overflows when using sprintf and makes it easy to use the result
 * functionally.  This function is fast when the resulting string is under 160 characters (not including terminator) and slower
 * when the string is longer.
 */
DGP_API std::string vformat(char const * fmt, va_list arg_ptr) DGP_CHECK_VPRINTF_ARGS;

#undef DGP_CHECK_PRINTF_ARGS
#undef DGP_CHECK_VPRINTF_ARGS

} // namespace DGP

#endif
