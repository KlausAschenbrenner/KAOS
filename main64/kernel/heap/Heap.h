//
//  heap.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 15.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef HEAP_H
#define HEAP_H

#define HEADER_SIZE 4

typedef struct _HeapBlock
{
    // Header: 4 bytes
    int InUse : 1;
    int Size : 31;

    // Payload
    unsigned char Payload[0];
} HeapBlock;

// Initializes the Heap Manager
int InitHeap();

// Allocates the specific amount of memory on the Heap
void *malloc(int Size);

// Frees up a Heap Block
void free(void *ptr);

// Dumps out the status of each Heap Block
void DumpHeap();

// Returns the last Heap Block
HeapBlock *GetLastHeapBlock();

// Finds a free block of the requested size on the Heap
static HeapBlock *Find(int Size);

// Returns the next Heap Block
static HeapBlock *NextHeapBlock(HeapBlock *Block);

// Allocates a Heap Block at the beginning of "*Block" with a size of "Size".
// Splits the remaining available Heap Space and marks it as a free Heap Block
static void Allocate(HeapBlock *Block, int Size);

// Merges 2 free blocks into one larger free block
static int Merge();

// Dumps out the status of a Heap Block
static void PrintHeapBlock(HeapBlock *Block);

unsigned long GetHeapEndOffset();

#endif