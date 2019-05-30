//
//  Spinlock.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 20.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef SPINLOCK_H
#define SPINLOCK_H

// Declares a Spinlock
#define DECLARE_SPINLOCK(name) volatile int name ## Locked

// Acquires a Spinlock
#define AcquireSpinlock(name) \
	while (!__sync_bool_compare_and_swap(& name ## Locked, 0, 1)); \
	__sync_synchronize();

// Releases a Spinlock
#define ReleaseSpinlock(name) \
	__sync_synchronize(); \
	name ## Locked = 0;

// A Spinlock for accessing the Floppy Drive single threaded
DECLARE_SPINLOCK(SPINLOCK_FLOPPYDRIVE);

// A Spinlock for making heap allocations single threaded
DECLARE_SPINLOCK(SPINLOCK_MALLOC);

#endif