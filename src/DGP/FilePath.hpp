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

#ifndef __DGP_FilePath_hpp__
#define __DGP_FilePath_hpp__

#include "Common.hpp"

namespace DGP {

/**
 * Operations on file paths. These do string manipulation and do <b>not</b> actually access the filesystem.
 *
 * @note Returned paths are in native OS format (e.g. backslashes on Windows, forward slashes on Unix).
 * @note Trailing slashes at the end of directory names, and repeated slashes, are ignored, so "/foo" and "/foo/" are treated
 *   identically, as are "foo/bar" and "foo///bar". In this respect this implementation differs from, say, Boost.Filesystem.
 * @note Beware of the distinction between extensions and complete extensions (and by symmetry, complete base names and base
 *   names). "foo.old.txt" has extension "txt", complete extension "old.txt", complete base name "foo.old", and base name "foo".
 */
class DGP_API FilePath
{
  public:
    /**
     * Get the basename of the object, consisting of the object name without the path, upto but not including the <i>first</i>
     * period character. In other words, this returns \a path minus completeExtension(\a path).
     *
     * @see completeBaseName()
     */
    static std::string baseName(std::string const & path);

    /**
     * Get the complete basename of the object, consisting of the object name without the path, upto but not including the
     * <i>last</i> period character. In other words, this returns \a path minus extension(\a path).
     *
     * @see baseName()
     */
    static std::string completeBaseName(std::string const & path);

    /**
     * Get the extension of the object, consisting of all characters after the last period character (or null if no period
     * exists).
     */
    static std::string extension(std::string const & path);

    /**
     * Get the complete extension of the object, consisting of all characters after the first period character (or null if no
     * period exists).
     */
    static std::string completeExtension(std::string const & path);

    /** Get the name of the object without the path. Ignores trailing slashes and isolated period characters. */
    static std::string objectName(std::string const & path);

    /** Get the path to the immediate parent of an object. Ignores trailing slashes and isolated period characters. */
    static std::string parent(std::string const & path);

    /**
     * Get the full path to a child object, given the path to the containing directory and the name of the child itself. If the
     * directory name is empty, just the child name is returned.
     */
    static std::string concat(std::string const & parent, std::string const & child);

    /**
     * Change the extension of a path. Equivalent to concat(parent(\a path), completeBaseName(\a path) + "." + \a new_ext).
     * Examples:
     *
     * \code
     * changeExtension("foo.txt", "dat")       // produces "foo.dat"
     * changeExtension("foo.old.txt", "dat")   // produces "foo.old.dat"
     * \endcode
     *
     * @param path The path to change.
     * @param new_ext The new extension.
     *
     * @see extension(), changeCompleteExtension()
     */
    static std::string changeExtension(std::string const & path, std::string const & new_ext);

    /**
     * Change the complete extension of a path. Equivalent to concat(parent(\a path), baseName(\a path) + "." + \a new_ext).
     * Examples:
     *
     * \code
     * changeExtension("foo.txt", "dat")       // produces "foo.dat"
     * changeExtension("foo.old.txt", "dat")   // produces "foo.dat"
     * \endcode
     *
     * @param path The path to change.
     * @param new_ext The new complete extension.
     *
     * @see completeExtension(), changeExtension()
     */
    static std::string changeCompleteExtension(std::string const & path, std::string const & new_ext);

}; // class FilePath

} // namespace DGP

#endif
