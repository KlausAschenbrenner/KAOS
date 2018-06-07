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

#define FRAMES_START_OFFSET 0x0000000000200000
#define FRAME_SIZE 4096

// A bitset of frames - used or free
long *BitsetFrames;
long NumberPhysicalFrames;

// Initializes the Physical Frame Allocator.
// Physical 4KB Frames are allocated in the physical Memory Region between "PhysicalFreeMemoryStartOffset" and "PhysicalFreeMemoryEndOffset"
void InitializeFrameAllocator(unsigned long PhysicalFreeMemoryStartOffset, unsigned long PhysicalFreeMemoryEndOffset);

// Allocates the specific physical Frame in the Bitset
void SetFrame(long Frame);

// Function to clear a bit in the frames bitset
void ClearFrame(long Frame);

// Allocates the first free physical Frame and returns the Frame number
long AllocateFrame();

// Returns the physical Memory Address for a given Frame Number
long GetPhysicalFrameAddress(long Frame);

// Tests the Frame Allocator
void TestFrameAllocator();

#endif