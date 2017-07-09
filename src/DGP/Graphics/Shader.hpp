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

#ifndef __DGP_Graphics_Shader_hpp__
#define __DGP_Graphics_Shader_hpp__

#include "../Common.hpp"
#include "../Colors.hpp"
#include "../MatrixMN.hpp"
#include "../VectorN.hpp"
#include "../NamedObject.hpp"
#include "Texture.hpp"
#include "GLHeaders.hpp"
#include <map>

namespace DGP {
namespace Graphics {

/** An interface for a shader. */
class DGP_API Shader : public AbstractNamedObject
{
  public:
    /** %Shader module types (enum class). */
    struct DGP_API ModuleType
    {
      /** Supported values. */
      enum Value
      {
        VERTEX    =  0,  ///< Vertex shader.
        FRAGMENT  =  1,  ///< Fragment (pixel) shader.
        GEOMETRY  =  2   ///< Geometry shader.
      };

      DGP_ENUM_CLASS_BODY(ModuleType)
    };

    /** Destructor. */
    ~Shader();

    char const * getName() const { return name.c_str(); }

    /** Get the parent rendersystem. */
    RenderSystem * getRenderSystem() const { return render_system; }

    /**
     * Check if the shader is ready to be used for rendering or not. Typically this requires both a vertex and a fragment
     * program to be attached.
     */
    bool isComplete() const;

    /** Attach a program module to the shader from a file containing its source code. */
    void attachModuleFromFile(ModuleType type, char const * path);

    /** Attach a program module to the shader from a string containing its source code. */
    void attachModuleFromString(ModuleType type, char const * source);

    /** Check if the shader has an active uniform of the given name. */
    bool hasUniform(char const * uniform_name) const;

    /** Set a floating-point uniform. */
    void setUniform(char const * uniform_name, float value);

    /** Set an integer uniform. */
    void setUniform(char const * uniform_name, int value);

    /** Set a 2-vector uniform. */
    void setUniform(char const * uniform_name, Vector2 const & value);

    /** Set a 3-vector uniform. */
    void setUniform(char const * uniform_name, Vector3 const & value);

    /** Set a 4-vector uniform. */
    void setUniform(char const * uniform_name, Vector4 const & value);

    /** Set a single-channel byte color uniform. */
    void setUniform(char const * uniform_name, ColorL8 const & value);

    /** Set a single-channel floating-point color uniform. */
    void setUniform(char const * uniform_name, ColorL const & value);

    /** Set a 3-channel byte color uniform. */
    void setUniform(char const * uniform_name, ColorRGB8 const & value);

    /** Set a 3-channel floating-point color uniform. */
    void setUniform(char const * uniform_name, ColorRGB const & value);

    /** Set a 4-channel byte color uniform. */
    void setUniform(char const * uniform_name, ColorRGBA8 const & value);

    /** Set a 4-channel floating-point color uniform. */
    void setUniform(char const * uniform_name, ColorRGBA const & value);

    /** Set a 2x2 matrix uniform. */
    void setUniform(char const * uniform_name, Matrix2 const & value);

    /** Set a 3x3 matrix uniform. */
    void setUniform(char const * uniform_name, Matrix3 const & value);

    /** Set a 4x4 matrix uniform. */
    void setUniform(char const * uniform_name, Matrix4 const & value);

    /** Set a texture uniform. */
    void setUniform(char const * uniform_name, Texture * value);

    /** Set a floating-point array uniform. */
    void setUniform(char const * uniform_name, long num_values, float const * values);

    /** Set an integer array uniform. */
    void setUniform(char const * uniform_name, long num_values, int const * values);

    /** Set a 2-vector array uniform. */
    void setUniform(char const * uniform_name, long num_values, Vector2 const * values);

    /** Set a 3-vector array uniform. */
    void setUniform(char const * uniform_name, long num_values, Vector3 const * values);

    /** Set a 4-vector array uniform. */
    void setUniform(char const * uniform_name, long num_values, Vector4 const * values);

    /** Set a single-channel byte color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorL8 const * values);

    /** Set a single-channel floating-point color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorL const * values);

    /** Set a 3-channel byte color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorRGB8 const * values);

    /** Set a 3-channel floating-point color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorRGB const * values);

    /** Set a 4-channel byte color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorRGBA8 const * values);

    /** Set a 4-channel floating-point color array uniform. */
    void setUniform(char const * uniform_name, long num_values, ColorRGBA const * values);

    /** Set a 2x2 matrix array uniform. */
    void setUniform(char const * uniform_name, long num_values, Matrix2 const * values);

    /** Set a 3x3 matrix array uniform. */
    void setUniform(char const * uniform_name, long num_values, Matrix3 const * values);

    /** Set a 4x4 matrix array uniform. */
    void setUniform(char const * uniform_name, long num_values, Matrix4 const * values);

    /** Set a texture array uniform. */
    void setUniform(char const * uniform_name, long num_values, Texture * const * values);

  private:
    /** A value for a uniform variable. */
    struct UniformValue
    {
      float f_val;
      int i_val;
      std::vector<float> f_array;
      std::vector<int> i_array;
      Texture * texture;
    };

    /** Data related to an uniform variable. */
    struct UniformData
    {
      GLenum type;
      GLint size;
      GLint location;
      int texunit;
      bool has_value;
      UniformValue value;
      bool requires_rebind;

      /** Constructor. */
      UniformData() : has_value(false), requires_rebind(false) {}

      /** Note that the value has been changed. */
      void valueChanged() { has_value = true; requires_rebind = true; }
    };

    /** A set of uniforms read from source code. */
    typedef std::map<std::string, UniformData> Uniforms;

    /** Constructor. */
    Shader(RenderSystem * render_system_, char const * name_);

    /** Link the various modules of the shader into a single program. */
    void link();

    /** Use the shader for rendering. */
    void use();

    /** Get the OpenGL ID of the shader. */
    GLhandleARB getGLID() const { return program_id; }

    /** Read the list of active uniforms in the shader object. */
    void readActiveUniforms();

    /** Bind the user-provided uniforms to the shader object. */
    void bindUniforms();

    /** Check if a build step (compile or link) succeeded, and throw a custom error if it did not. */
    void checkBuildStatus(GLhandleARB obj_id, GLenum status_field, std::string const & error_msg);

    RenderSystem * render_system;
    std::string name;
    bool complete;
    bool linked;
    bool has_vertex_module;
    bool has_fragment_module;
    GLhandleARB program_id;
    Uniforms uniforms;

    friend class RenderSystem;

}; // class Shader

} // namespace Graphics
} // namespace DGP

#endif
