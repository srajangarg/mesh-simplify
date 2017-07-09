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

#ifndef __DGP_Graphics_Framebuffer_hpp__
#define __DGP_Graphics_Framebuffer_hpp__

#include "../Common.hpp"
#include "../NamedObject.hpp"
#include "GLHeaders.hpp"
#include "Texture.hpp"

namespace DGP {
namespace Graphics {

// Forward declarations
class RenderSystem;

/** An interface for a framebuffer. */
class DGP_API Framebuffer : public AbstractNamedObject
{
  public:
    /** Attachment points (enum class). These are guaranteed to be consecutive integers starting from 0. */
    struct DGP_API AttachmentPoint
    {
      /** Supported values. */
      enum Value
      {
        COLOR_0 = 0,  ///< Color buffer attachment point 0.
        COLOR_1,      ///< Color buffer attachment point 1.
        COLOR_2,      ///< Color buffer attachment point 2.
        COLOR_3,      ///< Color buffer attachment point 3.
        COLOR_4,      ///< Color buffer attachment point 4.
        COLOR_5,      ///< Color buffer attachment point 5.
        COLOR_6,      ///< Color buffer attachment point 6.
        COLOR_7,      ///< Color buffer attachment point 7.
        COLOR_8,      ///< Color buffer attachment point 8.
        COLOR_9,      ///< Color buffer attachment point 9.
        COLOR_10,     ///< Color buffer attachment point 10.
        COLOR_11,     ///< Color buffer attachment point 11.
        COLOR_12,     ///< Color buffer attachment point 12.
        COLOR_13,     ///< Color buffer attachment point 13.
        COLOR_14,     ///< Color buffer attachment point 14.
        COLOR_15,     ///< Color buffer attachment point 15.
        DEPTH,        ///< Depth buffer attachment point.
        STENCIL,      ///< Stencil buffer attachment point.
        MAX_ATTACHMENTS  // only for reading the number of elements in the enum
      };

      DGP_ENUM_CLASS_BODY(AttachmentPoint)
    };

    /** Destructor. */
    ~Framebuffer();

    char const * getName() const { return name.c_str(); }

    /** Get the parent rendersystem. */
    RenderSystem * getRenderSystem() const { return render_system; }

    /**
     * Attach a render-texture to an attachment point. Specifying a null texture will cause any existing attachment to be
     * removed.
     */
    void attach(AttachmentPoint ap, Texture * texture, Texture::Face face = Texture::Face::POS_X, int z_offset = 0);

    /** Detach the current attachment at an attachment point. */
    void detach(AttachmentPoint ap);

    /** Remove all current attachments. */
    void detachAll();

    /** Get the width of the framebuffer in pixels. */
    int getWidth() const;

    /** Get the height of the framebuffer in pixels. */
    int getHeight() const;

  private:
    /** Constructor. */
    Framebuffer(RenderSystem * render_system_, char const * name_);

    /** Get the OpenGL ID of the framebuffer object. */
    GLuint getGLID() const { return gl_fbid; }

    /** Use the framebuffer for rendering. */
    void use();

    RenderSystem * render_system;
    std::string name;
    GLuint gl_fbid;
    Texture * attachment_table[AttachmentPoint::MAX_ATTACHMENTS];
    int num_attachments;
    std::vector<GLenum> gl_draw_buffers;
    int width;
    int height;

    friend class RenderSystem;

}; // class Framebuffer

} // namespace Graphics
} // namespace DGP

#endif
