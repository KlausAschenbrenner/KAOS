//
//  FrameAllocator.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.05.2018.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_FrameAllocator_h
#define KAOS_FrameAllocator_h

#define INDEX_FROM_BIT(a) (a / ( 8 * 4))
#define OFFSET_FROM_BIT(a) (a % ( 8 * 4))

#define FRAMES_START_OFFSET 0x0000000000110000
#define FRAME_SIZE 4096

// A bitset of frames - used or free.
int *BitsetFrames;
int NumberPhysicalFrames;

// Initializes the Physical Frame Allocator.
// Physical 4KB Frames are allocated in the physical Memory Region between "PhysicalFreeMemoryStartOffset" and "PhysicalFreeMemoryEndOffset"
void InitializeFrameAllocator(unsigned long PhysicalFreeMemoryStartOffset, unsigned long PhysicalFreeMemoryEndOffset);

// Returns the physical Memory Address for a given Frame Number
long GetPhysicalFrameAddress(int Frame);

// Tests the Frame Allocator
void Test();

#endif