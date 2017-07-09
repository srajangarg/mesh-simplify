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

#ifndef __DGP_Graphics_RenderSystem_hpp__
#define __DGP_Graphics_RenderSystem_hpp__

#include "../Common.hpp"
#include "../Camera.hpp"
#include "../Colors.hpp"
#include "../Image.hpp"
#include "../NamedObject.hpp"
#include "Framebuffer.hpp"
#include "Texture.hpp"
#include "Shader.hpp"
#include "VAR.hpp"
#include "VARArea.hpp"
#include <stack>
#include <unordered_set>

namespace DGP {

/** %Graphics module. */
namespace Graphics {

/**
 * Abstraction layer on top of OpenGL rendering API. Convenient for directly using other DGP classes and setting up
 * framebuffers, textures, shaders and vertex buffers. Can be freely mixed with raw OpenGL calls.
 *
 * If no rendering context is available when a rendersystem is constructed, the new rendersystem will be set up for offscreen
 * rendering if possible. In this case, you must explicitly create and attach a framebuffer to the rendersystem before you can
 * call any drawing functions.
 */
class DGP_API RenderSystem : public AbstractNamedObject
{
  public:
    /** Basic drawing primitives (enum class). */
    struct DGP_API Primitive
    {
      /** Supported values. */
      enum Value
      {
        POINTS,          ///< Set of points.
        LINES,           ///< Set of line segments.
        LINE_STRIP,      ///< Sequence of connected line segments.
        LINE_LOOP,       ///< Loop of line segments.
        TRIANGLES,       ///< Set of triangles.
        TRIANGLE_STRIP,  ///< Triangle strip.
        TRIANGLE_FAN,    ///< Triangle fan.
        QUADS,           ///< Set of quads.
        QUAD_STRIP,      ///< Quad strip.
        POLYGON          ///< A single polygon with an arbitrary number of edges.
      };

      DGP_ENUM_CLASS_BODY(Primitive)
    };

    /** Matrix-based transformation modes (enum class). */
    struct DGP_API MatrixMode
    {
      /** Supported values. */
      enum Value
      {
        MODELVIEW,   ///< Model-view matrix (cf. GL_MODELVIEW).
        PROJECTION,  ///< Projection matrix (cf. GL_PROJECTION).
        TEXTURE,     ///< Matrix to transform texture coordinates.
        COLOR        ///< Matrix to transform colors.
      };

      DGP_ENUM_CLASS_BODY(MatrixMode)
    };

    /** Depth tests (enum class). */
    struct DGP_API DepthTest
    {
      /** Supported values. */
      enum Value
      {
        GREATER,      ///< Accept if value is strictly greater than the threshold.
        LESS,         ///< Accept if value is strictly less than the threshold.
        GEQUAL,       ///< Accept if value is greater than or equal to the threshold.
        LEQUAL,       ///< Accept if value is less than or equal to the threshold.
        NOTEQUAL,     ///< Accept if value is not equal to the threshold.
        EQUAL,        ///< Accept if value is equal to the threshold.
        ALWAYS_PASS,  ///< Always accept.
        NEVER_PASS    ///< Never accept.
      };

      DGP_ENUM_CLASS_BODY(DepthTest)
    };

    /** Faces to be culled (enum class). */
    struct DGP_API CullFace
    {
      /** Supported values. */
      enum Value
      {
        NONE,   ///< No front/back culling.
        FRONT,  ///< Cull front faces.
        BACK    ///< Cull back faces.
      };

      DGP_ENUM_CLASS_BODY(CullFace)
    };

    /** Constructor. Creates a headless context for rendering if no rendering context currently exists. */
    RenderSystem(char const * name_);

    /** Destructor. Frees all resources (textures, shaders, framebuffers, VAR areas etc) created using this rendersystem. */
    ~RenderSystem();

    char const * getName() const { return name.c_str(); }

    /**
     * Get a string describing the render system. The string is guaranteed to be valid only till the next operation on the
     * object.
     */
    char const * describeSystem() const;

    /** Create a new, blank framebuffer with nothing attached. The framebuffer must be destroyed using destroyFramebuffer(). */
    Framebuffer * createFramebuffer(char const * name);

    /** Destroy a framebuffer created with createFramebuffer(). */
    void destroyFramebuffer(Framebuffer * framebuffer);

    /** Create a new, uninitialized shader. The shader must be destroyed using destroyShader(). */
    Shader * createShader(char const * name);

    /** Destroy a shader created with createShader(). */
    void destroyShader(Shader * shader);

