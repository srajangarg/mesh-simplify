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

#include "RenderSystem.hpp"
#include "GLCaps.hpp"
#include "GLHeaders.hpp"
#include "Texture.hpp"

namespace DGP {
namespace Graphics {

// Convert a RenderSystem primitive to the corresponding OpenGL enum.
static GLenum
RenderSystem__primitiveToGLenum(RenderSystem::Primitive primitive)
{
  switch (primitive)
  {
    case RenderSystem::Primitive::POINTS:         return GL_POINTS;
    case RenderSystem::Primitive::LINES:          return GL_LINES;
    case RenderSystem::Primitive::LINE_STRIP:     return GL_LINE_STRIP;
    case RenderSystem::Primitive::LINE_LOOP:      return GL_LINE_LOOP;
    case RenderSystem::Primitive::TRIANGLES:      return GL_TRIANGLES;
    case RenderSystem::Primitive::TRIANGLE_STRIP: return GL_TRIANGLE_STRIP;
    case RenderSystem::Primitive::TRIANGLE_FAN:   return GL_TRIANGLE_FAN;
    case RenderSystem::Primitive::QUADS:          return GL_QUADS;
    case RenderSystem::Primitive::QUAD_STRIP:     return GL_QUAD_STRIP;
    case RenderSystem::Primitive::POLYGON:        return GL_POLYGON;
  }

  throw Error("RenderSystem: Unknown primitive");
}

// Convert a RenderSystem depth test to the corresponding OpenGL enum.
static GLenum
RenderSystem__depthTestToGLenum(RenderSystem::DepthTest depth_test)
{
  switch (depth_test)
  {
    case RenderSystem::DepthTest::GREATER     : return GL_GREATER;
    case RenderSystem::DepthTest::LESS        : return GL_LESS;
    case RenderSystem::DepthTest::GEQUAL      : return GL_GEQUAL;
    case RenderSystem::DepthTest::LEQUAL      : return GL_LEQUAL;
    case RenderSystem::DepthTest::NOTEQUAL    : return GL_NOTEQUAL;
    case RenderSystem::DepthTest::EQUAL       : return GL_EQUAL;
    case RenderSystem::DepthTest::ALWAYS_PASS : return GL_ALWAYS;
    case RenderSystem::DepthTest::NEVER_PASS  : return GL_NEVER;
  }

  throw Error("RenderSystem: Unknown depth test");
}

RenderSystem::RenderSystem(char const * name_)
: name(name_), current_framebuffer(NULL), current_shader(NULL)
{
  GLCaps::init();

  if (!DGP_SUPPORTS(ARB_texture_non_power_of_two))
    DGP_WARNING << getName() << ": Non-power-of-two textures are not supported";

  if (!DGP_SUPPORTS(ARB_vertex_buffer_object))
    DGP_WARNING << getName() << ": Vertex/index buffers in GPU memory are not supported";

  if (!DGP_SUPPORTS(ARB_shader_objects))
    DGP_WARNING << getName() << ": Programmable shaders are not supported";

  if (!DGP_SUPPORTS(EXT_framebuffer_object))
    DGP_WARNING << getName() << ": Framebuffer objects are not supported";

  glDisable(GL_LIGHTING);
  setCullFace(CullFace::NONE);
  setDepthTest(DepthTest::LESS);
  DGP_CHECK_GL_OK
}

RenderSystem::~RenderSystem()
{
  for (FramebufferSet::const_iterator fi = created_framebuffers.begin(); fi != created_framebuffers.end(); ++fi)
    delete *fi;

  created_framebuffers.clear();

  for (TextureSet::const_iterator ti = created_textures.begin(); ti != created_textures.end(); ++ti)
    delete *ti;

  created_textures.clear();

  for (ShaderSet::const_iterator si = created_shaders.begin(); si != created_shaders.end(); ++si)
    delete *si;

  created_shaders.clear();

  for (VARAreaSet::const_iterator vi = created_varareas.begin(); vi != created_varareas.end(); ++vi)
    delete *vi;

  created_varareas.clear();
}

char const *
RenderSystem::describeSystem() const
{
  desc = GLCaps::describeSystem();
  return desc.c_str();
}

Framebuffer *
RenderSystem::createFramebuffer(char const * name_)
{
  Framebuffer * fb = new Framebuffer(this, name_);
  if (fb)
    created_framebuffers.insert(fb);

  return fb;
}

void
RenderSystem::destroyFramebuffer(Framebuffer * framebuffer)
{
  if (!framebuffer)
    return;

  if (created_framebuffers.erase(framebuffer) < 1)
  {
    DGP_ERROR << getName() << ": Attempting to destroy framebuffer '" << framebuffer->getName()
               << "' which was not created using this rendersystem";
    return;
  }

  delete framebuffer;
}

Shader *
RenderSystem::createShader(char const * name_)
{
  Shader * shader = new Shader(this, name_);
  if (shader)
    created_shaders.insert(shader);

  return shader;
}

void
RenderSystem::destroyShader(Shader * shader)
{
  if (!shader)
    return;

  if (created_shaders.erase(shader) < 1)
  {
    DGP_ERROR << getName() << ": Attempting to destroy shader '" << shader->getName()
               << "' which was not created using this rendersystem";
    return;
  }

  delete shader;
}

Texture *
RenderSystem::createTexture(char const * name_, int width, int height, int depth, Texture::Format const * desired_format,
                            Texture::Dimension dimension, Texture::Options const & options)
{
  Texture * tex = new Texture(this, name_, width, height, depth, desired_format, dimension, options);
  if (tex)
    created_textures.insert(tex);

  return tex;
}

Texture *
RenderSystem::createTexture(char const * name_, Image const & image, Texture::Format const * desired_format,
                            Texture::Dimension dimension, Texture::Options const & options)
{
  Texture * tex = new Texture(this, name_, image, desired_format, dimension, options);
  if (tex)
    created_textures.insert(tex);

  return tex;
}

Texture *
RenderSystem::createTexture(char const * name_, Image const * images[6], Texture::Format const * desired_format,
                            Texture::Options const & options)
{
  Texture * tex = new Texture(this, name_, images, desired_format, options);
  if (tex)
    created_textures.insert(tex);

  return tex;
}

void
RenderSystem::destroyTexture(Texture * texture)
{
  if (!texture)
    return;

  if (created_textures.erase(texture) < 1)
  {
    DGP_ERROR << getName() << ": Attempting to destroy texture '" << texture->getName()
               << "' which was not created using this rendersystem";
    return;
  }

  delete texture;
}

VARArea *
RenderSystem::createVARArea(char const * name_, long num_bytes, VARArea::Usage usage, bool gpu_memory)
{
  VARArea * vararea = new VARArea(this, name_, num_bytes, usage, gpu_memory);
  if (vararea)
    created_varareas.insert(vararea);

  return vararea;
}

void
RenderSystem::destroyVARArea(VARArea * area)
{
  if (!area)
    return;

  if (created_varareas.erase(area) < 1)
  {
    DGP_ERROR << getName() << ": Attempting to destroy VAR area '" << area->getName()
               << "' which was not created using this rendersystem";
    return;
  }

  delete area;
}

void
RenderSystem::pushFramebuffer()
{
  glPushAttrib(GL_VIEWPORT_BIT | GL_COLOR_BUFFER_BIT);
  DGP_CHECK_GL_OK

  framebuffer_stack.push(current_framebuffer);
}

void
RenderSystem::setFramebuffer(Framebuffer * framebuffer)
{
  if (framebuffer)
  {
    if (framebuffer != current_framebuffer)
    {
      framebuffer->use();
      current_framebuffer = framebuffer;
    }
  }
  else
  {
    if (current_framebuffer)
    {
      glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
      current_framebuffer = NULL;
      DGP_CHECK_GL_OK
    }
  }
}

Framebuffer const *
RenderSystem::getFramebuffer() const
{
  return current_framebuffer;
}

Framebuffer *
RenderSystem::getFramebuffer()
{
  return current_framebuffer;
}

void
RenderSystem::popFramebuffer()
{
  alwaysAssertM(!framebuffer_stack.empty(), std::string(getName()) + ": No framebuffer to pop");

  Framebuffer * fb = framebuffer_stack.top();
  framebuffer_stack.pop();
  setFramebuffer(fb);

  glPopAttrib();
  DGP_CHECK_GL_OK
}

void
RenderSystem::pushShader()
{
  shader_stack.push(current_shader);
  pushTextures();  // since binding a shader can overwrite current texture bindings
}

void
RenderSystem::setShader(Shader * shader)
{
  alwaysAssertM(DGP_SUPPORTS(ARB_shader_objects),
                std::string(getName()) + ": This OpenGL installation does not support shader objects");

  if (shader)
  {
    if (shader != current_shader)
    {
      shader->use();
      current_shader = shader;
    }
  }
  else
  {
    if (current_shader)
    {
      glUseProgramObjectARB(0);
      current_shader = NULL;
      DGP_CHECK_GL_OK
    }
  }
}

Shader const *
RenderSystem::getShader() const
{
  return current_shader;
}

Shader *
RenderSystem::getShader()
{
  return current_shader;
}

void
RenderSystem::popShader()
{
  debugAssertM(!shader_stack.empty(), std::string(getName()) + ": push/popShader calls not matched");

  popTextures();  // must be called before binding shader below

  setShader(shader_stack.top());
  shader_stack.pop();
}

void
RenderSystem::pushTextures()
{
  glPushAttrib(GL_TEXTURE_BIT | GL_ENABLE_BIT);  // Can we do without ENABLE_BIT? The doc is unclear.
}

void
RenderSystem::setTexture(int texunit, Texture * texture)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glActiveTextureARB(GL_TEXTURE0_ARB + texunit);
  else if (texunit != 0)
    throw Error(std::string(getName()) + ": Non-zero texture unit specified but multitexturing is not supported by OpenGL");

