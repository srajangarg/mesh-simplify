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

#ifndef __DGP_Image_hpp__
#define __DGP_Image_hpp__

#include "Common.hpp"
#include "IOStream.hpp"
#include "Serializable.hpp"

namespace DGP {

/** 2D images. */
class DGP_API Image : public Serializable
{
  public:
    /** Different image types (enum class plus extra functions). */
    struct DGP_API Type
    {
      /** Supported values. */
      enum Value
      {
        LUMINANCE_8U,   ///< 8-bit luminance image.
        LUMINANCE_32F,  ///< 32-bit floating-point luminance image.
        LA_8U,          ///< Luminance + alpha, 8 bits per channel.
        LA_32F,         ///< Luminance + alpha, 8-bit floating point per channel.
        RGB_8U,         ///< RGB image, 8 bits per channel.
        RGB_32F,        ///< RGB image, 32-bit floating point per channel.
        RGBA_8U,        ///< RGBA image, 8 bits per channel.
        RGBA_32F,       ///< RGBA image, 32-bit floating point per channel.
        UNKNOWN,        ///< Unknown format.
      };

      DGP_ENUM_CLASS_BODY(Type)

      /**
       * Get the number of channels per pixel. For example: 1 for luminance, 3 for RGB, 4 for RGBA. A complex number corresponds
       * to a single channel (not two). Returns -1 if the image is of unknown type.
       */
      int numChannels() const;

      /** Check if the channels hold floating-point values (at any precision). */
      bool isFloatingPoint() const;

      /** Get the number of bits assigned to each pixel. */
      int getBitsPerPixel() const;

      /** Get the number of bits assigned to each channel. Returns -1 if the channels don't all have the same number of bits. */
      int getBitsPerChannel() const;

    }; // struct Type

    /** Image resampling filters (enum class). */
    struct Filter
    {
      /** Supported values (copied from stb_image_resize). */
      enum Value
      {
        BOX,            ///< A trapezoid with 1-pixel wide ramps, same result as box for integer scale ratios.
        TRIANGLE,       ///< On upsampling, produces same results as bilinear texture filtering.
        CUBIC_BSPLINE,  ///< The cubic b-spline (aka Mitchell-Netrevalli with B=1,C=0), gaussian-esque.
        CATMULL_ROM,    ///< An interpolating cubic spline.
        MITCHELL,       ///< Mitchell-Netrevalli filter with B=1/3, C=1/3.
        AUTO,           ///< Automatically choose an appropriate filter.
      };

      DGP_ENUM_CLASS_BODY(Filter);

    }; // struct Filter

    /** Construct an empty image with no initial data. */
    Image();

    /** Construct an uninitialized image of the specified type and pixel dimensions, which must have valid non-zero values. */
    Image(Type type_, int width_, int height_);

    /**
     * Construct an image by deserializing it from an input stream.
     *
     * @see deserialize()
     */
    Image(BinaryInputStream & input, Codec const & codec = Codec_AUTO());

    /**
     * Construct an image by loading it from a file.
     *
     * @see load()
     */
    Image(std::string const & filename, Codec const & codec = Codec_AUTO());

    /* Copy constructor. */
    Image(Image const & src);

    /** Destructor. */
    ~Image();

    /* Assignment operator. */
    Image & operator=(Image const & src);

    /**
     * Check if the image has been allocated non-zero memory space (hence has valid type and dimensions) or not. An image
     * created by the default constructor is invalid and must be further initialized using deserialize() or a similar function.
     */
    bool isValid() const;

    /**
     * Destroy all image data, resetting the image to an invalid state.
     *
     * @see isValid()
     */
    void clear();

    /** Resize the image, changing its type and dimensions. All previous image data is discarded. */
    void resize(Type type, int width_, int height_);

    /** Get the width of the image in pixels. */
    int getWidth() const { return width; }

    /** Get the height of the image in pixels. */
    int getHeight() const { return height; }

    /** Get the type of the image pixels. */
    Type getType() const { return type; }

    /**
     * Get the number of channels per pixel. For example: 1 for luminance, 3 for RGB, 4 for RGBA. Returns -1 if the image is of
     * unknown type.
     */
    int numChannels() const { return type.numChannels(); }

    /** Check if the channels hold floating-point values (at any precision). */
    bool isFloatingPoint() const { return type.isFloatingPoint(); }

    /** Get the number of bits assigned to each pixel. */
    int getBitsPerPixel() const { return type.getBitsPerPixel(); }

    /** Get the number of bits assigned to each channel. Returns -1 if the channels don't all have the same number of bits. */
    int getBitsPerChannel() const { return type.getBitsPerChannel(); }

    /** Get a pointer to the image data. */
    void const * getData() const { return data; }

    /** Get a pointer to the image data. */
    void * getData() { return data; }

    /** Get a pointer to the beginning of a specified row of pixels. */
    void const * getScanLine(int row) const;

    /** Get a pointer to the beginning of a specified row of pixels. */
    void * getScanLine(int row);

    /**
     * Get the number of bytes consumed by a row of pixels. Rows may be aligned to 32-bit (or other) boundaries for performance
     * reasons, so this is <b>not</b> necessarily equal to the number of pixels in a row times the size of a pixel.
     */
    int getScanWidth() const;

    /** Get the byte alignment of a pixel row. */
    int getRowAlignment() const;