    /** Create an empty texture of the specified format and size. The texture must be destroyed using destroyTexture(). */
    Texture * createTexture(char const * name, int width, int height, int depth,
                            Texture::Format const * desired_format, Texture::Dimension dimension,
                            Texture::Options const & options = Texture::Options::defaults());

    /**
     * Create a texture from a pixel buffer. The dimension argument <em>cannot</em> be DIM_CUBE_MAP. The texture must be
     * destroyed using destroyTexture().
     */
    Texture * createTexture(char const * name, Image const & image,
                            Texture::Format const * desired_format = Texture::Format::AUTO(),
                            Texture::Dimension dimension = Texture::Dimension::DIM_2D,
                            Texture::Options const & options = Texture::Options::defaults());

    /**
     * Create a cube-map from six pixel buffers, representing 2D images of identical format and size. The texture must be
     * destroyed using destroyTexture().
     */
    Texture * createTexture(char const * name, Image const * images[6],
                            Texture::Format const * desired_format = Texture::Format::AUTO(),
                            Texture::Options const & options = Texture::Options::defaults());

    /** Destroy a texture created with createTexture(). */
    void destroyTexture(Texture * texture);

    /**
     * Create a new, uninitialized area for storing vertex/normal/texture-coordinate/index arrays. The area must be destroyed
     * using destroyVARArea().
     */
    VARArea * createVARArea(char const * name, long num_bytes, VARArea::Usage usage, bool gpu_memory = true);

    /** Destroy a memory area created with createVARArea(). */
    void destroyVARArea(VARArea * area);

    /** Save the current framebuffer by pushing it onto the stack. */
    void pushFramebuffer();

    /** Set the current framebuffer. The drawing viewport is set to the framebuffer's entire area. */
    void setFramebuffer(Framebuffer * framebuffer);

    /**
     * Get the current framebuffer (may be null). If the rendersystem has been externally modified via direct API (e.g.
     * OpenGL/Direct3D) calls, this may not be the actual framebuffer currently in use!
     */
    Framebuffer const * getFramebuffer() const;

    /**
     * Get the current framebuffer (may be null). If the rendersystem has been externally modified via direct API (e.g.
     * OpenGL/Direct3D) calls, this may not be the actual framebuffer currently in use!
     */
    Framebuffer * getFramebuffer();

    /** Restore the last saved framebuffer from the stack. */
    void popFramebuffer();

    /** Save the current shader by pushing it onto the stack. */
    void pushShader();

    /** Set the current shader. */
    void setShader(Shader * shader);

    /**
     * Get the current shader (may be null). If the rendersystem has been externally modified via direct API (e.g.
     * OpenGL/Direct3D) calls, this may not be the actual shader currently in use!
     */
    Shader const * getShader() const;

    /**
     * Get the current shader (may be null). If the rendersystem has been externally modified via direct API (e.g.
     * OpenGL/Direct3D) calls, this may not be the actual shader currently in use!
     */
    Shader * getShader();

    /** Restore the last saved shader from the stack. */
    void popShader();

    /** Save all texture bindings and related state on the stack. */
    void pushTextures();

    /**
     * Bind a texture to a texture unit. Passing a null pointer disables the unit. The function signals an error if the render
     * system does not support multitexturing and the specified texture unit is non-zero.
     */
    void setTexture(int texunit, Texture * texture);

    /** Restore the last saved set of texture bindings and related state from the stack. */
    void popTextures();

    /** Get the current matrix mode. */
    MatrixMode getMatrixMode() const;

    /** Set the current matrix mode. */
    void setMatrixMode(MatrixMode mode);

    /** Save the matrix of the current matrix mode by pushing it onto the stack. */
    void pushMatrix();

    /** Get the current matrix of the specified matrix mode. */
    Matrix4 getMatrix(MatrixMode mode) const;

    /** Set the matrix of the current matrix mode. */
    void setMatrix(Matrix4 const & m);

    /**
     * Set the current viewing matrices from a camera. Subsequent changes to the original camera will <b>NOT</b> affect the
     * rendersystem.
     */
    void setCamera(Camera const & camera)
    {
      setMatrixMode(MatrixMode::PROJECTION);
      setMatrix(camera.getProjectionTransform());

      setMatrixMode(MatrixMode::MODELVIEW);
      setMatrix(camera.getWorldToCameraTransform().toHomMatrix());
    }

    /** Set the matrix of the current matrix mode to the identity transformation. */
    void setIdentityMatrix();

