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

#ifndef __DGP_Graphics_VAR_hpp__
#define __DGP_Graphics_VAR_hpp__

#include "../Common.hpp"
#include "../Colors.hpp"
#include "../VectorN.hpp"
#include "GLHeaders.hpp"
#include "VARArea.hpp"

namespace DGP {
namespace Graphics {

// Forward declarations
class RenderSystem;

/**
 * An interface for a Vertex Area Range object, which may be in main or GPU memory. The VAR should be constructed via the
 * functions in VARArea.
 */
class DGP_API VAR
{
  public:
    /** Destructor. */
    ~VAR() {}

    /**
     * Update a section of a vector array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateVectors(long start_elem, long num_elems_to_update, float const * array);

    /**
     * Update a section of a vector array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateVectors(long start_elem, long num_elems_to_update, Vector2 const * array);

    /**
     * Update a section of a vector array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateVectors(long start_elem, long num_elems_to_update, Vector3 const * array);

    /**
     * Update a section of a vector array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateVectors(long start_elem, long num_elems_to_update, Vector4 const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorL const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorL8 const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorL16 const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorRGB const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorRGB8 const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorRGBA const * array);

    /**
     * Update a section of a color array. If the VAR is currently non-empty, the new and old data types must match. Call clear()
     * before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateColors(long start_elem, long num_elems_to_update, ColorRGBA8 const * array);

    /**
     * Update a section of an index array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateIndices(long start_elem, long num_elems_to_update, uint8 const * array);

    /**
     * Update a section of an index array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateIndices(long start_elem, long num_elems_to_update, uint16 const * array);

    /**
     * Update a section of an index array. If the VAR is currently non-empty, the new and old data types must match. Call
     * clear() before changing types.
     *
     * The update may increase the number of elements in the VAR, as long as it does not exceed the buffer capacity. The number
     * of elements (numElements()) is measured from the start of the VAR to the last initialized element: any uninitialized
     * portions in the middle will be included in the tally!
     *
     * @note Do <b>not</b> call this function within a RenderSystem::beginIndexedPrimitives() /
     *   RenderSystem::endIndexedPrimitives() block.
     */
    void updateIndices(long start_elem, long num_elems_to_update, uint32 const * array);

    /**
     * Clear all data in the buffer, without deallocating it. You must call this function before updating the VAR with data of
     * a different type.
     */
    void clear();

    /** Get the number of elements in the VAR. */
    long numElements() const { return num_elems; }

    /** Get the capacity of the VAR in bytes. */
    long getCapacityInBytes() const { return capacity; }

    /** Check if the VAR is still valid. */
    bool isValid() const { return area && capacity > 0 && generation == area->getCurrentGeneration(); }

  private:
    /** Default constructor. Creates an empty, invalid VAR. */
    VAR();

    /**
     * Constructor. Creates an empty VAR of the specified size. The VAR is not valid until it has been initialized with one of
     * the <code>update...()</code> functions. \a area_ must be non-null and \a num_bytes must be greater than zero.
     */
    VAR(VARArea * area_, long num_bytes);

    /** Get a string describing the VAR. */
    std::string toString() const;

    /** The OpenGL data type of a single component (eg GL_FLOAT). */
    GLenum getGLType() const { return gl_type; }

    /** The number of components per element. */
    int getNumComponents() const { return num_components; }

    /** The size of an element in bytes. */
    int getElementSize() const { return elem_size; }

    /** The id of the OpenGL target. */
    int getGLTarget() const { return gl_target; }

    /** Get the VARArea where this VAR is stored. */
    VARArea * getArea() const { return area; }

    /** A pointer to the first element of the VAR. */
    void * getBasePointer() const { return pointer; }

    /** The generation of the parent VARArea when this VAR was created. */
    int getGeneration() const { return generation; }

    /** Upload source data to the graphics system. */
    void uploadToGraphicsSystem(long offset_bytes, long num_bytes, void const * data);

    VARArea * area;
    long capacity;
    void * pointer;
    int generation;

    GLenum gl_type;
    int num_components;
    int elem_size;
    GLenum gl_target;
    long num_elems;

    friend class RenderSystem;
    friend class VARArea;

}; // class VAR

} // namespace Graphics
} // namespace DGP

#endif
