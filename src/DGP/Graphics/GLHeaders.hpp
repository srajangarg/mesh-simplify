//============================================================================
//
// From the G3D project. Copyright (C) 2000-2008 Morgan McGuire.
//
// For the full G3D license see LICENSE.txt in the documentation.
//
//============================================================================

#ifndef __DGP_Graphics_GLHeaders_hpp__
#define __DGP_Graphics_GLHeaders_hpp__

#include "../Common.hpp"
#include "../FilePath.hpp"

// Main includes
#include "glew.hpp"

#if defined(DGP_OSMESA)

// glew.hpp undefs a bunch of visibility macros after it's done with them, but we need to restore them for osmesa.h
#  if defined(_WIN32)
#    ifndef APIENTRY
#      if defined(__MINGW32__)
#        define APIENTRY __stdcall
#      elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#        define APIENTRY __stdcall
#      else
#        define APIENTRY
#      endif
#    endif
#    ifndef GLAPI
#      if defined(__MINGW32__)
#        define GLAPI extern
#      endif
#    endif
     /* <wingdi.h> and <winnt.h> */
#    ifndef WINGDIAPI
#      define WINGDIAPI __declspec(dllimport)
#    endif
#    ifndef GLAPI
#      if defined(__MINGW32__)
#        define GLAPI extern
#      else
#        define GLAPI WINGDIAPI
#      endif
#    endif

#    ifndef GLAPIENTRY
#      define GLAPIENTRY APIENTRY
#    endif

#  else /* _UNIX */

#    define APIENTRY

     /* <glu.h> */
#    ifndef GLAPI
#      define GLAPI extern
#    endif
#    ifndef GLAPIENTRY
#      define GLAPIENTRY
#    endif

#  endif /* _WIN32 */

#  include <GL/osmesa.h>

#endif

#if defined(DGP_OSX) && !defined(DGP_OSMESA)
#  include <OpenGL/OpenGL.h>  // required to pull in CGL, which OpenGL/gl.h does not
#endif

// GUI compatibility. Requires a display device.
#ifndef DGP_OSMESA
#  ifdef DGP_WIN32
#    include "wglew.hpp"
#  elif defined(DGP_LINUX) || defined(DGP_BSD)
#    include "glxew.hpp"
#  endif
#endif

namespace DGP {
namespace Graphics {

// RAII idiom for saving and restoring OpenGL server attribute states.
struct DGP_DLL_LOCAL GLScope
{
  // Constructor. Creates a new scope for a set of attributes.
  GLScope(GLbitfield attribs_to_save) { glPushAttrib(attribs_to_save); }

  // Destructor. Restores saved attributes from the stack.
  ~GLScope() { glPopAttrib(); }
};

// RAII idiom for saving and restoring OpenGL client attribute states.
struct DGP_DLL_LOCAL GLClientScope
{
  // Constructor. Creates a new scope for a set of attributes.
  GLClientScope(GLbitfield attribs_to_save) { glPushClientAttrib(attribs_to_save); }

  // Destructor. Restores saved attributes from the stack.
  ~GLClientScope() { glPopClientAttrib(); }
};

// Replacement for deprecated gluErrorString().
inline GLubyte const *
dgpGLErrorString(GLuint error)
{
  switch (error)
  {
#define DGP_ERROR_STRING_BRANCH(p) case(p): return (GLubyte const *)#p;
    DGP_ERROR_STRING_BRANCH(GL_NO_ERROR)
    DGP_ERROR_STRING_BRANCH(GL_INVALID_ENUM)
    DGP_ERROR_STRING_BRANCH(GL_INVALID_VALUE)
    DGP_ERROR_STRING_BRANCH(GL_INVALID_OPERATION)
    DGP_ERROR_STRING_BRANCH(GL_STACK_OVERFLOW)
    DGP_ERROR_STRING_BRANCH(GL_STACK_UNDERFLOW)
    DGP_ERROR_STRING_BRANCH(GL_OUT_OF_MEMORY)
    DGP_ERROR_STRING_BRANCH(GL_TABLE_TOO_LARGE)
    default: break;
#undef DGP_ERROR_STRING_BRANCH
  }

  if ((error >= GLU_NURBS_ERROR1) && (error <= GLU_NURBS_ERROR37))
    return (GLubyte const *)"NURBS error";
  if ((error >= GLU_TESS_ERROR1) && (error <= GLU_TESS_ERROR8))
    return (GLubyte const *)"tessellation error";

  return (GLubyte const *)"unknown error";
}


// Check if the OpenGL state is error-free.
//
// @todo Make this a no-op in release mode?
#define DGP_CHECK_GL_OK \
{ \
  GLenum err_code; \
  GLubyte const * err_string; \
\
  if ((err_code = glGetError()) != GL_NO_ERROR) \
  { \
    err_string = dgpGLErrorString(err_code); \
    throw Error(DGP::format("%s:%ld: OpenGL error: %s", \
                DGP::FilePath::objectName(__FILE__).c_str(), (long)__LINE__, err_string)); \
  } \
}

// A convenient shortcut for getting a single integer state.
inline DGP_DLL_LOCAL GLint
glGetInteger(GLenum which)
{
  // We allocate an array in case the caller accidentally invoked on a value that will return more than just one integer
  GLint result[32];
  glGetIntegerv(which, result);
  return result[0];
}

// Get a handle to the current OpenGL context, if available. On platforms where we can't return a context, this function always
// returns true.
#if defined(DGP_OSMESA)

  typedef OSMesaContext GLContext;
  inline DGP_DLL_LOCAL GLContext glGetCurrentContext()
  {
    return OSMesaGetCurrentContext();
  }

#elif defined(DGP_WINDOWS)

  typedef HGLRC GLContext;
  inline DGP_DLL_LOCAL GLContext glGetCurrentContext()
  {
    return wglGetCurrentContext();
  }

#elif defined(DGP_LINUX) || defined(DGP_BSD)

  typedef GLXContext GLContext;
  inline DGP_DLL_LOCAL GLContext glGetCurrentContext()
  {
    return glXGetCurrentContext();
  }

#elif defined(DGP_OSX)

  typedef CGLContextObj GLContext;
  inline DGP_DLL_LOCAL GLContext glGetCurrentContext()
  {
      return CGLGetCurrentContext();
  }

#endif

} // namespace Graphics
} // namespace DGP

#endif