    /**
     * Get the value of a channel of a particular pixel, normalized to the range [0, 1]. The following caveats should be
     * noted:
     *   - Signed integer channels are scaled to the range [-1, 1). E.g. Type::LUMINANCE_16 natively stores values in the range
     *     [-32768, 32767], which is mapped to [1, 1) by dividing by 32768.
     *   - Floating point channels are assumed to be pre-normalized and no further normalization is done.
     *   - For complex channels, the function returns the magnitude of the complex number.
     *   - For single-channel images, the luminance is extracted with Channel::ALPHA.
     *
     * This is a relatively slow way to iterate over pixel values and is provided only for convenience.
     *
     * This function <b>does not support channels smaller than a byte</b> (e.g. Type::LUMINANCE_1U), and returns a value of
     * zero for such images.
     */
    double getNormalizedValue(void const * pixel, int channel) const;

    /** Rescale the image to a new width and height. */
    bool rescale(int new_width, int new_height, Filter filter = Filter::AUTO);

    /**
     * {@inheritDoc}
     *
     * The serialized image is prefixed with a header indicating its encoded size.
     */
    void serialize(BinaryOutputStream & output, Codec const & codec = Codec_AUTO()) const;

    /**
     * {@inheritDoc}
     *
     * The image <b>must</b> have been serialized using the layout specified in serialize().
     */
    void deserialize(BinaryInputStream & input, Codec const & codec = Codec_AUTO());

    /**
     * Save the image to an image file. Unlike serialize(), the file will <b>not</b> have a prefixed header. An exception will
     * be thrown if the image cannot be saved.
     */
    void save(std::string const & filename, Codec const & codec = Codec_AUTO()) const;

    /**
     * Load the image from an image file. Unlike deserialize(), the file should <b>not</b> have a prefixed header. An exception
     * will be thrown if the image cannot be loaded.
     */
    void load(std::string const & filename, Codec const & codec = Codec_AUTO());

    /** <b>[Internal use only]</b> Set the dimensions and data of the image. */
    void _setData(int w, int h, void * data_);

    /** <b>[Internal use only]</b> Set the type of the image. */
    void _setType(Type type_);

  private:
    /** Automatically detect the type of the encoded image and deserialize it appropriately. */
    void deserialize_AUTO(BinaryInputStream & input, bool read_prefixed_info);

    Type type;
    int width;
    int height;
    void * data;
};

/** Abstract base class for all image codecs. */
class DGP_API ImageCodec : public Codec
{
  public:
    /**
     * Serialize an image to a binary output stream. Optionally prefixes extra information about the image block such as its
     * size and type (which may have not been specified in the encoding format itself).
     *
     * @return The number of bytes written (this will include the information field if it was written)
     */
    virtual long serializeImage(Image const & image, BinaryOutputStream & output, bool prefix_info) const = 0;

    /**
     * Deserialize an image from a binary input stream. If the <code>read_prefixed_info</code> parameter is true, extra
     * information about the image block (such as its size and type) will be read first from the input stream. Else, the entire
     * input will be treated as the image block (the size() function of the stream must return the correct value in this case).
     *
     * @see serializeMeshGroup
     */
    virtual void deserializeImage(Image & image, BinaryInputStream & input, bool read_prefixed_info) const = 0;
};

#define DGP_DEF_IMAGE_CODEC_BODY(name, desc)                                                                                  \
    public:                                                                                                                   \
      char const * getName() const { static char const * my_name = desc; return my_name; }                                    \
      long serializeImage(Image const & image, BinaryOutputStream & output, bool prefix_info) const;                          \
      void deserializeImage(Image & image, BinaryInputStream & input, bool read_prefixed_info) const;

#define DGP_DEF_IMAGE_CODEC(name, desc)                                                                                       \
  class DGP_API name : public ImageCodec                                                                                      \
  {                                                                                                                           \
    DGP_DEF_IMAGE_CODEC_BODY(name, desc)                                                                                      \
  };

// TODO: Add options to all the ones that support them
DGP_DEF_IMAGE_CODEC(CodecBMP,     "Windows or OS/2 Bitmap File (*.BMP)")
DGP_DEF_IMAGE_CODEC(CodecGIF,     "Graphics Interchange Format (*.GIF)")
DGP_DEF_IMAGE_CODEC(CodecHDR,     "High Dynamic Range (*.HDR)")
DGP_DEF_IMAGE_CODEC(CodecJPEG,    "Independent JPEG Group (*.JPG, *.JIF, *.JPEG, *.JPE)")
DGP_DEF_IMAGE_CODEC(CodecPGMRAW,  "Portable Graymap (BINARY) (*.PGM)")
DGP_DEF_IMAGE_CODEC(CodecPIC,     "Softimage PIC (*.PIC)")
DGP_DEF_IMAGE_CODEC(CodecPNG,     "Portable Network Graphics (*.PNG)")
DGP_DEF_IMAGE_CODEC(CodecPPMRAW,  "Portable Pixelmap (BINARY) (*.PPM)")
DGP_DEF_IMAGE_CODEC(CodecPSD,     "Adobe Photoshop (*.PSD)")
DGP_DEF_IMAGE_CODEC(CodecTARGA,   "Truevision Targa files (*.TGA, *.TARGA)")

} // namespace DGP

#endif
