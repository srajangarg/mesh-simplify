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

#include "Image.hpp"
#include "FilePath.hpp"
#include "stb_image.hpp"
#include "stb_image_resize.hpp"
#include "stb_image_write.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <unordered_map>

namespace DGP {

namespace ImageInternal {

Image::Type
typeFromNumChannelsAndBPC(int num_channels, int bpc)
{
  if (bpc != 8 && bpc != 32)
    return Image::Type::UNKNOWN;

  switch (num_channels)
  {
    case 1: return (bpc == 8 ? Image::Type::LUMINANCE_8U : Image::Type::LUMINANCE_32F);
    case 2: return (bpc == 8 ? Image::Type::LA_8U : Image::Type::LA_32F);
    case 3: return (bpc == 8 ? Image::Type::RGB_8U : Image::Type::RGB_32F);
    case 4: return (bpc == 8 ? Image::Type::RGBA_8U : Image::Type::RGBA_32F);
    default: return Image::Type::UNKNOWN;
  }
}

void
writeImageChunk(void * buffer, void * data, int size)
{
  if (!buffer)
    return;

  uint8 const * in = static_cast<uint8 const *>(data);
  std::vector<uint8> * out = static_cast<std::vector<uint8> *>(buffer);

  out->insert(out->end(), in, in + size);
}

typedef std::unordered_map<std::string, ImageCodec const *> CodecMap;
CodecMap codec_map;

static ImageCodec const *
initCodecMap()
{
  codec_map["BMP"  ] = new CodecBMP();
  codec_map["GIF"  ] = new CodecGIF();
  codec_map["HDR"  ] = new CodecHDR();
  codec_map["JPG"  ] = new CodecJPEG();
  codec_map["JIF"  ] = new CodecJPEG();
  codec_map["JPEG" ] = new CodecJPEG();
  codec_map["JPE"  ] = new CodecJPEG();
  codec_map["PGM"  ] = new CodecPGMRAW();
  codec_map["PIC"  ] = new CodecPIC();
  codec_map["PNG"  ] = new CodecPNG();
  codec_map["PPM"  ] = new CodecPPMRAW();
  codec_map["PSD"  ] = new CodecPSD();
  codec_map["TGA"  ] = new CodecTARGA();
  codec_map["TARGA"] = new CodecTARGA();

  return NULL;
}

static ImageCodec const *
codecFromPath(std::string const & path)
{
  static ImageCodec const * UNKNOWN_CODEC = initCodecMap();

  CodecMap::const_iterator existing = codec_map.find(toUpper(FilePath::extension(path)));
  if (existing == codec_map.end())
    return UNKNOWN_CODEC;
  else
    return existing->second;
}

} // namespace ImageInternal

#define DGP_DEF_SERIALIZE_IMAGE(codec)                                                                                        \
long                                                                                                                          \
codec::serializeImage(Image const & image, BinaryOutputStream & output, bool prefix_info) const                               \
{                                                                                                                             \
  int w = image.getWidth();                                                                                                   \
  int h = image.getHeight();                                                                                                  \
  int nchannels = image.numChannels();                                                                                        \
  std::vector<uint8> buffer;                                                                                                  \
  if (image.isFloatingPoint())                                                                                                \
  {                                                                                                                           \
    float const * data = (float const *)image.getData();                                                                      \
    if (dynamic_cast<CodecHDR const *>(this))                                                                                 \
      stbi_write_hdr_to_func(&ImageInternal::writeImageChunk, &buffer, w, h, nchannels, data);                                \
    else                                                                                                                      \
      throw Error(std::string(getName()) + ": Cannot write floating-point image to non-HDR format");                          \
  }                                                                                                                           \
  else                                                                                                                        \
  {                                                                                                                           \
    uint8 const * data = (uint8 const *)image.getData();                                                                      \
    if (dynamic_cast<CodecBMP const *>(this))                                                                                 \
      stbi_write_bmp_to_func(&ImageInternal::writeImageChunk, &buffer, w, h, nchannels, data);                                \
    else if (dynamic_cast<CodecPNG const *>(this))                                                                            \
      stbi_write_png_to_func(&ImageInternal::writeImageChunk, &buffer, w, h, nchannels, data, image.getScanWidth());          \
    else if (dynamic_cast<CodecTARGA const *>(this))                                                                          \
      stbi_write_tga_to_func(&ImageInternal::writeImageChunk, &buffer, w, h, nchannels, data);                                \
    else if (dynamic_cast<CodecHDR const *>(this))                                                                            \
      throw Error(std::string(getName()) + ": Cannot write 8-bit images");                                                    \
    else                                                                                                                      \
      throw Error(std::string(getName()) + ": Serialization not supported");                                                  \
  }                                                                                                                           \
                                                                                                                              \
  int64 size_in_bytes = (int64)buffer.size();                                                                                 \
  if (prefix_info)                                                                                                            \
  {                                                                                                                           \
    output.setEndianness(Endianness::LITTLE);                                                                                 \
    output.writeUInt64((uint64)size_in_bytes);                                                                                \
  }                                                                                                                           \
                                                                                                                              \
  output.writeBytes(size_in_bytes, &buffer[0]);                                                                               \
                                                                                                                              \
  return (long)(prefix_info ? size_in_bytes + 4 : size_in_bytes);                                                             \
}

DGP_DEF_SERIALIZE_IMAGE(CodecBMP)
DGP_DEF_SERIALIZE_IMAGE(CodecGIF)
DGP_DEF_SERIALIZE_IMAGE(CodecHDR)
DGP_DEF_SERIALIZE_IMAGE(CodecJPEG)
DGP_DEF_SERIALIZE_IMAGE(CodecPGMRAW)
DGP_DEF_SERIALIZE_IMAGE(CodecPIC)
DGP_DEF_SERIALIZE_IMAGE(CodecPNG)
DGP_DEF_SERIALIZE_IMAGE(CodecPPMRAW)
DGP_DEF_SERIALIZE_IMAGE(CodecPSD)
DGP_DEF_SERIALIZE_IMAGE(CodecTARGA)

#define DGP_DEF_DESERIALIZE_IMAGE(codec)                                                                                      \
void                                                                                                                          \
codec::deserializeImage(Image & image, BinaryInputStream & input, bool read_prefixed_info) const                              \
{                                                                                                                             \
  /* Get the size of the image block in bytes */                                                                              \
  input.setEndianness(Endianness::LITTLE);                                                                                    \
  uint64 size = read_prefixed_info ? input.readUInt64() : input.size();                                                       \
                                                                                                                              \
  /* Read the image block into a memory buffer (optimization possible when the data has already been buffered within the */   \
  /* input stream?)  */                                                                                                       \
  std::vector<uint8> img_block((size_t)size);                                                                                 \
  input.readBytes((int64)size, &img_block[0]);                                                                                \
                                                                                                                              \
  /* Decode the image (ignore the supplied codec) */                                                                          \
  stbi_uc const * buffer = (stbi_uc const *)(&img_block[0]);                                                                  \
  int bpc = 8;                                                                                                                \
  if (stbi_is_hdr_from_memory(buffer, (int)size))                                                                                         \
    bpc = 32;                                                                                                                 \
                                                                                                                              \
  int w, h, nchannels;                                                                                                        \
  void * data = NULL;                                                                                                         \
  if (bpc == 32)                                                                                                              \
    data = (void *)stbi_loadf_from_memory(buffer, (int)size, &w, &h, &nchannels, 0);                                          \
  else                                                                                                                        \
    data = (void *)stbi_load_from_memory(buffer, (int)size, &w, &h, &nchannels, 0);                                           \
                                                                                                                              \
  if (!data)                                                                                                                  \
    throw Error(std::string(getName()) + ": Could not decode image from memory stream");                                      \
                                                                                                                              \
  Image::Type type = ImageInternal::typeFromNumChannelsAndBPC(nchannels, bpc);                                                \
  if (type == Image::Type::UNKNOWN)                                                                                           \
  {                                                                                                                           \
    throw Error(std::string(getName())                                                                                        \
            + ": Image was successfully decoded but it has a format for which this library does not provide an interface");   \
  }                                                                                                                           \
                                                                                                                              \
  image.clear();                                                                                                              \
  image._setType(type);                                                                                                       \
  image._setData(w, h, data);                                                                                                 \
}

DGP_DEF_DESERIALIZE_IMAGE(CodecBMP)
DGP_DEF_DESERIALIZE_IMAGE(CodecGIF)
DGP_DEF_DESERIALIZE_IMAGE(CodecHDR)
DGP_DEF_DESERIALIZE_IMAGE(CodecJPEG)
DGP_DEF_DESERIALIZE_IMAGE(CodecPGMRAW)
DGP_DEF_DESERIALIZE_IMAGE(CodecPIC)
DGP_DEF_DESERIALIZE_IMAGE(CodecPNG)
DGP_DEF_DESERIALIZE_IMAGE(CodecPPMRAW)
DGP_DEF_DESERIALIZE_IMAGE(CodecPSD)
DGP_DEF_DESERIALIZE_IMAGE(CodecTARGA)

int
Image::Type::numChannels() const
{
  switch (value)
  {
    case LA_8U     :
    case LA_32F    :  return 2;

    case RGB_8U    :
    case RGB_32F   :  return 3;

    case RGBA_8U   :
    case RGBA_32F  :  return 4;

    default        :  return 1;
  }
}

bool
Image::Type::isFloatingPoint() const
{
  return value == LUMINANCE_32F
      || value == LA_32F
      || value == RGB_32F
      || value == RGBA_32F;
}

int
Image::Type::getBitsPerPixel() const
{
  // Currently all supported types have the same number of bits per channel
  return numChannels() * getBitsPerChannel();
}

int
Image::Type::getBitsPerChannel() const
{
  // Currently all supported types have the same number of bits per channel
  if (isFloatingPoint())
    return 32;
  else
    return 8;
}

Image::Image()
: type(Type::UNKNOWN), width(0), height(0), data(NULL)
{
}

Image::Image(Type type_, int width_, int height_)
: type(Type::UNKNOWN), width(0), height(0), data(NULL)
{
  resize(type_, width_, height_);
}

Image::Image(BinaryInputStream & input, Codec const & codec)
: type(Type::UNKNOWN), width(0), height(0), data(NULL)
{
  deserialize(input, codec);
}

Image::Image(std::string const & filename, Codec const & codec)
: type(Type::UNKNOWN), width(0), height(0), data(NULL)
{
  load(filename, codec);
}

Image::Image(Image const & src)
: type(Type::UNKNOWN), width(0), height(0), data(NULL)
{
  *this = src;
}

Image &
Image::operator=(Image const & src)
{
  clear();
  if (!src.data)
    return *this;

  size_t num_bytes = (size_t)(src.getWidth() * src.getHeight() * (src.getBitsPerPixel() / 8));
  data = std::malloc(num_bytes);  // assumes stbi also uses malloc
  if (!data)
    throw Error("Image: Could not allocate pixel buffer");

  std::memcpy(data, src.data, num_bytes);

  type = src.type;
  width = src.getWidth();
  height = src.getHeight();

  return *this;
}

Image::~Image()
{
  if (data)
    stbi_image_free(data);
}

bool
Image::isValid() const
{
  return (type != Type::UNKNOWN && data != NULL && width > 0 && height > 0);
}

void
Image::clear()
{
  if (data)
    stbi_image_free(data);

  width = height = 0;
  type = Type::UNKNOWN;
}

void
Image::resize(Type type_, int width_, int height_)
{
  if (type_ == Type::UNKNOWN || width_ <= 0 || height_ <= 0)
    throw Error("Cannot resize image to unknown type or non-positive size (use clear() function to destroy data)");

  if (type_ == type && width_ == getWidth() && height_ == getHeight())
    return;

  clear();

  size_t num_bytes = (size_t)(width_ * height_ * (type_.getBitsPerPixel() / 8));
  data = std::malloc(num_bytes);  // assumes stbi uses malloc
  if (!data)
    throw Error("Image: Could not resize pixel buffer");

  type = type_;
  width = width_;
  height = height_;

  if (!isValid())
    throw Error("Could not resize the image to the specified type and dimensions");
}

double
Image::getNormalizedValue(void const * pixel, int channel) const
{
  switch (type)
  {
    case Image::Type::LUMINANCE_8U  : return channel == 0 ? *((uint8 const *)pixel) / 255.0 : 0.0;
    case Image::Type::LUMINANCE_32F : return channel == 0 ? *((float32 const *)pixel) : 0.0;

    case Image::Type::LA_8U         : return (channel >= 0 && channel < 2) ? ((uint8   const *)pixel)[channel] / 255.0 : 0.0;
    case Image::Type::LA_32F        : return (channel >= 0 && channel < 2) ? ((float32 const *)pixel)[channel] : 0.0;

    case Image::Type::RGB_8U        : return (channel >= 0 && channel < 3) ? ((uint8   const *)pixel)[channel] / 255.0 : 0.0;
    case Image::Type::RGB_32F       : return (channel >= 0 && channel < 3) ? ((float32 const *)pixel)[channel] : 0.0;

    case Image::Type::RGBA_8U       : return (channel >= 0 && channel < 4) ? ((uint8   const *)pixel)[channel] / 255.0 : 0.0;
    case Image::Type::RGBA_32F      : return (channel >= 0 && channel < 4) ? ((float32 const *)pixel)[channel] : 0.0;

    default                         : return 0.0;
  }
}

void const *
Image::getScanLine(int row) const
{
  return isValid() ? ((uint8 const *)data + row * getScanWidth()) : NULL;
}

void *
Image::getScanLine(int row)
{
  return isValid() ? ((uint8 *)data + row * getScanWidth()) : NULL;
}

int
Image::getScanWidth() const
{
  return isValid() ? width * (getBitsPerPixel() / 8) : 0;
}

int
Image::getRowAlignment() const
{
  return 0;  // stbi does no alignment
}

namespace ImageInternal {

stbir_filter
filterToSTBFilter(Image::Filter filter)
{
  switch (filter)
  {
    case Image::Filter::BOX            :  return STBIR_FILTER_BOX; break;
    case Image::Filter::TRIANGLE       :  return STBIR_FILTER_TRIANGLE; break;
    case Image::Filter::CUBIC_BSPLINE  :  return STBIR_FILTER_CUBICBSPLINE; break;
    case Image::Filter::CATMULL_ROM    :  return STBIR_FILTER_CATMULLROM; break;
    case Image::Filter::MITCHELL       :  return STBIR_FILTER_MITCHELL; break;
    default                            :  return STBIR_FILTER_DEFAULT;
  }
}

} // namespace ImageInternal

bool
Image::rescale(int new_width, int new_height, Filter filter)
{
  if (!isValid())
  {
    DGP_ERROR << "Image: Attempting to rescale an invalid image";
    return false;
  }

  if (new_width <= 0 || new_height <= 0)
  {
    DGP_ERROR << "Image: Attempting to rescale to invalid dimensions: " << new_width << " x " << new_height;
    return false;
  }

  size_t num_bytes = (size_t)(new_width * new_height * (getBitsPerPixel() / 8));
  void * new_data = std::malloc(num_bytes);  // assume stbi uses malloc
  if (!new_data)
  {
    DGP_ERROR << "Image: Could not allocate memory to hold resized image";
    return false;
  }

  stbir_filter flt = ImageInternal::filterToSTBFilter(filter);

  int alpha = STBIR_ALPHA_CHANNEL_NONE;
  if (numChannels() == 2)
    alpha = 1;
  else if (numChannels() == 4)
    alpha = 3;

  int status;
  if (isFloatingPoint())
  {
    status = stbir_resize_float_generic((float const *)data, width,     height,     getScanWidth(),
                                        (float *)new_data,   new_width, new_height, new_width * (getBitsPerPixel() / 8),
                                        numChannels(), alpha, 0, STBIR_EDGE_CLAMP, flt, STBIR_COLORSPACE_LINEAR, NULL);
  }
  else
  {
    status = stbir_resize_uint8_generic((unsigned char const *)data, width,     height,     getScanWidth(),
                                        (unsigned char *)new_data,   new_width, new_height, new_width * (getBitsPerPixel() / 8),
                                        numChannels(), alpha, 0, STBIR_EDGE_CLAMP, flt, STBIR_COLORSPACE_LINEAR, NULL);
  }

  if (status == 0)
  {
    DGP_ERROR << "Image: Could not rescale image";
    return false;
  }

  stbi_image_free(data);
  data = new_data;
  width = new_width;
  height = new_height;

  return true;
}

void
Image::serialize(BinaryOutputStream & output, Codec const & codec) const
{
  if (!isValid())
    throw Error("Can't serialize an invalid image");

  if (codec == Codec_AUTO())
    throw Error("You must explicitly choose a codec for serializing images");

  ImageCodec const * img_codec = dynamic_cast<ImageCodec const *>(&codec);
  if (!img_codec)
    throw Error("Codec specified for image serialization is not an image codec.");

  img_codec->serializeImage(*this, output, true);
}

void
Image::deserialize(BinaryInputStream & input, Codec const & codec)
{
  if (codec == Codec_AUTO())
    deserialize_AUTO(input, true);
  else
  {
    ImageCodec const * img_codec = dynamic_cast<ImageCodec const *>(&codec);
    if (!img_codec)
      throw Error("Codec specified for image deserialization is not an image codec.");

    img_codec->deserializeImage(*this, input, true);
  }
}

void
Image::save(std::string const & filename, Codec const & codec) const
{
  if (!isValid())
    throw Error("Can't save an invalid image");

  ImageCodec const * c = NULL;
  if (codec == Codec_AUTO())
  {
    c = ImageInternal::codecFromPath(filename);
    if (!c)
      throw Error("Could not detect codec from filename");
  }

  if (!c)
  {
    c = dynamic_cast<ImageCodec const *>(&codec);
    if (!c)
      throw Error("Codec specified for saving image is not an image codec.");
  }

  BinaryOutputStream out(filename, Endianness::LITTLE);
  if (!out.ok())
    throw Error("Could not open image file for writing");

  c->serializeImage(*this, out, false);

  out.commit();
  if (!out.ok())
    throw Error("Could not save image file");
}

void
Image::load(std::string const & filename, Codec const & codec)
{
  BinaryInputStream in(filename, Endianness::LITTLE);
  int64 file_size = in.size();
  if (file_size <= 0)
    throw Error("Image file does not exist or is empty");

  if (codec == Codec_AUTO())
    deserialize_AUTO(in, false);
  else
  {
    try
    {
      ImageCodec const & img_codec = dynamic_cast<ImageCodec const &>(codec);
      img_codec.deserializeImage(*this, in, false);
    }
    catch (std::bad_cast &)
    {
      throw Error("Codec specified for loading image is not an image codec.");
    }
  }
}

void
Image::deserialize_AUTO(BinaryInputStream & input, bool read_prefixed_info)
{
  // All codecs currently decode with exactly the same code, so we can just use any one of them
  CodecBMP().deserializeImage(*this, input, read_prefixed_info);
}

void
Image::_setData(int w, int h, void * data_)
{
  width = w;
  height = h;
  data = data_;
}

void
Image::_setType(Type type_)
{
  type = type_;
}

} // namespace DGP
