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

#define FRAMES_START_OFFSET 0x400000
#define FRAME_SIZE 4096
#define BITSET_FRAMES_START_OFFSET 0xFFFF800000050000
#define BITSET_FRAMES_SIZE 0x40000

// A bitset of frames - used or free
long *BitsetFrames;
long NumberPhysicalFrames;

// Initializes the Physical Frame Allocator.
void InitializeFrameAllocator(unsigned long PhysicalAvailableRAM);

// Allocates the specific physical Frame in the Bitset
void SetFrame(long Frame);

// Function to clear a bit in the frames bitset
void ClearPhysicalFrame(long Frame);

// Allocates the first free physical Frame and returns the Frame number
long AllocatePhysicalFrame();

// Tests the Frame Allocator
void TestFrameAllocator();

#endif