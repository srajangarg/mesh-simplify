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

#include "System.hpp"
#include <thread>

#ifdef DGP_WINDOWS
#  include <windows.h>
#  include <sys/timeb.h>
#else
#  include <unistd.h>
#endif

#ifdef DGP_OSX
#  include <CoreServices/CoreServices.h>
#endif

namespace DGP {

long
System::concurrency()
{
  long cc = (long)std::thread::hardware_concurrency();
  if (cc <= 0)
    return 1;  // operate in single-threaded mode as fallback
  else
    return cc;
}

void
System::sleep(long ms)
{
#ifdef DGP_WINDOWS
  Sleep(static_cast<DWORD>(ms));
#else
  usleep(static_cast<useconds_t>(ms * 1000));
#endif
}

System::System()
{
  initTime();
}

void
System::initTime()
{
#ifdef DGP_WINDOWS

  m_counterFrequency = 0;
  m_start = 0;

  LARGE_INTEGER cf, st;
  if (QueryPerformanceFrequency(&cf))
  {
    if (QueryPerformanceCounter(&st))
    {
      m_counterFrequency = (int64)cf.QuadPart;
      m_start = (int64)st.QuadPart;
    }
  }

  struct _timeb t;
  _ftime(&t);

  m_realWorldGetTickTime0 = (double)t.time - t.timezone * 60 + (t.dstflag ? 60 * 60 : 0);

#else

  gettimeofday(&m_start, NULL);

  // "sse" = "seconds since epoch". The time function returns the seconds since the epoch GMT (perhaps more correctly called
  // UTC).
  time_t gmt = ::time(NULL);

  // No call to free or delete is needed, but subsequent calls to asctime, ctime, mktime, etc. might overwrite local_time_vals.
  tm * localTimeVals = localtime(&gmt);
  time_t local = gmt;

  if (localTimeVals)
  {
    // tm_gmtoff is already corrected for daylight savings.
    local = local + localTimeVals->tm_gmtoff;
  }

  m_realWorldGetTickTime0 = local;

#ifdef DGP_OSX
  SInt32 cpu_speed;
  Gestalt('pclk', &cpu_speed);

  m_OSXCPUSpeed = (int32)cpu_speed;
  m_secondsPerNS = 1.0 / 1.0e9;
#endif

#endif
}

double
System::time()
{
#ifdef DGP_WINDOWS
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);

  return ((double)(now.QuadPart - instance().m_start) / instance().m_counterFrequency) + instance().m_realWorldGetTickTime0;
#else
  // Linux resolution defaults to 100Hz. There is no need to do a separate RDTSC call as gettimeofday actually uses RDTSC
  // when on systems that support it, otherwise it uses the system clock.
  struct timeval now;
  gettimeofday(&now, NULL);

  return (now.tv_sec  - instance().m_start.tv_sec) +
      (now.tv_usec - instance().m_start.tv_usec) / 1e6
      + instance().m_realWorldGetTickTime0;
#endif
}

#if defined(DGP_WINDOWS)

#  ifdef DGP_64BIT  // 64-bit Windows

uint64
System::getCycleCount()
{
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return now.QuadPart;
}

#  else // 32-bit Windows

uint64
System::getCycleCount()
{
  uint32 timehi, timelo;
  // Use the assembly instruction rdtsc, which gets the current cycle count (since the process started) and puts it in edx:eax.
  __asm
  {
    rdtsc;
    mov timehi, edx;
    mov timelo, eax;
  }
  return ((uint64)timehi << 32) + (uint64)timelo;
}

#  endif

#elif defined(DGP_LINUX)

uint64
System::getCycleCount()
{
  uint32 timehi, timelo;
  __asm__ __volatile__ (
    "rdtsc            "
    : "=a" (timelo),
    "=d" (timehi)
    : );
  return ((uint64)timehi << 32) + (uint64)timelo;
}

#elif defined(DGP_OSX)

uint64
System::getCycleCount()
{
  // Note: To put off extra processing until the end, this does not return the actual clock cycle count. It is a bus cycle
  // count. When endCycleCount() is called, it converts the two into a difference of clock cycles.
  return (uint64)UnsignedWideToUInt64(UpTime());
  // return (uint64) mach_absolute_time();
}

#endif

void
System::beginCycleCount(uint64 & cycle_count)
{
  cycle_count = getCycleCount();
}

void
System::endCycleCount(uint64 & cycle_count)
{
#ifdef DGP_OSX
  AbsoluteTime end = UpTime();
  Nanoseconds diffNS = AbsoluteDeltaToNanoseconds(end, UInt64ToUnsignedWide(cycle_count));
  cycle_count = (uint64)((double)instance().m_OSXCPUSpeed
                       * (double)UnsignedWideToUInt64(diffNS)
                       * instance().m_secondsPerNS);
#else
  cycle_count = getCycleCount() - cycle_count;
#endif
}

} // namespace DGP
