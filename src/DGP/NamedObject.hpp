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

#ifndef __DGP_NamedObject_hpp__
#define __DGP_NamedObject_hpp__

#include "Common.hpp"

namespace DGP {

/** Interface for an object that has a name. */
class DGP_API AbstractNamedObject
{
  public:
    /** Destructor. */
    virtual ~AbstractNamedObject() {}

    /** Get the name of the object. */
    virtual char const * getName() const = 0;

}; // class AbstractNamedObject

/**
 * An object wrapping a name string.
 *
 * <b>IMPORTANT:</b> Always inherit virtually from this class, i.e. use:
 *
 * \code
 * class MyClass : public virtual NamedObject
 * {
 *   ...
 * };
 * \endcode
 *
 * This also means that a derived class in an inheritance hierarchy involving NamedObject must explicitly call the NamedObject
 * constructor if it wants to initialize the name.
 */
class DGP_API NamedObject : public AbstractNamedObject
{
  public:
    /** Destructor. */
    virtual ~NamedObject() = 0;

    /** Default constructor. */
    NamedObject() {}

    /** Initializing constructor. */
    NamedObject(std::string const & name_) : name(name_) {}

    /** Copy constructor. */
    NamedObject(NamedObject const & src): name(src.name) {}

    /** Assignment operator. */
    NamedObject & operator=(NamedObject const & src) { name = src.name; return *this; }

    /** Get the name of the object. */
    char const * getName() const { return name.c_str(); }

    /** Set the name of the object. */
    void setName(std::string const & name_) { name = name_; }

  protected:
    /** Access the name string directly, for efficiency. */
    std::string const & getNameStr() const { return name; }

  private:
    std::string name;

}; // class NamedObject

// Inline functions
inline
NamedObject::~NamedObject()
{
  // Pure virtual destructor should have a body
  //
  // http://www.linuxtopia.org/online_books/programming_books/thinking_in_c++/Chapter15_024.html
}

/** Write a short description of a named object to an output stream. */
inline std::ostream &
operator<<(std::ostream & os, NamedObject const & obj)
{
  std::string cls = getClass(obj);

  // Remove template parameters
  size_t last = cls.find('<');

  // Remove namespace qualifiers
  size_t first = cls.rfind(':', last);

  if (last  == std::string::npos) last  = cls.length();
  first = (first == std::string::npos ? 0 : first + 1);

  return os << cls.substr(first, last - first) << " '" << obj.getName() << '\'';
}

} // namespace DGP

#endif