  if (texture)
  {
    GLenum target = texture->getGLTarget();
    GLuint id     = texture->getGLID();

    glEnable(target);
    glBindTexture(target, id);
  }
  else
  {
    // Disable the texture unit
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_3D);
    glDisable(GL_TEXTURE_CUBE_MAP_ARB);
    glDisable(GL_TEXTURE_RECTANGLE_ARB);
  }

  DGP_CHECK_GL_OK
}

void
RenderSystem::popTextures()
{
  glPopAttrib();
}

void
RenderSystem::beginIndexedPrimitives()
{
  buffer_stack.push(current_buffer_state);
  current_buffer_state = BufferState();

  glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
}

void
RenderSystem::setVertexAreaFromVAR(VAR const & v)
{
  alwaysAssertM(!current_buffer_state.vertex_area || (v.getArea() == current_buffer_state.vertex_area),
      std::string(getName()) + ": All vertex arrays used within a single begin/endIndexedPrimitives block must share the same VARArea");

  if (v.getArea() != current_buffer_state.vertex_area)
  {
    current_buffer_state.vertex_area = const_cast<VAR &>(v).getArea();
    if (current_buffer_state.vertex_area->inGPUMemory())
      glBindBufferARB(GL_ARRAY_BUFFER_ARB, current_buffer_state.vertex_area->getGLBuffer());
  }
}

