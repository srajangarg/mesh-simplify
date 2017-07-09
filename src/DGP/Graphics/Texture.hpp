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

#ifndef __DGP_Graphics_Texture_hpp__
#define __DGP_Graphics_Texture_hpp__

#include "../Common.hpp"
#include "../NamedObject.hpp"
#include "../Image.hpp"
#include "GLHeaders.hpp"
#include "TextureFormat.hpp"

namespace DGP {
namespace Graphics {

// Forward declarations
class Framebuffer;
class RenderSystem;
class Shader;

/** An interface for a texture. */
class DGP_API Texture : public AbstractNamedObject
{
  public:
    /** %Texture dimensionality (enum class). */
    struct DGP_API Dimension
    {
      /** Supported values. */
      enum Value
      {
        DIM_1D,         ///< 1D texture.
        DIM_2D,         ///< 2D texture.
        DIM_3D,         ///< 3D texture.
        DIM_RECTANGLE,  ///< Rectangular texture (deprecated, retained only for compatibility with OpenGL).
        DIM_CUBE_MAP    ///< Cube-mapped texture.
      };

      DGP_ENUM_CLASS_BODY(Dimension)
    };

    /** Wrap modes (enum class). */
    struct DGP_API WrapMode
    {
      /** Supported values. */
      enum Value
      {
        CLAMP,  ///< Clamp out-of-range pixels to the border color.
        TILE,   ///< Tile the image to assign colors to out-of-range pixels.
        ZERO    ///< Out-of-range pixels are all set to zero.
      };

      DGP_ENUM_CLASS_BODY(WrapMode)
    };

    /** Interpolation modes (enum class). */
    struct DGP_API InterpolateMode
    {
      /** Supported values. */
      enum Value
      {
        NEAREST_NO_MIPMAP,   ///< No mipmapping or filtering.
        NEAREST_MIPMAP,      ///< Mipmapping, but no filtering during lookup.
        BILINEAR_NO_MIPMAP,  ///< Bilinear filtering, no mipmapping.
        BILINEAR_MIPMAP,     ///< Bilinear filtering with mipmapping.
        TRILINEAR            ///< Trilinear filtering (bilinear + interpolation between mipmaps)
      };

      DGP_ENUM_CLASS_BODY(InterpolateMode)
    };

    /** Depth read modes, useful for shadow mapping (enum class).*/
    struct DGP_API DepthReadMode
    {
      /** Supported values. */
      enum Value
      {
        NORMAL,  ///< See documentation of GL_TEXTURE_COMPARE_MODE and GL_TEXTURE_COMPARE_FUNC.
        LEQUAL,  ///< See documentation of GL_TEXTURE_COMPARE_MODE and GL_TEXTURE_COMPARE_FUNC.
        GEQUAL   ///< See documentation of GL_TEXTURE_COMPARE_MODE and GL_TEXTURE_COMPARE_FUNC.
      };

      DGP_ENUM_CLASS_BODY(DepthReadMode)
    };

    /** Cube map faces (enum class).*/
    struct DGP_API Face
    {
      /** Supported values. */
      enum Value
      {
        POS_X = 0,  ///< Face with outward normal along positive X.
        NEG_X,      ///< Face with outward normal along negative X.
        POS_Y,      ///< Face with outward normal along negative Y.
        NEG_Y,      ///< Face with outward normal along negative Y.
        POS_Z,      ///< Face with outward normal along negative Z.
        NEG_Z       ///< Face with outward normal along negative Z.
      };

      DGP_ENUM_CLASS_BODY(Face)
    };

    /** %Texture options. */
    struct DGP_API Options
    {
      WrapMode         wrapMode;         ///< Texture wrapping mode.
      InterpolateMode  interpolateMode;  ///< Texture interpolation mode.
      DepthReadMode    depthReadMode;    ///< Depth read mode.

      /** Get the set of default options. */
      static Options const & defaults()
      {
        static Options const ops = { WrapMode::CLAMP, InterpolateMode::BILINEAR_NO_MIPMAP, DepthReadMode::NORMAL };
        return ops;
      }
    };

    /** %Texture storage format. */
    typedef TextureFormat Format;

    /** Destructor. */
    ~Texture();

