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

#ifndef __DGP_Error_hpp__
#define __DGP_Error_hpp__

#include "Platform.hpp"
#include "BasicStringAlg.hpp"
#include "Log.hpp"
#include <stdexcept>
#include <string>

namespace DGP {

/**
 * An error class.
 */
typedef std::runtime_error Error;

/**
 * A fatal error class. Doesn't derive from std::exception so that it is not caught by one of the usual handlers.
 */
class DGP_API FatalError
{
  public:
    /** Constructor. */
    FatalError(std::string const & message_) : message(message_) {}

    /** Destructor. */
    ~FatalError() {}

    /** Assignment operator. */
    FatalError & operator=(FatalError const & src) { message = src.message; return *this; }

    /** The error message. */
    char const * what() const { return message.c_str(); }

  private:
    std::string message;

}; // class FatalError

/**
 * Generate a standard series of catch blocks that print a message on the specified stream and then perform an action. A fatal
 * error always generates a standard message on the error stream and the exception is rethrown, regardless of the specified
 * stream, message and action.
 *
 * Example:
 * <pre>
 *   DGP_STANDARD_CATCH_BLOCKS(continue;, WARNING, "A non-fatal error occurred in iteration %d", i)
 * </pre>
 */
#define DGP_STANDARD_CATCH_BLOCKS(action__, stream__, message__, ...) \
    catch (FatalError & e__) \
    { \
      DGP_ERROR << format( "A fatal error occurred (%s)", e__.what() ); \
      throw; \
    } \
    catch (Error & e__) \
    { \
      DGP_ ## stream__ << format( (message__ + std::string(" (%s)")).c_str(), __VA_ARGS__, e__.what() ); \
      action__ \
    } \
    catch (std::exception & e__) \
    { \
      DGP_ ## stream__ << format( (message__ + std::string(" (%s)")).c_str(), __VA_ARGS__, e__.what() ); \
      action__ \
    } \
    catch (std::string & e__) \
    { \
      DGP_ ## stream__ << format( (message__ + std::string(" (%s)")).c_str(), __VA_ARGS__, e__.c_str() ); \
      action__ \
    } \
    catch (const char * e__) \
    { \
      DGP_ ## stream__ << format( (message__ + std::string(" (%s)")).c_str(), __VA_ARGS__, e__ ); \
      action__ \
    } \
    catch (...) \
    { \
      DGP_ ## stream__ << format( (message__ + std::string(" (Unknown error)")).c_str(), __VA_ARGS__ ); \
      action__ \
    }

} // namespace DGP

#endif