void
RenderSystem::setIndexAreaFromVAR(VAR const & v)
{
  alwaysAssertM(!current_buffer_state.index_area || (v.getArea() == current_buffer_state.index_area),
                std::string(getName())
              + ": All index arrays used within a single begin/endIndexedPrimitives block must share the same VARArea");

  if (v.getArea() != current_buffer_state.index_area)
  {
    current_buffer_state.index_area = const_cast<VAR &>(v).getArea();
    if (current_buffer_state.index_area->inGPUMemory())
      glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, current_buffer_state.index_area->getGLBuffer());
  }
}

void
RenderSystem::setVertexArray(VAR const * vertices)
{
  if (vertices)
  {
    assert(vertices->isValid());
    assert(vertices->getGLType() != GL_UNSIGNED_BYTE
        && vertices->getGLType() != GL_UNSIGNED_SHORT
        && vertices->getGLType() != GL_UNSIGNED_INT);

    setVertexAreaFromVAR(*vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(vertices->getNumComponents(), vertices->getGLType(), vertices->getElementSize(),
                    vertices->getBasePointer());
  }
  else
    glDisableClientState(GL_VERTEX_ARRAY);
}

void
RenderSystem::setColorArray(VAR const * colors)
{
  if (colors)
  {
    assert(colors->isValid());
    setVertexAreaFromVAR(*colors);
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(colors->getNumComponents(), colors->getGLType(), colors->getElementSize(), colors->getBasePointer());
  }
  else
    glDisableClientState(GL_COLOR_ARRAY);
}

void
RenderSystem::setTexCoordArray(int texunit, VAR const * texcoords)
{
  if (texcoords)
  {
    assert(texcoords->isValid());
    debugAssertM(DGP_SUPPORTS(ARB_multitexture) || (texunit == 0),
                 std::string(getName()) + ": Graphics card does not support multitexture");

    if (DGP_SUPPORTS(ARB_multitexture))
      glClientActiveTextureARB(GL_TEXTURE0_ARB + texunit);

    setVertexAreaFromVAR(*texcoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(texcoords->getNumComponents(), texcoords->getGLType(), texcoords->getElementSize(),
                      texcoords->getBasePointer());

    if (DGP_SUPPORTS(ARB_multitexture))
      glClientActiveTextureARB(GL_TEXTURE0_ARB);
  }
  else
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void
RenderSystem::setNormalArray(VAR const * normals)
{
  if (normals)
  {
    assert(normals->isValid());
    assert(normals->getNumComponents() == 3);
    assert(normals->getGLType() != GL_UNSIGNED_BYTE
        && normals->getGLType() != GL_UNSIGNED_SHORT
        && normals->getGLType() != GL_UNSIGNED_INT);

    setVertexAreaFromVAR(*normals);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(normals->getGLType(), normals->getElementSize(), normals->getBasePointer());
  }
  else
    glDisableClientState(GL_NORMAL_ARRAY);
}

void
RenderSystem::setIndexArray(VAR const * indices)
{
  if (indices)
  {
    assert(indices->isValid());
    assert(indices->getNumComponents() == 1);
    assert(indices->getGLTarget() == GL_ELEMENT_ARRAY_BUFFER_ARB);

    setIndexAreaFromVAR(*indices);
    glEnableClientState(GL_VERTEX_ARRAY);
    current_buffer_state.index_var = *indices;
  }
  else
  {
    current_buffer_state.index_var = VAR();  // an invalid buffer
    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
  }
}

void
RenderSystem::endIndexedPrimitives()
{
  debugAssertM(!buffer_stack.empty(), std::string(getName()) + ": begin/endIndexedPrimitives calls not matched");

  glPopClientAttrib();

  current_buffer_state = buffer_stack.top();
  buffer_stack.pop();
}

RenderSystem::MatrixMode
RenderSystem::getMatrixMode() const
{
  GLint gl_mode;
  glGetIntegerv(GL_MATRIX_MODE, &gl_mode);
  switch (gl_mode)
  {
    case GL_MODELVIEW:   return MatrixMode::MODELVIEW;
    case GL_PROJECTION:  return MatrixMode::PROJECTION;
    case GL_TEXTURE:     return MatrixMode::TEXTURE;
    case GL_COLOR:       return MatrixMode::COLOR;
    default:             throw Error(std::string(getName()) + "Unknown matrix mode");
  }
}

void
RenderSystem::setMatrixMode(MatrixMode mode)
{
  switch (mode)
  {
    case MatrixMode::MODELVIEW:   glMatrixMode(GL_MODELVIEW); break;
    case MatrixMode::PROJECTION:  glMatrixMode(GL_PROJECTION); break;
    case MatrixMode::TEXTURE:     glMatrixMode(GL_TEXTURE); break;
    case MatrixMode::COLOR:       glMatrixMode(GL_COLOR); break;
    default:                      throw Error(std::string(getName()) + "Unsupported matrix mode");
  }
}

void
RenderSystem::pushMatrix()
{
  glPushMatrix();
}

Matrix4
RenderSystem::getMatrix(MatrixMode mode) const
{
  float f[16];
  glGetFloatv((mode == MatrixMode::MODELVIEW ? GL_MODELVIEW_MATRIX : GL_PROJECTION_MATRIX), f);

  DGP_CHECK_GL_OK

  return Matrix4(f[0], f[4], f[ 8], f[12],
                 f[1], f[5], f[ 9], f[13],
                 f[2], f[6], f[10], f[14],
                 f[3], f[7], f[11], f[15]);
}

void
RenderSystem::setMatrix(Matrix4 const & m)
{
  GLfloat f[16];
  m.getElementsColumnMajor(f);
  glLoadMatrixf(f);
}

void
RenderSystem::setIdentityMatrix()
{
  glLoadIdentity();
}

void
RenderSystem::multMatrix(Matrix4 const & m)
{
  GLfloat f[16];
  m.getElementsColumnMajor(f);
  glMultMatrixf(f);
}

void
RenderSystem::popMatrix()
{
  glPopMatrix();
}

void
RenderSystem::sendIndices(Primitive primitive, long num_indices, uint8 const * indices)
{
  glDrawElements(RenderSystem__primitiveToGLenum(primitive), (GLsizei)num_indices, GL_UNSIGNED_BYTE, indices);
}

void
RenderSystem::sendIndices(Primitive primitive, long num_indices, uint16 const * indices)
{
  glDrawElements(RenderSystem__primitiveToGLenum(primitive), (GLsizei)num_indices, GL_UNSIGNED_SHORT, indices);
}

void
RenderSystem::sendIndices(Primitive primitive, long num_indices, uint32 const * indices)
{
  glDrawElements(RenderSystem__primitiveToGLenum(primitive), (GLsizei)num_indices, GL_UNSIGNED_INT, indices);
}

void
RenderSystem::sendSequentialIndices(Primitive primitive, int first_index, int num_indices)
{
  glDrawArrays(RenderSystem__primitiveToGLenum(primitive), first_index, (GLsizei)num_indices);
}

void
RenderSystem::sendIndicesFromArray(Primitive primitive, long offset, long num_indices)
{
  alwaysAssertM(current_buffer_state.index_var.isValid(), std::string(getName()) + ": No valid index array set");

  uint8 * ptr = static_cast<uint8 *>(current_buffer_state.index_var.getBasePointer());
  int elem_size = current_buffer_state.index_var.getElementSize();

  glDrawElements(RenderSystem__primitiveToGLenum(primitive),
                 (GLsizei)num_indices,
                 current_buffer_state.index_var.getGLType(),
                 ptr + offset * elem_size);
}

void
RenderSystem::beginPrimitive(Primitive primitive)
{
  glBegin(RenderSystem__primitiveToGLenum(primitive));
}

void
RenderSystem::sendVertex(Vector2 const & vertex)
{
  glVertex2f(vertex.x(), vertex.y());
}

void
RenderSystem::sendVertex(float x, float y)
{
  glVertex2f(x, y);
}

void
RenderSystem::sendVertex(double x, double y)
{
  glVertex2d(x, y);
}

void
RenderSystem::sendVertex(Vector3 const & vertex)
{
  glVertex3f(vertex.x(), vertex.y(), vertex.z());
}

void
RenderSystem::sendVertex(float x, float y, float z)
{
  glVertex3f(x, y, z);
}

void
RenderSystem::sendVertex(double x, double y, double z)
{
  glVertex3d(x, y, z);
}

void
RenderSystem::sendVertex(Vector4 const & vertex)
{
  glVertex4f(vertex.x(), vertex.y(), vertex.z(), vertex.w());
}

void
RenderSystem::sendVertex(float x, float y, float z, float w)
{
  glVertex4f(x, y, z, w);
}

void
RenderSystem::sendVertex(double x, double y, double z, double w)
{
  glVertex4d(x, y, z, w);
}

void
RenderSystem::setNormal(Vector3 const & normal)
{
  glNormal3f(normal.x(), normal.y(), normal.z());
}

void
RenderSystem::setNormal(float x, float y, float z)
{
  glNormal3f(x, y, z);
}

void
RenderSystem::setNormal(double x, double y, double z)
{
  glNormal3d(x, y, z);
}

void
RenderSystem::setTexCoord(int texunit, float texcoord)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord1fARB(GL_TEXTURE0_ARB + texunit, texcoord);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord1f(texcoord);
  }
}

void
RenderSystem::setTexCoord(int texunit, double texcoord)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord1dARB(GL_TEXTURE0_ARB + texunit, texcoord);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord1d(texcoord);
  }
}

