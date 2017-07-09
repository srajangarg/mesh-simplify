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

#ifndef __DGP_StringAlg_hpp_
#define __DGP_StringAlg_hpp_

#include "Common.hpp"
#include "BasicStringAlg.hpp"

#ifdef DGP_WINDOWS
#  ifndef FNM_NOMATCH
#    define FNM_NOMATCH         1      /* Match failed. */
#    define FNM_NOESCAPE     0x01      /* Disable backslash escaping. */
#    define FNM_PATHNAME     0x02      /* Slash must be matched by slash. */
#    define FNM_PERIOD       0x04      /* Period must be matched by period. */
#    define FNM_LEADING_DIR  0x08      /* Ignore /<tail> after Imatch. */
#    define FNM_CASEFOLD     0x10      /* Case insensitive search. */
#  endif
#else  // On non-windows systems, include fnmatch directly. Both GNU/Linux and OS X support all the flags above.
#  include <fnmatch.h>
#endif

namespace DGP {

/**
 * Separates a comma-separated line, properly escaping commas within double quotes (") and super quotes ("""). This matches
 * Microsoft Excel's CSV output.
 *
 * @param s The string to parse.
 * @param array The comma-separated fields are stored here.
 * @param strip_quotes If true, strips leading and trailing " and """.
 *
 * @see stringSplit, TextInput
 */
DGP_API void parseCommaSeparated(std::string const & s, std::vector<std::string> & array, bool strip_quotes = true);

/**
 * Split a string at each occurrence of a splitting character.
 *
 * @param s The string to split.
 * @param split_char The delimiting character.
 * @param result Used to return the sequence of fields found.
 * @param skip_empty_fields If true, a sequence of delimiters is treated as a single delimiter.
 *
 * @return The number of fields found.
 */
DGP_API long stringSplit(std::string const & s, char split_char, std::vector<std::string> & result,
                         bool skip_empty_fields = false);

/**
 * Split a string at each occurrence of any splitting character from a provided set.
 *
 * @param s The string to split.
 * @param split_chars The set of delimiting characters. E.g. to split a string on whitespace, use
 *   <tt>split_chars = " \t\n\f\r"</tt>.
 * @param result Used to return the sequence of fields found.
 * @param skip_empty_fields If true, a sequence of delimiters is treated as a single delimiter.
 *
 * @return The number of fields found.
 */
DGP_API long stringSplit(std::string const & s, std::string const & split_chars, std::vector<std::string> & result,
                         bool skip_empty_fields = false);

/** Concatenate a sequence of strings, separated by a joining character. */
DGP_API std::string stringJoin(std::vector<std::string> const  & a, char join_char);

/** Concatenate a sequence of strings, separated by a joining string. */
DGP_API std::string stringJoin(std::vector<std::string> const & a, std::string const & join_str);

/** Pattern matching flags (enum class). Correspond to flags for POSIX fnmatch. */
struct DGP_API Match
{
  /** Supported values. */
  enum Value
  {
    /** Treat backslash as an ordinary character, instead of an escape character. */
    NOESCAPE     =  FNM_NOESCAPE,

    /**
     * Match a slash in the query only with a slash in the pattern and not by an asterisk (*) or a question mark (?)
     * metacharacter, nor by a bracket expression ([]) containing a slash.
     */
    PATHNAME     =  FNM_PATHNAME,

    /**
     * A leading period in the query has to be matched exactly by a period in the pattern. A period is considered to be leading
     * if it is the first character in \a query, or if both FNM_PATHNAME is set and the period immediately follows a slash.
     */
    PERIOD       =  FNM_PERIOD,

    /**
     * If this flag (a GNU extension) is set, the pattern is considered to be matched if it matches an initial segment of the
     * query which is followed by a slash. This flag is mainly for the internal use of glibc and is only implemented in certain
     * cases.
     */
    LEADING_DIR  =  FNM_LEADING_DIR,

    /** If this flag (a GNU extension) is set, the pattern is matched case-insensitively. */
    CASEFOLD     =  FNM_CASEFOLD
  };

  DGP_ENUM_CLASS_BODY(Match)

}; // struct Match

/**
 * Compares a filename or pathname to a pattern. Equivalent (except for boolean instead of integer return value) to function
 * fnmatch() as specified in POSIX 1003.2-1992, section B.6.
 *
 * The function checks whether the \a query argument matches the \a pattern argument, which is a shell wildcard pattern. The
 * \a flags argument modifies the behaviour; it is the bitwise OR of zero or more Match flags.
 *
 * @return True if \a query matches \a pattern, false otherwise. Throws an error if the pattern is malformed.
 */
DGP_API bool patternMatch(std::string const & pattern, std::string const & query, int flags = 0);

} // namespace DGP

#endif
