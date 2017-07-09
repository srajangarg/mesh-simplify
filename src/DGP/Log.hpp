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

#ifndef __DGP_Log_hpp__
#define __DGP_Log_hpp__

#include "Platform.hpp"
#include "BasicStringAlg.hpp"
#include "Noncopyable.hpp"
#include "Spinlock.hpp"
#include <iostream>
#include <string>

namespace DGP {

namespace LogInternal {

extern Spinlock lock;

// Extract the filename from a full path.
DGP_API std::string stripPathFromFilename(std::string const & full_path);

// Get the current date and time as a string (not threadsafe).
DGP_API std::string currentDateTimeToString();

} // namespace LogInternal

/**
 * A temporary object that locks an output stream on construction and unlocks it (after optionally writing a newline) on
 * destruction. All objects piped to the object in a single line are written atomically. Useful e.g. for writing log messages to
 * the same file/console from multiple threads.
 *
 * Example:
 * \code
 *   LockedOutputStream<>(std::cout).getStream() << "This " << " line " << " will " << " be " << " written " << " atomically";
 * \endcode
 *
 * @note Currently, all objects of this class share the same lock, regardless of the wrapped stream.
 */
template < typename StreamT = std::basic_ostream<char> >
class /* DGP_API */ LockedOutputStream : public Noncopyable
{
  public:
    typedef StreamT StreamType;  ///< The type of wrapped output stream.

    /** Constructor. */
    LockedOutputStream(StreamT & stream_, bool append_newline_ = false)
    : stream(&stream_), append_newline(append_newline_)
    {
      setOutputLock(true);
    }

    /** Constructor. Writes a prefix to the stream after acquiring the output lock. */
    LockedOutputStream(StreamT & stream_, std::string const & prefix, bool append_newline_ = false)
    : stream(&stream_), append_newline(append_newline_)
    {
      setOutputLock(true);
      getStream() << prefix;
    }

    /** Destructor. Writes a newline to the output stream if the object was constructed with <tt>append_newline = true</tt>. */
    ~LockedOutputStream()
    {
      if (append_newline)
        getStream() << std::endl;

      setOutputLock(false);
    }

    /** Get the locked stream. */
    StreamT & getStream() { return *stream; }

  private:
    StreamT * stream;  ///< The wrapped output stream.
    bool append_newline;  ///< If true, a newline is written to the output stream when this object is destroyed.

    /** Lock/unlock the common lock */
    void setOutputLock(bool value)
    {
      if (value)
        LogInternal::lock.lock();
      else
        LogInternal::lock.unlock();
    }

}; // class LockedOutputStream

} // namespace DGP

// Fully qualify references in #defines so they can be used in client programs in non-DGP namespaces without namespace errors.

#define DGP_LOG_STANDARD_PREFIX DGP::format("[%s] %s:%ld: ", \
                                              DGP::LogInternal::currentDateTimeToString().c_str(), \
                                              DGP::LogInternal::stripPathFromFilename(__FILE__).c_str(), \
                                              (long)__LINE__)

/**
 * Synchronized console output stream, with no line prefix. Outputs a newline at the end of every sequence of stream operations
 * (i.e. after every stack such as <code>DGP_CONSOLE << a << b << c;</code>).
 */
#define DGP_CONSOLE DGP::LockedOutputStream<>(std::cout, true).getStream()

/**
 * Synchronized logging stream, with a prefix indicating the time, source file and line number. Outputs a newline at the end of
 * every sequence of stream operations (i.e. after every stack such as <code>DGP_LOG << a << b << c;</code>).
 */
#define DGP_LOG DGP::LockedOutputStream<>(std::cout, DGP_LOG_STANDARD_PREFIX, true).getStream()

#ifdef DGP_DEBUG_BUILD
/**
 * Synchronized stream for debug messages, with a prefix indicating the time, source file and line number. Outputs a newline at
 * the end of every sequence of stream operations (i.e. after every stack such as <code>DGP_DEBUG << a << b << c;</code>).
 *
 * Deactivated in release mode.
 */
#  define DGP_DEBUG DGP::LockedOutputStream<>(std::cout, DGP_LOG_STANDARD_PREFIX, true).getStream()
#else
/**
 * Synchronized stream for debug messages, with a prefix indicating the time, source file and line number. Outputs a newline at
 * the end of every sequence of stream operations (i.e. after every stack such as <code>DGP_DEBUG << a << b << c;</code>).
 *
 * Deactivated in release mode.
 */
#  define DGP_DEBUG while (false) std::cout
#endif

/**
 * Synchronized stream for error messages, with a prefix indicating the time, source file and line number. Outputs a newline at
 * the end of every sequence of stream operations (i.e. after every stack such as <code>DGP_ERROR << a << b << c;</code>).
 */
#define DGP_ERROR DGP::LockedOutputStream<>(std::cerr, DGP_LOG_STANDARD_PREFIX + "ERROR: ", true).getStream()

/**
 * Synchronized stream for warning messages, with a prefix indicating the time, source file and line number. Outputs a newline
 * at the end of every sequence of stream operations (i.e. after every stack such as <code>DGP_WARNING << a << b << c;</code>).
 */
#define DGP_WARNING DGP::LockedOutputStream<>(std::cerr, DGP_LOG_STANDARD_PREFIX + "WARNING: ", true).getStream()

#endif
