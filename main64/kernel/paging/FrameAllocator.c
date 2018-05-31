//
//  FrameAllocator.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.05.2018.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "FrameAllocator.h"

void InitializeFrameAllocator(unsigned long PhysicalFreeMemoryStartOffset, unsigned long PhysicalFreeMemoryEndOffset)
{
    // Somehow the input parameters are passed in incorrectly... but why...????
    // int frames = PhysicalFreeMemoryEndOffset - PhysicalFreeMemoryStartOffset;

    NumberPhysicalFrames = 0x000000003FEEFFFF - 0x0000000000110000;
    NumberPhysicalFrames = NumberPhysicalFrames / 4096;

    // With the range from 0x80000 to 0x9FFFF we can manage a physical 4 GB large RAM:
    // 0x20000 = 131072d
    // 131072 Bytes * 8 Bits = 1048576 Bits
    // Each of these 1048576 Bits represents a 4K large page = 4194304 Bytes = 4 GB Physical RAM
    BitsetFrames = 0x80000;

    // !!!!CHANGED FROM 0x20000!!!!
    memset(BitsetFrames, 0, 0x1000);
}

// Allocates the specific physical Frame in the Bitset
void SetFrame(int Frame)
{
    int idx = INDEX_FROM_BIT(Frame);
    int off = OFFSET_FROM_BIT(Frame);

    BitsetFrames[idx] |= (0x1 << off);
}

// Function to clear a bit in the frames bitset
void ClearFrame(int Frame)
{
    int idx = INDEX_FROM_BIT(Frame);
    int off = OFFSET_FROM_BIT(Frame);

    BitsetFrames[idx] &= ~(0x1 << off);
}

// Allocates the first free physical Frame and returns the Frame number
int AllocateFrame()
{
    int i, j;

    for (i = 0; i < INDEX_FROM_BIT(NumberPhysicalFrames); i++)
    {
        // Check if the whole bits in the int Variable are allocated
        if (BitsetFrames[i] != 0xFFFFFFFF)
        {
            // At least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                int test = 0x1 << j;

                if (!(BitsetFrames[i] & test))
                {
                    // Allocate the found physical Frame in the Bitset
                    int frame = i * 4 * 8 + j;
                    SetFrame(frame);

                    return frame;
                }
            }
        }
    }
}

// Returns the physical Memory Address for a given Frame Number
long GetPhysicalFrameAddress(int Frame)
{
    return (Frame * FRAME_SIZE) + FRAMES_START_OFFSET;
}

void Test()
{
    char str[32] = "";
    int i;

    // Frame 0
    int frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 1
    frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Release Frame 1 & 0
    ClearFrame(frame);
    ClearFrame(0);

    // Frame 1
    frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 2
    frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 3
    frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 4
    frame = AllocateFrame();
    itoa(frame, 16, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Allocate 1000 Frames
    for (i = 0; i < 1000; i++)
    {
        frame = AllocateFrame();
    }

    // Release all 1003 allocated Frames
    for (i = 0; i < 1003; i++)
    {
        ClearFrame(i);
    }

    // Allocate 1000 Frames
    for (i = 0; i < 1000; i++)
    {
        frame = AllocateFrame();
    }

    // Release Frames 500 - 505
    for (i = 500; i < 505; i++)
    {
        ClearFrame(i);
    }

    // Release Frame 737
    ClearFrame(737);

    // Frame 500
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 501
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 502
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 503
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 504
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 737
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");

    // Frame 1000
    frame = AllocateFrame();
    itoa(frame, 10, str);
    printf("Frame: ");
    printf(str);
    printf("\n");
}