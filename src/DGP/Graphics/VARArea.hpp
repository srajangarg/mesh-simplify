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

#ifndef __DGP_Graphics_VARArea_hpp__
#define __DGP_Graphics_VARArea_hpp__

#include "../Common.hpp"
#include "../NamedObject.hpp"
#include "GLHeaders.hpp"

namespace DGP {
namespace Graphics {

// Forward declarations
class RenderSystem;
class VAR;

/**
 * An interface for a Vertex Area Range storage area.
 *
 * @see VAR
 */
class DGP_API VARArea : public AbstractNamedObject
{
  public:
    /** How the storage will be used (enum class). */
    struct DGP_API Usage
    {
      /** Supported values. */
      enum Value
      {
        WRITE_EVERY_FRAME,   ///< The buffer will be written to frequently.
        WRITE_OCCASIONALLY,  ///< The buffer will be written to occasionally.
        WRITE_ONCE           ///< The buffer will be written to at most once.
      };

      DGP_ENUM_CLASS_BODY(Usage)
    };

    /** Destructor. */
    ~VARArea();

    char const * getName() const { return name.c_str(); }

    /** Destroy all vertex arrays allocated in this block. */
    void reset();

    /** Get the total capacity of the area in bytes. */
    long getCapacity() const { return capacity; }

    /** Get the number of bytes already allocated. */
    long getAllocatedSize() const { return allocated_size; }

    /** Get the number of available bytes. */
    long getAvailableSize() const { return getCapacity() - getAllocatedSize(); }

    /** Check if the area is stored in GPU memory or not. */
    bool inGPUMemory() const { return gpu_memory; }

    /** Create a VAR with a specified capacity in bytes. The VAR must be destroyed with destroyArray(). */
    VAR * createArray(long num_bytes);

    /** Destroy a VAR. The VAR must have been created with createArray(). */
    void destroyArray(VAR * array);

  private:
    /** Constructor. */
    VARArea(RenderSystem * render_system, char const * name_, long capacity_, Usage usage, bool gpu_memory_ = true);

    /** Get the parent rendersystem. */
    RenderSystem * getRenderSystem() const { return render_system; }

    /** Get a string describing the storage area. */
    std::string toString() const;

    /** Get the OpenGL index for this buffer.*/
    GLuint getGLBuffer() const { return gl_buffer; }

    /** Get a pointer to the first byte of the storage area.*/
    void * getBasePointer() const { return base_pointer; }

    /** Get the current generation (i.e. the number of times reset() has been called). */
    int getCurrentGeneration() const { return generation; }

    /** Mark an extra block as allocated. */
    void incrementAllocated(long inc) { allocated_size += inc; }

    RenderSystem * render_system;
    std::string name;
    long capacity;
    bool gpu_memory;
    GLuint gl_buffer;
    uint8 * base_pointer;
    int generation;
    long allocated_size;

    friend class RenderSystem;
    friend class VAR;

}; // class VARArea

} // namespace Graphics
} // namespace DGP

#endif