void
RenderSystem::setTexCoord(int texunit, Vector2 const & texcoord)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord2fARB(GL_TEXTURE0_ARB + texunit, (float)texcoord.x(), (float)texcoord.y());
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord2f((float)texcoord.x(), (float)texcoord.y());
  }
}

void
RenderSystem::setTexCoord(int texunit, float x, float y)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord2fARB(GL_TEXTURE0_ARB + texunit, x, y);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord2f(x, y);
  }
}

void
RenderSystem::setTexCoord(int texunit, double x, double y)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord2dARB(GL_TEXTURE0_ARB + texunit, x, y);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord2d(x, y);
  }
}

void
RenderSystem::setTexCoord(int texunit, Vector3 const & texcoord)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord3fARB(GL_TEXTURE0_ARB + texunit, (float)texcoord.x(), (float)texcoord.y(), (float)texcoord.z());
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord3f((float)texcoord.x(), (float)texcoord.y(), (float)texcoord.z());
  }
}

void
RenderSystem::setTexCoord(int texunit, float x, float y, float z)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord3fARB(GL_TEXTURE0_ARB + texunit, x, y, z);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord3f(x, y, z);
  }
}

void
RenderSystem::setTexCoord(int texunit, double x, double y, double z)
{
  if (DGP_SUPPORTS(ARB_multitexture))
    glMultiTexCoord3dARB(GL_TEXTURE0_ARB + texunit, x, y, z);
  else
  {
    debugAssertM(texunit == 0, std::string(getName()) + ": Multitexturing not supported, texture unit must be zero");
    glTexCoord3d(x, y, z);
  }
}

