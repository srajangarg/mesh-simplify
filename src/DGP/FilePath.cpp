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

#include "FilePath.hpp"

namespace DGP {

std::string
FilePath::baseName(std::string const & path)
{
  std::string node = objectName(path);
  size_t first_dot = node.find_first_of('.');
  return (first_dot == std::string::npos ? node : node.substr(0, first_dot));
}

std::string
FilePath::completeBaseName(std::string const & path)
{
  std::string node = objectName(path);
  size_t last_dot = node.find_last_of('.');
  return (last_dot == std::string::npos ? node : node.substr(0, last_dot));
}

std::string
FilePath::extension(std::string const & path)
{
  std::string node = objectName(path);
  size_t last_dot = node.find_last_of('.');
  return (last_dot == std::string::npos ? std::string() : node.substr(last_dot + 1));
}

std::string
FilePath::completeExtension(std::string const & path)
{
  std::string node = objectName(path);
  size_t first_dot = node.find_first_of('.');
  return (first_dot == std::string::npos ? std::string() : node.substr(first_dot + 1));
}

namespace FilePathInternal {

bool
isSlash(char c)
{
#ifdef DGP_WINDOWS
  return (c == '/' || c == '\\');
#else
  return c == '/';
#endif
}

// No special handling of "."
std::string
objectNameHelper1(std::string const & path, size_t & obj_start)
{
  obj_start = 0;
  size_t obj_end = path.length();
  for (long i = (long)path.length() - 1; i >= 0; --i)
  {
    if (isSlash(path[(size_t)i]))
    {
      if (obj_end == (size_t)(i + 1))
      {
        if (i == 0)
        {
          obj_start = 0;
          break;
        }
        else
          obj_end = (size_t)i;
      }
      else
      {
        obj_start = (size_t)(i + 1);
        break;
      }
    }
  }

  return path.substr(obj_start, obj_end - obj_start);
}

// Strip trailing "."
std::string
objectNameHelper2(std::string const & path, size_t & obj_start)
{
  obj_start = 0;
  std::string p = path;
  while (!p.empty())
  {
    std::string n = objectNameHelper1(p, obj_start);  // index relative to p, but also valid for path since p is prefix of path

    if (n == "." && p != ".")
      p = p.substr(0, obj_start);  // strip self-reference "."
    else
      return n;
  }

  return "";
}

} // namespace FilePathInternal

std::string
FilePath::objectName(std::string const & path)
{
  size_t obj_start;
  return FilePathInternal::objectNameHelper2(path, obj_start);
}

std::string
FilePath::parent(std::string const & path)
{
  size_t obj_start;
  std::string obj_name = FilePathInternal::objectNameHelper2(path, obj_start);
  if (obj_start > 0)
  {
    if (obj_start == 1)
      return "/";
    else
      return path.substr(0, obj_start - 1);
  }
  else
    return "";
}

std::string
FilePath::concat(std::string const & parent_name, std::string const & child_name)
{
  if (parent_name.empty())
    return child_name;

  if (FilePathInternal::isSlash(parent_name[parent_name.length() - 1]))
    return parent_name + child_name;
  else
  {
#ifdef DGP_WINDOWS
    return parent_name + '\\' + child_name;
#else
    return parent_name + '/' + child_name;
#endif
  }
}

std::string
FilePath::changeExtension(std::string const & path, std::string const & new_ext)
{
  return concat(parent(path), completeBaseName(path) + '.' + new_ext);
}

std::string
FilePath::changeCompleteExtension(std::string const & path, std::string const & new_ext)
{
  return concat(parent(path), baseName(path) + '.' + new_ext);
}

} // namespace DGP