    char const * getName() const { return name.c_str(); }

    /** Get the parent rendersystem. */
    RenderSystem * getRenderSystem() const { return render_system; }

    /** Get the width of the texture in pixels. */
    int getWidth() const { return width; }

    /** Get the height of the texture in pixels. */
    int getHeight() const { return height; }

    /** Get the depth of the texture in pixels. */
    int getDepth() const { return depth; }

    /** Get the storage format of the texture. */
    Format const * getFormat() const { return format; }

    /** Get the dimensionality of the texture. */
    Dimension getDimension() const { return dimension; }

    /** Update (a face of) the texture from a pixel buffer. The face argument is ignored for non-cube map textures. */
    void updateImage(Image const & image, Face face = Face::POS_X);

    /** Update a part of (a face of) the texture from a pixel buffer. The face argument is ignored for non-cube map textures. */
    void updateSubImage(Image const & image, int dst_x, int dst_y, int dst_z = 0, Face face = Face::POS_X)
    {
      updateSubImage(image, 0, 0, image.getWidth(), image.getHeight(), dst_x, dst_y, dst_z, face);
    }

    /**
     * Update a part of (a face of) the texture from a portion of a pixel buffer. The block of the source image with corner
     * (\a src_x, \a src_y) and size \a src_width x \a src_height is copied to the corresponding block of the texture with
     * corner (\a dst_x, \a dst_y). The face argument is ignored for non-cube map textures.
     */
    void updateSubImage(Image const & image, int src_x, int src_y, int src_width, int src_height, int dst_x, int dst_y,
                        int dst_z = 0, Face face = Face::POS_X);

    /** Copy (a face of) the texture into a pixel buffer. The face argument is ignored for non-cube map textures. */
    void getImage(Image & image, Face face = Face::POS_X) const;

    /** Copy a part of (a face of) the texture into a pixel buffer. The face argument is ignored for non-cube map textures. */
    void getSubImage(Image & image, int x, int y, int z, int subimage_width, int subimage_height, int subimage_depth,
                     Face face = Face::POS_X) const;

  protected:
    /** Constructs an empty texture of the specified format and size. */
    Texture(RenderSystem * render_system_, char const * name_, int width_, int height_, int depth_,
            Format const * desired_format, Dimension dimension, Options const & options);

    /** Constructs a texture from a pixel buffer. The dimension argument <em>cannot</em> be DIM_CUBE_MAP. */
    Texture(RenderSystem * render_system_, char const * name_, Image const & image, Format const * desired_format,
            Dimension dimension, Options const & options);

    /** Constructs a cube-map from six pixel buffers, representing 2D images of identical format and size. */
    Texture(RenderSystem * render_system_, char const * name_, Image const * images[6],
            Format const * desired_format, Options const & options);

    /** Get the OpenGL target to which this texture is bound (e.g. GL_TEXTURE_2D). */
    GLenum getGLTarget() const { return gl_target; }

    /** Get the OpenGL ID of the texture. */
    GLuint getGLID() const { return gl_id; }

    /** Determine the internal storage format of the texture. */
    void setInternalFormat(Format const * bytes_format, Format const * desired_format);

    /** Do a series of checks to detect invalid parameters. */
    void doSanityChecks();

    /** Set texture parameters from user-specified options. */
    void setOptions(Options const & options);

    /** A quick selection of the appropriate glTexImage... call based on current state. */
    void glTexImage(void const * bytes, Format const * bytes_format, Face face);

    /** Updates the texture image and optionally sets user-specified options while doing so. */
    void updateImage(Image const & image, Face face, Options const * options);

    /** Convenience function to convert an image type to a texture storage format. */
    static Format const * toTextureFormat(Image::Type type);

    /** Convert the label of a texture face to the corresponding GL enum. */
    static GLenum toGLCubeMapFace(Texture::Face face);

    RenderSystem * render_system;
    std::string name;
    int width;
    int height;
    int depth;
    Format const * format;
    Dimension dimension;
    GLenum gl_target;
    GLuint gl_id;

    friend class Framebuffer;
    friend class RenderSystem;
    friend class Shader;

}; // class Texture

} // namespace Graphics
} // namespace DGP

#endif
