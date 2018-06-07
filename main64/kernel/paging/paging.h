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
long KERNEL_PML4_OFFSET;

// Represents a 64 Bit long Page Table Entry
struct _Page
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
typedef struct _Page Page;

// Defines the Page Map Level 4 Table
typedef struct _PageMapLevel4Table
{
    long Entries[512];
} PageMapLevel4Table;

// Defines the Page Directory Pointer Table
typedef struct _PageDirectoryPointerTable
{
    long Entries[512];
} PageDirectoryPointerTable;

// Defines the Page Directory Table
typedef struct _PageDirectoryTable
{
    long Entries[512];
} PageDirectoryTable;

// Defines the Page Table
typedef struct _PageTable
{
    Page Entries[512];
} PageTable;

// Initializes the Paging Data Structures
void InitializePaging();

// Switches the PML4 Page Table Offset in the CR3 Register
void SwitchPageDirectory(PageMapLevel4Table *PML4);

// Handles a Page Fault
void HandlePageFault(unsigned long VirtualAddress);

// Maps another Virtual Address to a Physical Address - just for testing purposes...
void MapAnotherVirtualAddress();

#endif