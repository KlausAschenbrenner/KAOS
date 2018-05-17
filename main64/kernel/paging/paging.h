//
//  paging.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 14.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_paging_h
#define KAOS_paging_h

long PDE_PRESENT =	1; // 0000000000000000000000000000001
long PDE_WRITABLE =	2; // 0000000000000000000000000000010

int SMALL_PAGE_SIZE = 4096;
int PT_ENTRIES = 512;

// Represents a 64 Bit long Page Table Entry
struct Page
{
    unsigned Present : 1;       // P
    unsigned ReadWrite: 1;      // R/W
    unsigned User : 1;          // U/S
    unsigned WriteThrough : 1;  // PWT
    unsigned CacheDisable : 1;  // PCD
    unsigned Accessed : 1;      // A
    unsigned Dirty : 1;         // D
    unsigned PageSize : 1;      // PS
    unsigned Global : 1;        // G
    unsigned Available : 3;     // AVL
    unsigned long Frame : 36;
    unsigned short Reserved;    // 16 Bits
} __attribute__ ((packed));
typedef struct Page Page_PT;

// Defines the Page Map Level 4 Table<
typedef struct PageMapLevel4Table
{
    long Entries[512];
} Paging_PML4;

// Defines the Page Directory Pointer Table
typedef struct PageDirectoryPointerTable
{
    long Entries[512];
} Paging_PDP;

// Defines the Page Directory Table
typedef struct PageDirectoryTable
{
    long Entries[512];
} Paging_PD;

// Defines the Page Table
typedef struct PageTable
{
    Page_PT Entries[512];
} Paging_PT;

// Initializes the Paging Data Structures
void InitializePaging(long PhysicalMemoryAvailableInKB, unsigned long PhysicalFreeMemoryStartOffset, unsigned long PhysicalFreeMemoryEndOffset);

// Switches the PML4 Page Table Offset in the CR3 Register 
void SwitchPageDirectory(Paging_PML4 *PML4);

// Maps another Virtual Address to a Physical Address - just for testing purposes...
void MapAnotherVirtualAddress(Paging_PML4 *PML4);

#endif