void
RenderSystem::endPrimitive()
{
  glEnd();
}

void
RenderSystem::pushState()
{
  pushFramebuffer();
  pushShader();
  pushTextures();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
}

void
RenderSystem::pushColorFlags()
{
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT);
}

void
RenderSystem::pushDepthFlags()
{
  glPushAttrib(GL_DEPTH_BUFFER_BIT);
}

void
RenderSystem::pushStencilFlags()
{
  glPushAttrib(GL_STENCIL_BUFFER_BIT);
}

void
RenderSystem::pushShapeFlags()
{
  glPushAttrib(GL_POINT_BIT | GL_LINE_BIT | GL_POLYGON_BIT);
}

void
RenderSystem::setColorWrite(bool red, bool green, bool blue, bool alpha)
{
  glColorMask(red, green, blue, alpha);
}

void
RenderSystem::setDepthWrite(bool value)
{
  glDepthMask(value);
}

void
RenderSystem::setStencilWrite(uint32 mask)
{
  glStencilMask((GLuint)mask);
}

void
RenderSystem::setColor(ColorRGB const & value)
{
  glColor3f((GLfloat)value.r(), (GLfloat)value.g(), (GLfloat)value.b());
}

void
RenderSystem::setColor(ColorRGBA const & value)
{
  glColor4f((GLfloat)value.r(), (GLfloat)value.g(), (GLfloat)value.b(), (GLfloat)value.a());
}

