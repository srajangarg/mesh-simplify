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

#ifndef __DGP_FastCopy_hpp__
#define __DGP_FastCopy_hpp__

#include "Common.hpp"
#include <cstring>
#include <iterator>
#include <type_traits>

namespace DGP {

// Adapted from the Boost type_traits examples.

namespace FastCopyInternal {

template <typename I1, typename I2, bool b>
I2
fastCopyImpl(I1 first, I1 last, I2 out, std::integral_constant<bool, b> const &)
{
  while (first != last) *(out++) = *(first++);
  return out;
}

template <typename T>
T *
fastCopyImpl(T const * first, T const * last, T * out, std::true_type const &)
{
   memcpy(out, first, (last - first) * sizeof(T));
   return out + (last - first);
}

template <typename I1, typename I2, bool b>
I2
fastCopyBackwardImpl(I1 first, I1 last, I2 out, std::integral_constant<bool, b> const &)
{
  while (last != first) *(--out) = *(--last);
  return out;
}

template <typename T>
T *
fastCopyBackwardImpl(T const * first, T const * last, T * out, std::true_type const &)
{
   memmove(out, first, (last - first) * sizeof(T));
   return out;
}

} // namespace FastCopyInternal

/**
 * A version of <tt>std::copy</tt> that calls <tt>memcpy</tt> where appropriate (if the class has a trivial assignment operator
 * and the iterators are raw pointers) for speed.
 *
 * To take advantage of fast copying, specialize std::is_trivial to return true for the value type.
 *
 * @todo Reduce requirement to std::is_trivially_copyable once support for this is widespread.
 */
template <typename I1, typename I2>
inline I2
fastCopy(I1 first, I1 last, I2 out)
{
  //
  // We can copy with memcpy if T has a trivial assignment operator,
  // and if the iterator arguments are actually pointers (this last
  // requirement we detect with overload resolution):
  //
  typedef typename std::iterator_traits<I1>::value_type value_type;
  return FastCopyInternal::fastCopyImpl(first, last, out, std::is_trivial<value_type>());
}

/**
 * A version of <tt>std::copy_backward</tt> that calls <tt>memmove</tt> where appropriate (if the class has a trivial assignment
 * operator) for speed.
 *
 * To take advantage of fast copying, specialize std::is_trivial to return true for the value type.
 *
 * @todo Reduce requirement to std::is_trivially_copyable once support for this is widespread.
 */
template <typename I1, typename I2>
inline I2
fastCopyBackward(I1 first, I1 last, I2 out)
{
  typedef typename std::iterator_traits<I1>::value_type value_type;
  return FastCopyInternal::fastCopyBackwardImpl(first, last, out, std::is_trivial<value_type>());
}

} // namespace DGP

#endif
