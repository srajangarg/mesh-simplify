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

#ifndef __DGP_Spinlock_hpp__
#define __DGP_Spinlock_hpp__

#include "AtomicInt32.hpp"

namespace DGP {

/**
 * A simple lock that can be shared by multiple threads for synchronization. Busy-waits for a lock, and unlocks immediately.
 * Implemented with a single atomic integer.
 */
class DGP_API Spinlock
{
  public:
    /** Constructor. The object is initially unlocked. */
    Spinlock() : atomic(0) {}

    /**
     * Acquire the lock by atomically setting the value of an integer to non-zero, busy-waiting until the lock is obtained.
     *
     * @see unlock()
     */
    void lock()
    {
      while (atomic.compareAndSet(0, 1) != 0) {}
    }

    /**
     * Release the lock by atomically setting the value of an integer to zero. This operation is immediate and does not wait.
     *
     * @see unlock()
     */
    void unlock()
    {
      atomic = 0;
    }

  private:
    AtomicInt32 atomic;

}; // class Spinlock

} // namespace DGP

#endif
