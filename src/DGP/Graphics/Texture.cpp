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

#include "Texture.hpp"
#include "../Math.hpp"
#include "GLCaps.hpp"

namespace DGP {
namespace Graphics {

static GLenum
Texture__dimensionToGLTarget(Texture::Dimension dimension)
{
  switch (dimension)
  {
    case Texture::Dimension::DIM_1D: return GL_TEXTURE_1D;
    case Texture::Dimension::DIM_2D: return GL_TEXTURE_2D;
    case Texture::Dimension::DIM_3D: return GL_TEXTURE_3D;
    case Texture::Dimension::DIM_RECTANGLE: return GL_TEXTURE_RECTANGLE_ARB;
    case Texture::Dimension::DIM_CUBE_MAP: return GL_TEXTURE_CUBE_MAP_ARB;
    default: throw Error("Texture: Unsupported dimension");
  }
}

GLenum
Texture::toGLCubeMapFace(Texture::Face face)
{
  switch (face)
  {
    case Texture::Face::POS_X: return GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB;
    case Texture::Face::NEG_X: return GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB;
    case Texture::Face::POS_Y: return GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB;
    case Texture::Face::NEG_Y: return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB;
    case Texture::Face::POS_Z: return GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB;
    default:                   return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB;
  }
}

Texture::Format const *
Texture::toTextureFormat(Image::Type type)
{
  switch (type)
  {
    case Image::Type::LUMINANCE_8U  : return Format::L8();
    case Image::Type::LUMINANCE_32F : return Format::L32F();
    case Image::Type::LA_8U         : return Format::LA8();
    case Image::Type::LA_32F        : return Format::LA32F();
    case Image::Type::RGB_8U        : return Format::RGB8();
    case Image::Type::RGBA_8U       : return Format::RGBA8();
    case Image::Type::RGB_32F       : return Format::RGB32F();
    case Image::Type::RGBA_32F      : return Format::RGBA32F();
    default: throw Error("No supported texture format corresponds to the specified image format");
  }
}

static void
Texture__setDefaultUnpackingOptions(int row_alignment)
{
  debugAssertM(row_alignment >= 0, "Texture: Row alignment cannot be negative");

  // GL's default values for everything except alignment
  glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
  glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
  glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
  glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_UNPACK_ALIGNMENT, row_alignment);
}

static void
Texture__setDefaultPackingOptions(int row_alignment)
{
  debugAssertM(row_alignment >= 0, "Texture: Row alignment cannot be negative");

  // GL's default values for everything except alignment
  glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
  glPixelStorei(GL_PACK_LSB_FIRST, GL_FALSE);
  glPixelStorei(GL_PACK_ROW_LENGTH, 0);
  glPixelStorei(GL_PACK_SKIP_ROWS, 0);
  glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
  glPixelStorei(GL_PACK_ALIGNMENT, row_alignment);
}

Texture::Texture(RenderSystem * render_system_, char const * name_, int width_, int height_, int depth_,
                 Format const * desired_format, Dimension dimension_, Options const & options)
: render_system(render_system_), name(name_), width(width_), height(height_), depth(depth_), dimension(dimension_)
{
  setInternalFormat(NULL, desired_format);
  doSanityChecks();

  glGenTextures(1, &gl_id);
  DGP_CHECK_GL_OK

  { GLScope scope(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
    GLClientScope client_scope(GL_CLIENT_PIXEL_STORE_BIT);

    gl_target = Texture__dimensionToGLTarget(dimension);
    glEnable(gl_target);
    glBindTexture(gl_target, gl_id);
    DGP_CHECK_GL_OK

    setOptions(options);

    switch (dimension)
    {
      case Dimension::DIM_CUBE_MAP:
        glTexImage(NULL, format, Face::NEG_X);
        glTexImage(NULL, format, Face::POS_Y);
        glTexImage(NULL, format, Face::NEG_Y);
        glTexImage(NULL, format, Face::POS_Z);
        glTexImage(NULL, format, Face::NEG_Z);
        // Fall-through...

      default:
        glTexImage(NULL, format, Face::POS_X);  // face argument is ignored if not cube map
    }
  }
}

Texture::Texture(RenderSystem * render_system_, char const * name_, Image const & image,
                 Format const * desired_format, Dimension dimension_, Options const & options)
: render_system(render_system_), name(name_), dimension(dimension_), gl_target(Texture__dimensionToGLTarget(dimension))
{
  if (dimension == Dimension::DIM_CUBE_MAP)
    throw Error(std::string(getName()) + ": This constructor cannot be used to create a cube map");

  Format const * bytes_format = toTextureFormat(image.getType());
  setInternalFormat(bytes_format, desired_format);

  glGenTextures(1, &gl_id);
  DGP_CHECK_GL_OK

  updateImage(image, Face::POS_X, &options);
}

Texture::Texture(RenderSystem * render_system_, char const * name_, Image const * images[6],
                 Format const * desired_format, Options const & options)
: render_system(render_system_), name(name_), dimension(Dimension::DIM_CUBE_MAP),
  gl_target(Texture__dimensionToGLTarget(dimension))
{
  if (!images[0] || !images[0]->isValid())
    throw Error(std::string(getName()) + ": All source images must be valid");

  Image::Type type = images[0]->getType();
  width  = images[0]->getWidth();
  height = images[0]->getHeight();
  depth = 1;

  for (int i = 1; i < 6; ++i)
  {
    if (!images[i] || !images[i]->isValid())
      throw Error(std::string(getName()) + ": All source images must be valid");

    if (images[i]->getType() != type || images[i]->getWidth() != width || images[i]->getHeight() != height)
      throw Error(std::string(getName()) + ": All source images must have identical type and dimensions");
  }

  Format const * bytes_format = toTextureFormat(type);
  setInternalFormat(bytes_format, desired_format);

  doSanityChecks();

  glGenTextures(1, &gl_id);
  DGP_CHECK_GL_OK

  { GLScope scope(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
    GLClientScope client_scope(GL_CLIENT_PIXEL_STORE_BIT);

    gl_target = Texture__dimensionToGLTarget(dimension);
    glEnable(gl_target);
    glBindTexture(gl_target, gl_id);
    DGP_CHECK_GL_OK

    setOptions(options);

    Texture__setDefaultUnpackingOptions(images[0]->getRowAlignment());
    glTexImage(images[0]->getData(), bytes_format, Face::POS_X);

    glPixelStorei(GL_PACK_ALIGNMENT, images[1]->getRowAlignment());
    glTexImage(images[1]->getData(), bytes_format, Face::NEG_X);

    glPixelStorei(GL_PACK_ALIGNMENT, images[2]->getRowAlignment());
    glTexImage(images[2]->getData(), bytes_format, Face::POS_Y);

    glPixelStorei(GL_PACK_ALIGNMENT, images[3]->getRowAlignment());
    glTexImage(images[3]->getData(), bytes_format, Face::NEG_Y);

    glPixelStorei(GL_PACK_ALIGNMENT, images[4]->getRowAlignment());
    glTexImage(images[4]->getData(), bytes_format, Face::POS_Z);

    glPixelStorei(GL_PACK_ALIGNMENT, images[5]->getRowAlignment());
    glTexImage(images[5]->getData(), bytes_format, Face::NEG_Z);
  }
}

Texture::~Texture()
{
  glDeleteTextures(1, &gl_id);
}

void
Texture::glTexImage(void const * bytes, Format const * bytes_format, Face face)
{
  switch (gl_target)
  {
    case GL_TEXTURE_1D:
      glTexImage1D(gl_target, 0, format->openGLFormat, width, 0, bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat,
                   bytes);
      break;

    case GL_TEXTURE_2D:
    case GL_TEXTURE_RECTANGLE_ARB:
      glTexImage2D(gl_target, 0, format->openGLFormat, width, height, 0, bytes_format->openGLBaseFormat,
                   bytes_format->openGLDataFormat, bytes);
      break;

    case GL_TEXTURE_3D:
#ifdef GL_VERSION_1_2  // Apple omits the EXT extension after moving 3D textures to core
      glTexImage3D
#else
      glTexImage3DEXT
#endif
        (gl_target, 0, format->openGLFormat, width, height, depth, 0, bytes_format->openGLBaseFormat,
         bytes_format->openGLDataFormat, bytes);
      break;

    default:  // GL_TEXTURE_CUBE_MAP_ARB
      glTexImage2D(toGLCubeMapFace(face), 0, format->openGLFormat, width, height, 0, bytes_format->openGLBaseFormat,
                   bytes_format->openGLDataFormat, bytes);
  }
  DGP_CHECK_GL_OK
}

void
Texture::setInternalFormat(Format const * bytes_format, Format const * desired_format)
{
  if (desired_format == Format::AUTO())
  {
    if (!bytes_format)
      throw Error(std::string(getName()) + ": Internal format cannot be automatically determined");

    format = bytes_format;
  }
  else
    format = desired_format;

  if (GLCaps::hasBug_redBlueMipmapSwap() && format == Format::RGB8())
    format = Format::RGBA8();

  if (!GLCaps::supportsTexture(format))
    throw Error(std::string(getName()) + ": Texture format not supported");
}

void
Texture::doSanityChecks()
{
  if (dimension == Dimension::DIM_CUBE_MAP && !DGP_SUPPORTS(ARB_texture_cube_map))
    throw Error(std::string(getName()) + ": Cube map textures are not supported");

  if (dimension == Dimension::DIM_RECTANGLE && !DGP_SUPPORTS(ARB_texture_rectangle))
    throw Error(std::string(getName()) + ": Rectangular textures are not supported");

  if (width < 1 || height < 1 || depth < 1)
    throw Error(std::string(getName()) + ": Texture must be at least one pixel wide in each dimension");

  if (depth > 1 && dimension != Dimension::DIM_3D)
    throw Error(std::string(getName()) + ": Only a 3D texture can have depth greater than one pixel");

  if (dimension == Dimension::DIM_1D && (height > 1 || depth > 1))
    throw Error(std::string(getName()) + ": A 1D texture cannot have height or depth greater than one pixel");

  if (!(Math::isPowerOf2(width) && Math::isPowerOf2(height) && Math::isPowerOf2(depth)) && dimension != Dimension::DIM_RECTANGLE
   && !DGP_SUPPORTS(ARB_texture_non_power_of_two))  // rectangular textures can be npot by the spec
    throw Error(std::string(getName()) + ": Non-power-of-two textures are not supported");
}

void
Texture::setOptions(Options const & options)
{
  if (dimension == Dimension::DIM_RECTANGLE && options.wrapMode == WrapMode::TILE)
    throw Error(std::string(getName())
              + ": Tiling is not supported for rectangular textures");  // see GL_ARB_texture_rectangle spec

  GLenum wrap = GL_REPEAT;
  switch (options.wrapMode)
  {
    case WrapMode::CLAMP: wrap = DGP_SUPPORTS(EXT_texture_edge_clamp) ? GL_CLAMP_TO_EDGE : GL_CLAMP; break;
    case WrapMode::TILE: wrap = GL_REPEAT; break;
    case WrapMode::ZERO:
    {
      wrap = DGP_SUPPORTS(ARB_texture_border_clamp) ? GL_CLAMP_TO_BORDER_ARB : GL_CLAMP;
      GLfloat border_color[4] = {0, 0, 0, 1};
      glTexParameterfv(gl_target, GL_TEXTURE_BORDER_COLOR, border_color);
      break;
    }
    default: throw Error(std::string(getName()) + ": Unsupported wrap mode");
  }

  glTexParameteri(gl_target, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(gl_target, GL_TEXTURE_WRAP_T, wrap);

  DGP_CHECK_GL_OK

  bool has_mipmaps = (options.interpolateMode == InterpolateMode::NEAREST_MIPMAP
                   || options.interpolateMode == InterpolateMode::BILINEAR_MIPMAP
                   || options.interpolateMode == InterpolateMode::TRILINEAR);

  if (dimension == Dimension::DIM_RECTANGLE && has_mipmaps)
    throw Error(std::string(getName())
              + ": Mipmapping is not supported for rectangular textures");  // see GL_ARB_texture_rectangle spec

  switch (options.interpolateMode)
  {
    case InterpolateMode::NEAREST_NO_MIPMAP:
      glTexParameteri(gl_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(gl_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      break;

    case InterpolateMode::NEAREST_MIPMAP:
      glTexParameteri(gl_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameteri(gl_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
      break;

    case InterpolateMode::BILINEAR_NO_MIPMAP:
      glTexParameteri(gl_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(gl_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      break;

    case InterpolateMode::BILINEAR_MIPMAP:
      glTexParameteri(gl_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(gl_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
      break;

    case InterpolateMode::TRILINEAR:
      glTexParameteri(gl_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(gl_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      break;

    default: throw Error(std::string(getName()) + ": Unsupported texture interpolation mode");
  }

  DGP_CHECK_GL_OK

  if (has_mipmaps)
  {
    if (DGP_SUPPORTS(SGIS_generate_mipmap))
      glTexParameteri(gl_target, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    else if (GL_VERSION_1_4)  // moved to core in 1.4
      glTexParameteri(gl_target, GL_GENERATE_MIPMAP, GL_TRUE);
    else
    {
      throw Error(std::string(getName()) + ": Automatic mipmap generation not supported");
      // TODO: Implement manual fallback (or replace everything with glGenerateMipmap for new versions of GL).
    }
  }

  DGP_CHECK_GL_OK

  if (DGP_SUPPORTS(ARB_shadow))
  {
    if (options.depthReadMode == DepthReadMode::NORMAL)
    {
      glTexParameteri(gl_target, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
      glTexParameteri(gl_target, GL_TEXTURE_COMPARE_MODE_ARB, GL_NONE);
    }
    else
    {
      glTexParameteri(gl_target, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
      glTexParameteri(gl_target, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
      glTexParameteri(gl_target, GL_TEXTURE_COMPARE_FUNC_ARB,
                      (options.depthReadMode == DepthReadMode::LEQUAL) ? GL_LEQUAL : GL_GEQUAL);
    }
  }
  else if (options.depthReadMode != DepthReadMode::NORMAL)
    throw Error(std::string(getName()) + ": Comparison-based depth read modes are not supported");

  DGP_CHECK_GL_OK
}

void
Texture::updateImage(Image const & image, Face face)
{
  updateImage(image, face, NULL);
}

void
Texture::updateImage(Image const & image, Face face, Options const * options)
{
  if (!image.isValid())
    throw Error(std::string(getName()) + ": Cannot update texture from invalid image");

  { GLScope scope(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
    GLClientScope client_scope(GL_CLIENT_PIXEL_STORE_BIT);

    glEnable(gl_target);
    glBindTexture(gl_target, gl_id);
    DGP_CHECK_GL_OK

    Format const * bytes_format = toTextureFormat(image.getType());
    width  = image.getWidth();
    height = image.getHeight();
    depth  = 1;

    doSanityChecks();

    if (options) setOptions(*options);
    Texture__setDefaultUnpackingOptions(image.getRowAlignment());

    glTexImage(image.getData(), bytes_format, face);
  }
}

void
Texture::updateSubImage(Image const & image, int src_x, int src_y, int src_width, int src_height,
                          int dst_x, int dst_y, int dst_z, Face face)
{
  if (!image.isValid())
    throw Error(std::string(getName()) + ": Cannot update texture from invalid image");

  Format const * bytes_format = toTextureFormat(image.getType());
  int src_depth = 1;

  alwaysAssertM(src_x >= 0 && src_y >= 0
             && src_x + src_width <= image.getWidth() && src_y + src_height <= image.getHeight(),
                std::string(getName()) + ": All or part of subimage lies outside source image boundaries");
  alwaysAssertM(dst_x >= 0 && dst_y >= 0 && dst_z >= 0
             && dst_x + src_width <= width && dst_y + src_height <= height && dst_z + src_depth <= depth,
                std::string(getName()) + ": All or part of subimage lies outside texture boundaries");

  { GLScope scope(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
    GLClientScope client_scope(GL_CLIENT_PIXEL_STORE_BIT);

    glEnable(gl_target);
    glBindTexture(gl_target, gl_id);
    DGP_CHECK_GL_OK

    Texture__setDefaultUnpackingOptions(image.getRowAlignment());
    glPixelStorei(GL_UNPACK_ROW_LENGTH, image.getWidth());
    glPixelStorei(GL_UNPACK_SKIP_ROWS, src_y);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, src_x);

    switch (gl_target)
    {
      case GL_TEXTURE_1D:
        glTexSubImage1D(gl_target, 0, dst_x, (GLsizei)src_width, bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat,
                        image.getData());
        break;

      case GL_TEXTURE_2D:
      case GL_TEXTURE_RECTANGLE_ARB:
        glTexSubImage2D(gl_target, 0, dst_x, dst_y, (GLsizei)src_width, (GLsizei)src_height, bytes_format->openGLBaseFormat,
                        bytes_format->openGLDataFormat, image.getData());
        break;

      case GL_TEXTURE_3D:
#ifdef GL_VERSION_1_2  // Apple omits the EXT extension after moving 3D textures to core
        glTexSubImage3D
#else
        glTexSubImage3DEXT
#endif
          (gl_target, 0, dst_x, dst_y, dst_z, (GLsizei)src_width, (GLsizei)src_height, (GLsizei)src_depth,
           bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat, image.getData());
        break;

      default:  // GL_TEXTURE_CUBE_MAP_ARB
        glTexSubImage2D(toGLCubeMapFace(face), 0, dst_x, dst_y, (GLsizei)src_width, (GLsizei)src_height,
                        bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat, image.getData());
    }
    DGP_CHECK_GL_OK
  }
}

void
Texture::getImage(Image & image, Face face) const
{
  { GLScope scope(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
    GLClientScope client_scope(GL_CLIENT_PIXEL_STORE_BIT);

    glEnable(gl_target);
    glBindTexture(gl_target, gl_id);
    DGP_CHECK_GL_OK

    if (depth > 1) throw Error(std::string(getName()) + ": 3D images are not currently supported");
    image.resize(image.getType(), width, height);

    Format const * bytes_format = toTextureFormat(image.getType());
    Texture__setDefaultPackingOptions(image.getRowAlignment());

    if (gl_target == GL_TEXTURE_CUBE_MAP_ARB)
      glGetTexImage(toGLCubeMapFace(face), 0, bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat, image.getData());
    else
      glGetTexImage(gl_target, 0, bytes_format->openGLBaseFormat, bytes_format->openGLDataFormat, image.getData());

    DGP_CHECK_GL_OK
  }
}

void
Texture::getSubImage(Image & image, int x, int y, int z, int subimage_width, int subimage_height, int subimage_depth,
                       Face face) const
{
  // Until GL gets a GetTexSubImage function...
  throw Error(std::string(getName()) + ": Reading texture subimages is not supported");
}

} // namespace Graphics
} // namespace DGP
