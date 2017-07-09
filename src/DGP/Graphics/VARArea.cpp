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

#include "VARArea.hpp"
#include "GLCaps.hpp"
#include "VAR.hpp"

namespace DGP {
namespace Graphics {

VARArea::VARArea(RenderSystem * render_system_, char const * name_, long capacity_, Usage usage, bool gpu_memory_)
: render_system(render_system_), name(name_), capacity(capacity_), gpu_memory(gpu_memory_), generation(0), allocated_size(0)
{
  if (gpu_memory && !DGP_SUPPORTS(ARB_vertex_buffer_object))
    throw Error(std::string(getName()) + ": OpenGL vertex/index buffers in GPU memory are not supported");

  assert(capacity > 0);

  if (gpu_memory)
  {
    { GLClientScope scope(GL_CLIENT_VERTEX_ARRAY_BIT);

      glGenBuffersARB(1, &gl_buffer);
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, gl_buffer);
      DGP_CHECK_GL_OK

      GLenum gl_usage;
      switch (usage)
      {
        case Usage::WRITE_EVERY_FRAME:  gl_usage = GL_STREAM_DRAW_ARB;  break;
        case Usage::WRITE_OCCASIONALLY: gl_usage = GL_DYNAMIC_DRAW_ARB; break;
        case Usage::WRITE_ONCE:         gl_usage = GL_STATIC_DRAW_ARB;  break;
        default:                        gl_usage = GL_STREAM_DRAW_ARB;
      }

      // Load some (undefined) data to initialize the buffer
      glBufferDataARB(GL_ARRAY_BUFFER_ARB, (GLsizei)capacity, NULL, gl_usage);
      DGP_CHECK_GL_OK

      base_pointer = NULL;

      glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
      DGP_CHECK_GL_OK
    }
  }
  else
  {
    gl_buffer = 0;
    base_pointer = new uint8[capacity];
  }
}

VARArea::~VARArea()
{
  if (capacity <= 0)  // how did this happen?
    return;

  if (gpu_memory)
    glDeleteBuffersARB(1, &gl_buffer);
  else
    delete [] base_pointer;
}

std::string
VARArea::toString() const
{
  std::ostringstream oss;
  oss << "OpenGL VARArea of capacity " << getCapacity() << " bytes in " << (gpu_memory ? "GPU" : "CPU") << " memory, of which "
      << getAllocatedSize() << " bytes are currently allocated";
  return oss.str();
}

void
VARArea::reset()
{
  generation++;
  allocated_size = 0;
}

VAR *
VARArea::createArray(long num_bytes)
{
  return new VAR(this, num_bytes);
}

void
VARArea::destroyArray(VAR * array)
{
  delete array;
}

} // namespace Graphics
} // namespace DGP
