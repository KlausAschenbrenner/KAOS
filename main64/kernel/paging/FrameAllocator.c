//
//  FrameAllocator.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.05.2018.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "FrameAllocator.h"

void InitializeFrameAllocator(unsigned long PhysicalAvailableRAM)
{
    NumberPhysicalFrames = PhysicalAvailableRAM - FRAMES_START_OFFSET;
    NumberPhysicalFrames = NumberPhysicalFrames / FRAME_SIZE;

    // With the range from 0x50000 to 0x8FFFF we can manage a physical 8 GB large RAM:
    // 0x40000 = 262144d
    // 262144 Bytes * 8 Bits = 2097152 Bits
    // Each of these 2097152 Bits represents a 4K large page of 4096 bytes = 8 GB Physical RAM
    BitsetFrames = (long *)BITSET_FRAMES_START_OFFSET;
    memset(BitsetFrames, 0, BITSET_FRAMES_SIZE);
}

// Allocates the specific physical Frame in the Bitset
void SetFrame(long Frame)
{
    long idx = INDEX_FROM_BIT(Frame);
    long off = OFFSET_FROM_BIT(Frame);

    BitsetFrames[idx] |= (0x1 << off);
}

// Function to clear a bit in the frames bitset
void ClearPhysicalFrame(long Frame)
{
    Frame = Frame - (FRAMES_START_OFFSET / FRAME_SIZE);

    long idx = INDEX_FROM_BIT(Frame);
    long off = OFFSET_FROM_BIT(Frame);
    BitsetFrames[idx] &= ~(0x1 << off);
}

// Allocates the first free physical Frame and returns the Frame number
long AllocatePhysicalFrame()
{
    long i, j;

    for (i = 0; i < INDEX_FROM_BIT(NumberPhysicalFrames); i++)
    {
        // Check if the whole bits in the int Variable are allocated
        if (BitsetFrames[i] != 0xFFFFFFFFFFFFFFFF)
        {
            // At least one bit is free here.
            for (j = 0; j < 64; j++)
            {
                int test = 0x1 << j;

                if (!(BitsetFrames[i] & test))
                {
                    // Allocate the found physical Frame in the Bitset
                    long frame = i * 4 * 8 + j;
                    SetFrame(frame);

                    return (frame + (FRAMES_START_OFFSET / FRAME_SIZE));
                }
            }
        }
    }
}

void TestFrameAllocator()
{
    char str[32] = "";
    long i;

    // Frame 0
    int frame0 = AllocatePhysicalFrame();
    itoa(frame0, 16, str);
    printf("Frame: 0x");
    printf(str);
    printf("\n");

    // Frame 1
    int frame1 = AllocatePhysicalFrame();
    itoa(frame1, 16, str);
    printf("Frame: 0x");
    printf(str);
    printf("\n");

    // Release Frame 1 & 0
    ClearPhysicalFrame(frame1);
    ClearPhysicalFrame(frame0);

    // Frame 0
    frame0 = AllocatePhysicalFrame();
    itoa(frame0, 16, str);
    printf("Frame: 0x");
    printf(str);
    printf("\n");

    // Frame 1
    frame1 = AllocatePhysicalFrame();
    itoa(frame1, 16, str);
    printf("Frame: 0x");
    printf(str);
    printf("\n");
}