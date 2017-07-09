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

#ifndef __DGP_ImageMatrix_hpp__
#define __DGP_ImageMatrix_hpp__

#include "AddressableMatrix.hpp"
#include "Image.hpp"
#include "ResizableMatrix.hpp"
#include <climits>

namespace DGP {

/**
 * A wrapper class that allows a single-channel (luminance) image to be treated as an addressable matrix. Please ensure the type
 * T matches the type of pixels in the image! The constructor will do a series of checks for this, but checks can be defeated
 * when custom types are involved.
 */
template <typename T>
class /* DGP_API */ ImageMatrix : public AddressableMatrix<T>, public ResizableMatrix<T>
{
  public:
    /** Constructor. The image pointer must remain valid until the matrix is destroyed. */
    ImageMatrix(Image * image_) : image(image_)
    {
      alwaysAssertM(image, "ImageMatrix: Cannot initialize from a null image");
      alwaysAssertM(image->numChannels() == 1, "ImageMatrix: The image must be single-channel");
      alwaysAssertM(image->getBitsPerPixel() / CHAR_BIT == sizeof(T),
                    "ImageMatrix: The number of bytes per pixel does not match the size of the matrix data type");
    }

    long numRows() const { return image->getHeight(); }
    long numColumns() const { return image->getWidth(); }

    void resize(long num_rows, long num_cols) { image->resize(image->getType(), (int)num_cols, (int)num_rows); }

    // This is needed to avoid a Visual Studio warning about inheriting via dominance
    void makeZero() { AddressableMatrix<T>::makeZero(); }

    /** Element access. Use this whenever possible to avoid the virtual function overhead of get(). */
    T const & operator()(long row, long col) const { return ((T const *)image->getScanLine(row))[col]; }

    /** Element access. Use this whenever possible to avoid the virtual function overhead of get() or set(). */
    T & operator()(long row, long col) { return ((T *)image->getScanLine(row))[col]; }

    T const & get(long row, long col) const { return (*this)(row, col); }
    T & getMutable(long row, long col) { return (*this)(row, col); }
    void set(long row, long col, T const & value) { (*this)(row, col) = value; }

    void fill(T const & value)
    {
      long nr = numRows(), nc = numColumns();

      for (long r = 0; r < nr; ++r)
      {
        T * scanline = static_cast<T *>(image->getScanLine(r));
        std::fill(scanline, scanline + nc, value);
      }
    }

  private:
    Image * image;  ///< The wrapped image

}; // class ImageMatrix

} // namespace DGP

#endif
