//
//  heap.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 15.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "Heap.h"
#include "../drivers/screen.h"
#include "../Tasks/Spinlock.h"
#include "../irq/irq.h"

unsigned long HEAP_START_OFFSET = 0xFFFF810000500000;
unsigned long HEAP_END_OFFSET =   0xFFFF810000500000;
unsigned long INITIAL_HEAP_SIZE = 0x10000;
unsigned long HEAP_GROWTH =       0x10000;

unsigned long spinlock;

// A Spinlock for making heap allocations single threaded
DECLARE_SPINLOCK(SPINLOCK_MALLOC);

// Initializes the Heap Manager
int InitHeap()
{
    // Initially the whole Heap is unallocated
    HeapBlock *heap = (HeapBlock *)HEAP_START_OFFSET;
    heap->InUse = 0;
    heap->Size = INITIAL_HEAP_SIZE;

    HEAP_END_OFFSET = HEAP_START_OFFSET + INITIAL_HEAP_SIZE;
    
    // Return the size of the whole Heap
    return heap->Size;
}

// Allocates the specific amount of memory on the Heap
void *malloc_internal(int Size)
{
    // Add the size of the Header to the requested size
    Size = Size + HEADER_SIZE;

    // Adjust the size to a 4-byte boundary, so that we can use
    // the lower 2 bits for storing status information
    Size = (Size + HEADER_SIZE - 1) & ~(HEADER_SIZE - 1);

    // Find a free block
    HeapBlock *block = Find(Size);

    if (block != 0)
    {
        // Allocate the free Heap Block
        Allocate(block, Size);

        // Return the address of the payload of the found Heap Block
        return (void *)block->Payload;
    }
    else
    {
        // We don't have found any free Heap Block.
        // Let's allocate another 4K page for the Heap
        HeapBlock *lastBlock = GetLastHeapBlock();
        lastBlock->InUse = 0;
        lastBlock->Size = HEAP_GROWTH;
        HEAP_END_OFFSET += HEAP_GROWTH;

        // Merge the last free block with the newly allocated block together
        Merge();

        // Try to allocate the requested block after the expansion of the Heap...
        return malloc_internal(Size - HEADER_SIZE);
    }
}

// Performs an allocation on the Heap.
// The memory allocation must happen single threaded, because otherwise we could corrupt the Heap Data Structure...
void *malloc(int Size)
{
    // Acquire a Spinlock prior making the memory allocation
    AcquireSpinlock(SPINLOCK_MALLOC);

    // Perform the memory allocation
    void *ptr = malloc_internal(Size);

    // Release the Spinlock
    ReleaseSpinlock(SPINLOCK_MALLOC);

    // Return a pointer to the newly allocated memory block on the Heap
    return ptr;
}

unsigned long GetHeapEndOffset()
{
    return HEAP_END_OFFSET;
}

// Frees up a Heap Block
void free(void *ptr)
{
    // Mark the Heap Block as Free
    HeapBlock *block = ptr - HEADER_SIZE;
    block->InUse = 0;

    /* // Merge free blocks together
    if (Merge() > 0)
    {
        // If we have merged some free blocks together, we try it once again
        Merge();
    } */
}

// Merges 2 free blocks into one larger free block
static int Merge()
{
    HeapBlock *block = (HeapBlock *)HEAP_START_OFFSET;
    int mergedBlocks = 0;

    // Iterate over the various Heap Blocks
    while (block->Size > 0)
    {
        HeapBlock *nextBlock = NextHeapBlock(block);

        // If the current and the next block are free, merge them together
        if (block->InUse == 0 && nextBlock->InUse == 0)
        {
            // Merge with the next free Heap Block
            block->Size = block->Size + nextBlock->Size;
            mergedBlocks++;
        }

        block = NextHeapBlock(block);
    }

    // Return the number of merged blocks
    return mergedBlocks;
}

// Allocates a Heap Block at the beginning of "*Block" with a size of "Size".
// Splits the remaining available Heap Space and marks it as a free Heap Block
static void Allocate(HeapBlock *Block, int Size)
{
    int oldSize = Block->Size;

    // Check if there is free space available for an additional Heap Block after we have allocated the requested size
    // The minimum remaining size must be the Header Size + 1 Byte payload
    if (Block->Size - Size >= HEADER_SIZE + 1)
    {
        // Resize the current Heap Block
        Block->InUse = 1;
        Block->Size = Size;

        // Split the current Heap Block, because there is a remaining free space after the previous resizing
        HeapBlock *nextBlock = NextHeapBlock(Block);
        nextBlock->InUse = 0;
        nextBlock->Size = oldSize - Size;
    }
    else
    {
        // We don't have to split the current Heap Block, because there is no remaining free space after the Allocation
        // The remaining space is also allocated to this Heap Block!
        // Therefore the Heap Block Size is larger than the requested size!
        Block->InUse = 1;
    }
}

// Finds a free block of the requested size on the Heap
static HeapBlock *Find(int Size)
{
    HeapBlock *block;

    // Iterate over the various Heap Blocks
    for (block = HEAP_START_OFFSET; block->Size > 0; block = NextHeapBlock(block))
    {
        // Check if we have found a free and large enough Heap Block
        if ((block->InUse == 0) && (Size <= block->Size))
            return block;
    }

    // No free Heap Block was found
    return 0;
}

// Returns the last Heap Block
HeapBlock *GetLastHeapBlock()
{
    HeapBlock *block = (HeapBlock *)HEAP_START_OFFSET;

    // Loop until we reach the end of the current Heap...
    while (block->Size > 0) block = NextHeapBlock(block);

    // Return the last Heap Block
    return block;
}

// Returns the next Heap Block
static HeapBlock *NextHeapBlock(HeapBlock *Block)
{
    // Return a pointer to the next Heap Block
    return (unsigned char *)Block + Block->Size;
}

// Dumps out the status of each Heap Block
void DumpHeap()
{
    HeapBlock *block;
    char str[32] = "";
    int size = 0;
    
    for (block = HEAP_START_OFFSET; block->Size > 0; block = NextHeapBlock(block))
    {
        size += block->Size;
        PrintHeapBlock(block);
    }

    printf("Heap Start Offset: 0x");
    printf_long(HEAP_START_OFFSET, 16);
    printf("\n");
    printf("Heap End Offset:   0x");
    printf_long(HEAP_END_OFFSET, 16);
    printf("\n");
    printf("Whole Heap Size: ");
    itoa(size, 10, str);
    printf(str);
    printf("\n");
}

// Dumps out the status of a Heap Block
static void PrintHeapBlock(HeapBlock *Block)
{
    char str[32] = "";
    printf("Heap Block Address: 0x");
    ltoa(Block, 16, str);
    printf(str);
    printf("\n");
    printf("Heap Block Size: ");
    itoa(Block->Size, 10, str);
    printf(str);
    printf("\n");
    printf("Heap Block Status: ");

    if (Block->InUse == 0)
    {
        int color = SetColor(COLOR_LIGHT_GREEN);
        printf("FREE\n\n");
        SetColor(color);
    }
    else
    {
        int color = SetColor(COLOR_LIGHT_RED);
        printf("ALLOCATED\n\n");
        SetColor(color);
    }
}