    /**
     * Post-multiply the matrix of the current matrix mode by the given matrix. The given transformation will be applied
     * <b>before</b> any previous transformations.
     */
    void multMatrix(Matrix4 const & m);

    /** Restore the last saved matrix of the current matrix mode from the stack. */
    void popMatrix();

    /** Prepare to draw a set of indexed primitives, after saving the current array states on the stack. */
    void beginIndexedPrimitives();

    /** Set the current vertex array. Passing a null VAR unbinds all vertex data. */
    void setVertexArray(VAR const * vertices);

    /** Set the current color array. Passing a null VAR unbinds all color data. */
    void setColorArray(VAR const * colors);

    /** Set the current texture coordinate array. Passing a null VAR unbinds all texture coordinate data. */
    void setTexCoordArray(int texunit, VAR const * texcoords);

    /** Set the current normal array. Passing a null VAR unbinds all normal data. */
    void setNormalArray(VAR const * normals);

    /** Set the current index array. Passing a null VAR unbinds all index data. */
    void setIndexArray(VAR const * indices);

    /** Draw a set of primitives by sending a set of 8-bit indices to the rendersystem. */
    void sendIndices(Primitive primitive, long num_indices, uint8 const * indices);

    /** Draw a set of primitives by sending a set of 16-bit indices to the rendersystem. */
    void sendIndices(Primitive primitive, long num_indices, uint16 const * indices);

    /** Draw a set of primitives by sending a set of 32-bit indices to the rendersystem. */
    void sendIndices(Primitive primitive, long num_indices, uint32 const * indices);

    /**
     * Draw a set of primitives by sending \a num_indices consecutive indices, starting from \a first_index, to the
     * rendersystem.
     */
    void sendSequentialIndices(Primitive primitive, int first_index, int num_indices);

    /**
     * Draw a set of primitives by sending indices from the current index array to the rendersystem. You must call
     * setIndexArray() to set a valid index array before you call this function.
     *
     * @param primitive The type of primitive to draw.
     * @param offset The number of initial indices to skip.
     * @param num_indices The number of indices to send to the rendersystem.
     *
     * @see setIndexArray()
     */
    void sendIndicesFromArray(Primitive primitive, long offset, long num_indices);

    /** Finish drawing the current set of indexed primitives and restore the last saved array states from the stack. */
    void endIndexedPrimitives();

    /** Start drawing a primitive of the given type. Must be matched with endPrimitive(). */
    void beginPrimitive(Primitive primitive);

    /** Send a 2-vertex to the rendersystem. */
    void sendVertex(Vector2 const & vertex);

    /** Send a 2-vertex to the rendersystem. */
    void sendVertex(float x, float y);

    /** Send a 2-vertex to the rendersystem. */
    void sendVertex(double x, double y);

    /** Send a 3-vertex to the rendersystem. */
    void sendVertex(Vector3 const & vertex);

    /** Send a 3-vertex to the rendersystem. */
    void sendVertex(float x, float y, float z);

    /** Send a 3-vertex to the rendersystem. */
    void sendVertex(double x, double y, double z);

    /** Send a 4-vertex to the rendersystem. */
    void sendVertex(Vector4 const & vertex);

    /** Send a 4-vertex to the rendersystem. */
    void sendVertex(float x, float y, float z, float w);

    /** Send a 4-vertex to the rendersystem. */
    void sendVertex(double x, double y, double z, double w);

    /** Set the current normal. */
    void setNormal(Vector3 const & normal);

    /** Set the current normal. */
    void setNormal(float x, float y, float z);

    /** Set the current normal. */
    void setNormal(double x, double y, double z);

    /** Set the current 1D texture coordinate. */
    void setTexCoord(int texunit, float texcoord);

    /** Set the current 1D texture coordinate. */
    void setTexCoord(int texunit, double texcoord);

    /** Set the current 2D texture coordinate. */
    void setTexCoord(int texunit, Vector2 const & texcoord);

    /** Set the current 2D texture coordinate. */
    void setTexCoord(int texunit, float x, float y);

    /** Set the current 2D texture coordinate. */
    void setTexCoord(int texunit, double x, double y);

    /** Set the current 3D texture coordinate. */
    void setTexCoord(int texunit, Vector3 const & texcoord);

    /** Set the current 3D texture coordinate. */
    void setTexCoord(int texunit, float x, float y, float z);

    /** Set the current 3D texture coordinate. */
    void setTexCoord(int texunit, double x, double y, double z);

    /** Finish drawing the primitive started by beginPrimitive(). */
    void endPrimitive();