void
RenderSystem::setColorClearValue(ColorRGB const & value)
{
  glClearColor((GLclampf)value.r(), (GLclampf)value.g(), (GLclampf)value.b(), 1.0f);
}

void
RenderSystem::setColorClearValue(ColorRGBA const & value)
{
  glClearColor((GLclampf)value.r(), (GLclampf)value.g(), (GLclampf)value.b(), (GLclampf)value.a());
}

void
RenderSystem::setDepthClearValue(Real value)
{
  glClearDepth((GLclampd)value);
}

void
RenderSystem::setStencilClearValue(int value)
{
  glClearStencil(value);
}

void
RenderSystem::clear()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void
RenderSystem::clear(bool color, bool depth, bool stencil)
{
  glClear((color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0));
}

void
RenderSystem::setDepthTest(DepthTest test)
{
  if (test == DepthTest::ALWAYS_PASS)
  {
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);  // just to be safe
    return;
  }
  else
    glEnable(GL_DEPTH_TEST);

  glDepthFunc(RenderSystem__depthTestToGLenum(test));
}

void
RenderSystem::setCullFace(CullFace cull)
{
  if (cull == CullFace::NONE)
  {
    glDisable(GL_CULL_FACE);
    return;
  }
  else
  {
    glEnable(GL_CULL_FACE);
    glCullFace((cull == CullFace::FRONT) ? GL_FRONT : GL_BACK);
  }
}

void
RenderSystem::setPolygonOffset(bool enable, Real offset)
{
  if (enable)
  {
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(offset, offset);
  }
  else
    glDisable(GL_POLYGON_OFFSET_FILL);
}

void
RenderSystem::setPointSize(Real size)
{
  glEnable(GL_POINT_SMOOTH);
  glPointSize((GLfloat)size);
}

void
RenderSystem::popColorFlags()
{
  glPopAttrib();
}

void
RenderSystem::popDepthFlags()
{
  glPopAttrib();
}

void
RenderSystem::popStencilFlags()
{
  glPopAttrib();
}

void
RenderSystem::popShapeFlags()
{
  glPopAttrib();
}

void
RenderSystem::popState()
{
  glPopClientAttrib();
  glPopAttrib();
  popTextures();
  popShader();
  popFramebuffer();
}

void
RenderSystem::finishAllOperations()
{
  glFlush();
}

} // namespace Graphics
} // namespace DGP
