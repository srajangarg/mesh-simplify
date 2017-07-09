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

#include "VAR.hpp"
#include "VARArea.hpp"
#include "GLCaps.hpp"
#include <cstring>

namespace DGP {
namespace Graphics {

VAR::VAR()
: area(NULL), capacity(0), pointer(NULL), generation(-1), gl_type(-1), num_components(0), elem_size(0), gl_target(-1),
  num_elems(0)
{
}

VAR::VAR(VARArea * area_, long num_bytes)
: area(area_), capacity(num_bytes), pointer(NULL), generation(-1), gl_type(-1), num_components(0), elem_size(0), gl_target(-1),
  num_elems(0)
{
  alwaysAssertM(area_, "VAR: Valid VAR area required");
  alwaysAssertM(num_bytes > 0, "VAR: Capacity must be greater than zero");

  area = area_;

  if (num_bytes > area_->getAvailableSize())
    throw Error("VAR: Not enough free space in VAR area to create VAR");

  generation = area_->getCurrentGeneration();
  pointer = (uint8 *)area_->getBasePointer() + area_->getAllocatedSize();

  area_->incrementAllocated(num_bytes);
}

std::string
VAR::toString() const
{
  std::ostringstream oss;
  oss << "OpenGL VAR (" << capacity << " bytes)";
  return oss.str();
}

#define VAR_UPDATE_ARRAY(func_name, type_, gl_type_, num_components_, gl_target_) \
  void \
  VAR::func_name(long start_elem, long num_elems_to_update, type_ const * array) \
  { \
    if (num_elems_to_update <= 0) return; \
    \
    alwaysAssertM(isValid(), "VAR: Can't update invalid VAR"); \
    \
    if (num_elems > 0) \
    { \
      alwaysAssertM(gl_type == gl_type_ && num_components == num_components_ && gl_target == gl_target_, \
                    "VAR: Can't update non-empty VAR with elements of a different type"); \
    } \
    else \
    { \
      gl_type = gl_type_; \
      num_components = num_components_; \
      elem_size = sizeof(type_); \
      gl_target = gl_target_; \
    } \
    \
    long offset_bytes = start_elem * elem_size; \
    long num_bytes = num_elems_to_update * elem_size; \
    long total_size = offset_bytes + num_bytes; \
    if (total_size > capacity) \
      throw Error("VAR: Can't update beyond end of VAR"); \
    \
    if (start_elem + num_elems_to_update > num_elems) \
      num_elems = start_elem + num_elems_to_update; \
    \
    uploadToGraphicsSystem(offset_bytes, num_bytes, array); \
  }

#define VAR_UPDATE_VECTOR_ARRAY(type_, gl_type_, num_components_) \
  VAR_UPDATE_ARRAY(updateVectors, type_, gl_type_, num_components_, GL_ARRAY_BUFFER_ARB)

#define VAR_UPDATE_COLOR_ARRAY(type_, gl_type_, num_components_) \
  VAR_UPDATE_ARRAY(updateColors, type_, gl_type_, num_components_, GL_ARRAY_BUFFER_ARB)

#define VAR_UPDATE_INDEX_ARRAY(type_, gl_type_, num_components_) \
  VAR_UPDATE_ARRAY(updateIndices, type_, gl_type_, num_components_, GL_ELEMENT_ARRAY_BUFFER_ARB)

VAR_UPDATE_VECTOR_ARRAY(float,    GL_FLOAT,  1)
VAR_UPDATE_VECTOR_ARRAY(Vector2,  GL_FLOAT,  2)
VAR_UPDATE_VECTOR_ARRAY(Vector3,  GL_FLOAT,  3)
VAR_UPDATE_VECTOR_ARRAY(Vector4,  GL_FLOAT,  4)

VAR_UPDATE_COLOR_ARRAY(ColorL,      GL_FLOAT,           1)
VAR_UPDATE_COLOR_ARRAY(ColorL8,     GL_UNSIGNED_BYTE,   1)
VAR_UPDATE_COLOR_ARRAY(ColorL16,    GL_UNSIGNED_SHORT,  1)
VAR_UPDATE_COLOR_ARRAY(ColorRGB,    GL_FLOAT,           3)
VAR_UPDATE_COLOR_ARRAY(ColorRGB8,   GL_UNSIGNED_BYTE,   3)
VAR_UPDATE_COLOR_ARRAY(ColorRGBA,   GL_FLOAT,           4)
VAR_UPDATE_COLOR_ARRAY(ColorRGBA8,  GL_UNSIGNED_BYTE,   4)

VAR_UPDATE_INDEX_ARRAY(uint8,   GL_UNSIGNED_BYTE,   1)
VAR_UPDATE_INDEX_ARRAY(uint16,  GL_UNSIGNED_SHORT,  1)
VAR_UPDATE_INDEX_ARRAY(uint32,  GL_UNSIGNED_INT,    1)

void
VAR::clear()
{
  gl_type = -1;
  num_components = -1;
  elem_size = -1;
  gl_target = -1;
  num_elems = 0;
}

void
VAR::uploadToGraphicsSystem(long offset_bytes, long num_bytes, void const * data)
{
  assert(isValid());

  void * ptr = (void *)((uint8 *)pointer + offset_bytes);

  if (area->inGPUMemory())
  {
    { GLClientScope scope(GL_CLIENT_VERTEX_ARRAY_BIT);

      glBindBufferARB(gl_target, area->getGLBuffer());
      glBufferSubDataARB(gl_target, (GLintptrARB)ptr, (GLsizeiptr)num_bytes, data);
      glBindBufferARB(gl_target, 0);
    }
  }
  else
    std::memcpy(ptr, data, num_bytes);
}

} // namespace Graphics
} // namespace DGP
