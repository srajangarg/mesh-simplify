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

#ifndef __DGP_System_hpp__
#define __DGP_System_hpp__

#include "Common.hpp"

#ifndef DGP_WINDOWS
#  include <sys/time.h>
#endif

namespace DGP {

/** Low-level system information and profiling functions. */
class DGP_API System
{
  public:
    /** Get the hardware concurrency (approximate number of thread contexts). */
    static long concurrency();

    /** Get the machine endianness. */
    static Endianness endianness()
    {
      return Endianness::machine();
    }

    /** Pause the current thread for a given number of milliseconds. */
    static void sleep(long ms);

    /**
     * The actual time (measured in seconds since Jan 1 1970 midnight). Adjusted for local timezone and daylight savings time.
     * This is as accurate and fast as getCycleCount().
     */
    static double time();

    /**
     * Begin a timing operation. To count the number of cycles a given operation takes:
     *
     * <pre>
     *   unsigned long count;
     *   System::beginCycleCount(count);
     *   ...
     *   System::endCycleCount(count);
     *   // count now contains the cycle count for the intervening operation.
     * </pre>
     *
     * @see endCycleCount()
     */
    static void beginCycleCount(uint64 & cycle_count);

    /**
     * End a timing operation.
     *
     * @see beginCycleCount()
     */
    static void endCycleCount(uint64 & cycle_count);

  private:
    /** Constructor. */
    System();

    /** Called to initialize timing operations when the object is constructed. */
    void initTime();

    /** Get the current cycle count. */
    static uint64 getCycleCount();

    /** Singleton instance. */
    static System & instance()
    {
      static System s; return s;
    }

#ifdef DGP_WINDOWS
    int64          m_start;
    int64          m_counterFrequency;
#else
    struct timeval m_start;
#endif

#ifdef DGP_OSX
    int32          m_OSXCPUSpeed;
    double         m_secondsPerNS;
#endif

    double         m_realWorldGetTickTime0;

}; // class System

} // namespace DGP

#endif