    /** Save the current state of the rendersystem. This includes all attributes saved by other <code>push...</code> calls. */
    void pushState();

    /** Save the current set of color flags (color write, clear value etc) by pushing it onto the stack. */
    void pushColorFlags();

    /** Save the current set of depth flags (depth write, depth test, clear value etc) by pushing it onto the stack. */
    void pushDepthFlags();

    /** Save the current set of stencil flags (stencil write, clear value etc) by pushing it onto the stack. */
    void pushStencilFlags();

    /**
     * Save current set of parameters for rasterizing shapes (line width, smoothing flag for lines/points, polygon offsets
     * etc).
     */
    void pushShapeFlags();

    /** Set the color write state. */
    void setColorWrite(bool red, bool green, bool blue, bool alpha);

    /** Set the depth write state. */
    void setDepthWrite(bool value);

    /** Set the stencil write mask. */
    void setStencilWrite(uint32 mask);

    /** Set the current drawing color. */
    void setColor(ColorRGB const & value);

    /** Set the current drawing color. */
    void setColor(ColorRGBA const & value);

    /** Set the value to clear the color buffer with. */
    void setColorClearValue(ColorRGB const & value);

    /** Set the value to clear the color buffer with. */
    void setColorClearValue(ColorRGBA const & value);

    /** Set the value to clear the depth buffer with. */
    void setDepthClearValue(Real value);

    /** Set the value to clear the stencil buffer with. */
    void setStencilClearValue(int value);

    /** Clear color, depth and stencil buffers. */
    void clear();

    /** Clear the selected buffers. */
    void clear(bool color, bool depth, bool stencil);

    /** Set the depth test. */
    void setDepthTest(DepthTest test);

    /** Set the faces to be culled. */
    void setCullFace(CullFace cull);

    /**
     * Set the depth offset, if any, to be applied to polygon faces. The supplied value is scaled by an implementation-specific
     * offset.
     */
    void setPolygonOffset(bool enable, Real offset = 1);

    /** Set the size (diameter) of rasterized points. This may be ignored if shaders are being used. */
    void setPointSize(Real size = 1);

    /** Restore the last saved set of color flags from the stack. */
    void popColorFlags();

    /** Restore the last saved set of depth flags from the stack. */
    void popDepthFlags();

    /** Restore the last saved set of stencil flags from the stack. */
    void popStencilFlags();

    /** Restore the last saved set of shape flags from the stack. */
    void popShapeFlags();

    /** Restore the last saved rendersystem state from the stack. */
    void popState();

    /** The function returns only when the rendersystem has completely executed all previously-issued drawing calls. */
    void finishAllOperations();

  private:
    /** Stores the state of the current set of GPU buffers. */
    struct BufferState
    {
      VARArea * vertex_area;  ///< Vertex buffer.
      VARArea * index_area;  ///< Index buffer.
      VAR index_var;  ///< Index array.

      /** Constructor. */
      BufferState(VARArea * vertex_area_ = NULL, VARArea * index_area_ = NULL, VAR index_var_ = VAR())
      : vertex_area(vertex_area_), index_area(index_area_), index_var(index_var_)
      {}

    }; // struct BufferState

    typedef std::stack<Framebuffer *>  FramebufferStack;
    typedef std::stack<BufferState>    BufferStack;
    typedef std::stack<Shader *>       ShaderStack;

    typedef std::unordered_set<Framebuffer *>  FramebufferSet;
    typedef std::unordered_set<Texture *>      TextureSet;
    typedef std::unordered_set<Shader *>       ShaderSet;
    typedef std::unordered_set<VARArea *>      VARAreaSet;

    /**
     * Set the current vertex area to match the specified VAR. The vertex area used within a single
     * beginIndexedPrimitives()/endIndexedPrimitives() block must remain constant.
     */
    void setVertexAreaFromVAR(VAR const & v);

    /**
     * Set the current index area to match the specified VAR. The vertex area used within a single
     * beginIndexedPrimitives()/endIndexedPrimitives() block must remain constant.
     */
    void setIndexAreaFromVAR(VAR const & v);

    std::string name;
    mutable std::string desc;

    Framebuffer * current_framebuffer;
    FramebufferStack framebuffer_stack;

    BufferState current_buffer_state;
    BufferStack buffer_stack;

    Shader * current_shader;
    ShaderStack shader_stack;

    FramebufferSet  created_framebuffers;
    TextureSet      created_textures;
    ShaderSet       created_shaders;
    VARAreaSet      created_varareas;

}; // class RenderSystem

} // namespace Graphics
} // namespace DGP

#endif
