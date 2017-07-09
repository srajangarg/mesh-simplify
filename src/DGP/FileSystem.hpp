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

#ifndef __DGP_FileSystem_hpp__
#define __DGP_FileSystem_hpp__

#include "Common.hpp"

namespace DGP {

/**
 * Filesystem operations. Unlike FilePath, these functions do actually access the filesystem.
 *
 * @note Returned paths are in native OS format (e.g. backslashes on Windows, forward slashes on Unix).
 */
class DGP_API FileSystem
{
  public:
    /** Types of objects in the filesystem (enum class). */
    struct ObjectType
    {
      /** Supported values. */
      enum Value
      {
        FILE            =  0x0001,  ///< Ordinary file.
        DIRECTORY       =  0x0002,  ///< Directory.
        SYMLINK         =  0x0004,  ///< Symbolic link.
        ALL             =  0xFFFF,  ///< Catch-all value for all types of filesystem objects.
      };

      DGP_ENUM_CLASS_BODY(ObjectType)

    }; // struct ObjectType

    /** Check if a file or directory exists. */
    static bool exists(std::string const & path);

    /** Check if a file exists, and is indeed a regular file (and not for instance a directory). */
    static bool fileExists(std::string const & path);

    /** Check if a directory exists, and is indeed a directory (and not for instance a file). */
    static bool directoryExists(std::string const & path);

    /** Get the length of a file in bytes. Returns a negative number on failure. */
    static int64 fileSize(std::string const & path);

    /** Get the entire contents of a file as a string. */
    static std::string readWholeFile(std::string const & path)
    {
      std::string s;
      if (!readWholeFile(path, s))
        throw Error("FileSystem: Could not read '" + path + '\'');

      return s;
    }

    /**
     * Get the entire contents of a file as a string.
     *
     * @return True on success, false on error.
     */
    static bool readWholeFile(std::string const & path, std::string & ret);

}; // class FileSystem

} // namespace DGP

#endif
