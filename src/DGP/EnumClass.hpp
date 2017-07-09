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

#ifndef __DGP_EnumClass_hpp__
#define __DGP_EnumClass_hpp__

#include "Platform.hpp"
#include <string>
#include <utility>

namespace DGP {

// Define the body of an enum class.
#define DGP_ENUM_CLASS_BODY(name)                                                                                            \
    public:                                                                                                                   \
      name() {}                                                                                                               \
      template <typename T> explicit name(T value_) : value(static_cast<Value>(value_)) {}                                    \
      name(Value value_) : value(value_) {}                                                                                   \
      operator Value() const { return value; }                                                                                \
      bool operator==(Value other) const { return value == other; }                                                           \
      bool operator!=(Value other) const { return value != other; }                                                           \
      bool operator==(name const & other) const { return value == other.value; }                                              \
      bool operator!=(name const & other) const { return value != other.value; }                                              \
                                                                                                                              \
    private:                                                                                                                  \
      Value value;                                                                                                            \
                                                                                                                              \
    public:

// Serialize and deserialize enums from binary I/O streams (requires explicitly including Serialization.hpp)
#define DGP_ENUM_CLASS_SERIALIZATION(name)                                                                                   \
    public:                                                                                                                   \
      void serialize(BinaryOutputStream & output, Codec const & codec = Codec_AUTO()) const                                   \
      {                                                                                                                       \
        output.setEndianness(Endianness::LITTLE);                                                                             \
        output.writeInt32(static_cast<int>(value));                                                                           \
      }                                                                                                                       \
                                                                                                                              \
      void deserialize(BinaryInputStream & input, Codec const & codec = Codec_AUTO())                                         \
      {                                                                                                                       \
        input.setEndianness(Endianness::LITTLE);                                                                              \
        int v = (int)input.readInt32();                                                                                       \
        value = static_cast<Value>(v);                                                                                        \
      }

// Put quotes around the result of a macro expansion.
#define DGP_ENUM_CLASS_STRINGIFY_(x) #x
#define DGP_ENUM_CLASS_STRINGIFY(x) DGP_ENUM_CLASS_STRINGIFY_(x)

// Begin sequence of mappings of enum values to strings.
#define DGP_ENUM_CLASS_STRINGS_BEGIN(name)                                                                                   \
    private:                                                                                                                  \
      static std::pair<Value, std::string> const * DGP_ENUM_CLASS_stringMapping(std::size_t i)                               \
      {                                                                                                                       \
        static std::pair<Value, std::string> const STRS[] = {

// Register an enum value with the string representation of its name.
#define DGP_ENUM_CLASS_STRING_SELF(value) std::pair<Value, std::string>(value, DGP_ENUM_CLASS_STRINGIFY(value)),

// Register an enum value to an arbitrary string.
#define DGP_ENUM_CLASS_STRING(value, str) std::pair<Value, std::string>(value, str),

// End sequence of mappings of enum values to strings, and define toString(), fromString() and construct-from-string functions.
#define DGP_ENUM_CLASS_STRINGS_END(name)                                                                                     \
        };                                                                                                                    \
                                                                                                                              \
        return (i >= (sizeof(STRS) / sizeof(std::pair<Value, std::string>))) ? NULL : &STRS[i];                               \
      }                                                                                                                       \
                                                                                                                              \
    public:                                                                                                                   \
      std::string const & toString() const                                                                                    \
      {                                                                                                                       \
        std::pair<Value, std::string> const * mapping = DGP_ENUM_CLASS_stringMapping(0);                                     \
        std::size_t i = 0;                                                                                                    \
        while (mapping)                                                                                                       \
        {                                                                                                                     \
          if (mapping->first == value) return mapping->second;                                                                \
          mapping = DGP_ENUM_CLASS_stringMapping(++i);                                                                       \
        }                                                                                                                     \
                                                                                                                              \
        throw DGP_ENUM_CLASS_STRINGIFY(name) ": Enum value has no string representation";                                    \
      }                                                                                                                       \
                                                                                                                              \
      explicit name(std::string const & str)                                                                                  \
      {                                                                                                                       \
        if (!fromString(str))                                                                                                 \
          throw DGP_ENUM_CLASS_STRINGIFY(name) ": Could not convert string to enum value";                                   \
      }                                                                                                                       \
                                                                                                                              \
      bool fromString(std::string const & str)                                                                                \
      {                                                                                                                       \
        std::pair<Value, std::string> const * mapping = DGP_ENUM_CLASS_stringMapping(0);                                     \
        std::size_t i = 0;                                                                                                    \
        while (mapping)                                                                                                       \
        {                                                                                                                     \
          if (mapping->second == str)                                                                                         \
          {                                                                                                                   \
            value = mapping->first;                                                                                           \
            return true;                                                                                                      \
          }                                                                                                                   \
                                                                                                                              \
          mapping = DGP_ENUM_CLASS_stringMapping(++i);                                                                       \
        }                                                                                                                     \
                                                                                                                              \
        return false;                                                                                                         \
      }

} // namespace DGP

#endif
