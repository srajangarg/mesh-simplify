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

#include "FileSystem.hpp"
#include "StringAlg.hpp"
#include <cstdio>

#ifdef DGP_WINDOWS
#  include <sys/types.h>
#  include <sys/stat.h>
#  define DGP_STAT _stat
#  ifndef S_IREG
#    define S_ISREG(B) ((B) & _S_IFREG)
#  endif
#  ifndef S_IREG
#    define S_ISDIR(B) ((B) & _S_IFDIR)
#  endif
#else
#  include <sys/stat.h>
#  define DGP_STAT stat
#endif

namespace DGP {

bool
FileSystem::exists(std::string const & path)
{
  struct DGP_STAT buffer;
  return (DGP_STAT(path.c_str(), &buffer) == 0);
}

bool
FileSystem::fileExists(std::string const & path)
{
  struct DGP_STAT buffer;
  int exists = (DGP_STAT(path.c_str(), &buffer) == 0);
  return exists && S_ISREG(buffer.st_mode);
}

bool
FileSystem::directoryExists(std::string const & path)
{
  struct DGP_STAT buffer;
  int exists = (DGP_STAT(path.c_str(), &buffer) == 0);
  return exists && S_ISDIR(buffer.st_mode);
}

int64
FileSystem::fileSize(std::string const & path)
{
  struct DGP_STAT buffer;
  if (DGP_STAT(path.c_str(), &buffer) == 0)
    return (int64)buffer.st_size;
  else
    return -1;
}

bool
FileSystem::readWholeFile(std::string const & path, std::string & ret)
{
  if (!fileExists(path))
  {
    DGP_ERROR << "FileSystem: File '" << path << "' not found";
    return false;
  }

  int64 length = fileSize(path);
  if (length <= 0)
  {
    ret.clear();
    return true;
  }

  char * buffer = (char *)std::malloc((size_t)length);
  if (!buffer)
  {
    DGP_ERROR << "FileSystem: Could not allocate buffer to hold " << length << " bytes from file '" << path << '\'';
    return false;
  }

  FILE * f = std::fopen(path.c_str(), "rb");
  if (!f)
  {
    DGP_ERROR << "FileSystem: Couldn't open file '" << path << "' for reading";
    return false;
  }

  size_t num_read = std::fread(buffer, 1, length, f);
  if ((int64)num_read != length)
  {
    DGP_ERROR << "FileSystem: Error reading from file '" << path << '\'';
    return false;
  }

  std::fclose(f);

  ret.assign(buffer, (size_t)length);
  std::free(buffer);

  return true;
}

} // namespace DGP
