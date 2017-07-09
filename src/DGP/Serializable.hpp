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

#ifndef __DGP_Serializable_hpp__
#define __DGP_Serializable_hpp__

#include "Common.hpp"
#include "IOStream.hpp"
#include "NamedObject.hpp"

namespace DGP {

/**
 * A serialization codec. Identified by an ID that is unique for a given run of the program (it is <b>not</b> guaranteed to
 * retain its value over different runs).
 */
class DGP_API Codec : public AbstractNamedObject
{
  public:
    /** Destructor. */
    virtual ~Codec() {}

    /** Check if two codecs are equal. All instances of a codec class <b>must</b> be considered equal. */
    bool operator==(Codec const & other) const { return typeid(*this) == typeid(other); }

    /**
     * Implicitly convert to an integer value for use in switch statements etc. This value will be common to all instances of
     * the codec class
     */
    operator long() const { return reinterpret_cast<long>(&typeid(*this)); }
};

/** Write the name of the object to an output stream. */
inline std::ostream &
operator<<(std::ostream & os, Codec const & codec)
{
  return os << codec.getName() << " codec";
}

/** Indicates that the appropriate codec should be auto-detected. */
class DGP_API Codec_AUTO : public Codec
{
  public:
    char const * getName() const { static char const * my_name = "Auto"; return my_name; }
};

/** Indicates that the codec is unknown. */
class DGP_API Codec_UNKNOWN : public Codec
{
  public:
    char const * getName() const { static char const * my_name = "Unknown"; return my_name; }
};

/** The interface for a serializable object. */
class DGP_API Serializable
{
  public:
    /** Destructor. */
    virtual ~Serializable() {};

    /** Serialize the object to a binary output stream. */
    virtual void serialize(BinaryOutputStream & output, Codec const & codec = Codec_AUTO()) const = 0;

    /** Deserialize the object from a binary input stream. */
    virtual void deserialize(BinaryInputStream & input, Codec const & codec = Codec_AUTO()) = 0;

    /** Serialize the object to a text output stream. */
    virtual void serialize(TextOutputStream & output, Codec const & codec = Codec_AUTO()) const
    { throw Error("Serialization to text stream not implemented"); }

    /** Deserialize the object from a text input stream. */
    virtual void deserialize(TextInputStream & input, Codec const & codec = Codec_AUTO())
    { throw Error("Deserialization from text stream not implemented"); }

    /** Get the default settings for parsing configuration text files. */
    static TextInputStream::Settings const & configReadSettings()
    {
      static const TextInputStream::Settings def = initConfigReadSettings();
      return def;
    }

    /** Get the default settings for writing configuration text files. */
    static TextOutputStream::Settings const & configWriteSettings()
    {
      static const TextOutputStream::Settings def = initConfigWriteSettings();
      return def;
    }

  private:
    /** Create default settings for parsing configuration text files. */
    static TextInputStream::Settings initConfigReadSettings();

    /** Create default settings for writing configuration text files. */
    static TextOutputStream::Settings initConfigWriteSettings();

}; // class Serializable

} // namespace DGP

#endif
