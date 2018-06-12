//
//  paging.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 14.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_paging_h
#define KAOS_paging_h

#define SMALL_PAGE_SIZE 4096
#define PT_ENTRIES 512

// Macros to index into the various Page Tables
#define PML4_INDEX(virt) ((((unsigned long)(virt)) >> 39) & 511)
#define PML3_INDEX(virt) ((((unsigned long)(virt)) >> 30) & 511)
#define PML2_INDEX(virt) ((((unsigned long)(virt)) >> 21) & 511)
#define PML1_INDEX(virt) ((((unsigned long)(virt)) >> 12) & 511)

// Page Table Offsets from the Recursive Page Table Mapping
#define PML4_TABLE       ((unsigned long *)(0xfffffffffffff000))
#define PML3_TABLE(virt) ((unsigned long *)(0xffffffffffe00000 + ((((unsigned long)(virt)) >> 27) & 0x00001ff000)))
#define PML2_TABLE(virt) ((unsigned long *)(0xffffffffc0000000 + ((((unsigned long)(virt)) >> 18) & 0x003ffff000)))
#define PML1_TABLE(virt) ((unsigned long *)(0xffffff8000000000 + ((((unsigned long)(virt)) >> 9)  & 0x7ffffff000)))

// Macros to return a Page Table Entry
#define PML4_ENTRY(virt) PML4_TABLE[PML4_INDEX(virt)]
#define PML3_ENTRY(virt) PML3_TABLE(virt)[PML3_INDEX(virt)]
#define PML2_ENTRY(virt) PML2_TABLE(virt)[PML2_INDEX(virt)]
#define PML1_ENTRY(virt) PML1_TABLE(virt)[PML1_INDEX(virt)]

// Represents a 64-bit long PML4 Entry
struct _PML4Entry
{
    unsigned Present : 1;           // P
    unsigned ReadWrite : 1;         // R/W
    unsigned User : 1;              // U/S
    unsigned WriteThrough : 1;      // PWT
    unsigned CacheDisable : 1;      // PCD
    unsigned Accessed : 1;          // A
    unsigned Ignored1 : 1;          // IGN
    unsigned PageSize : 1;          
    unsigned Ignored2 : 4;          
    unsigned long Frame : 36;
    unsigned short Reserved;
} __attribute__ ((packed));
typedef struct _PML4Entry PML4Entry;

// Represents a 64-bit long Page Directory Pointer Entry
struct _PDPEntry
{
    unsigned Present : 1;           // P
    unsigned ReadWrite : 1;         // R/W
    unsigned User : 1;              // U/S
    unsigned WriteThrough : 1;      // PWT
    unsigned CacheDisable : 1;      // PCD
    unsigned Accessed : 1;          // A
    unsigned Ignored1 : 1;          // IGN
    unsigned PageSize : 1;          
    unsigned Ignored2 : 4;          
    unsigned long Frame : 36;
    unsigned short Reserved;
} __attribute__ ((packed));
typedef struct _PDPEntry PDPEntry;

// Represents a 64-bit long Page Directory Entry
struct _PDEntry
{
    unsigned Present : 1;           // P
    unsigned ReadWrite : 1;         // R/W
    unsigned User : 1;              // U/S
    unsigned WriteThrough : 1;      // PWT
    unsigned CacheDisable : 1;      // PCD
    unsigned Accessed : 1;          // A
    unsigned Ignored1 : 1;          // IGN
    unsigned PageSize : 1;          
    unsigned Ignored2 : 4;          
    unsigned long Frame : 36;
    unsigned short Reserved;
} __attribute__ ((packed));
typedef struct _PDEntry PDEntry;

// Represents a 64-bit long Page Table Entry
struct _PTEntry
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
typedef struct _PTEntry PTEntry;

// Defines the Page Map Level 4 Table
typedef struct _PageMapLevel4Table
{
    PML4Entry Entries[512];
} PageMapLevel4Table;

// Defines the Page Directory Pointer Table
typedef struct _PageDirectoryPointerTable
{
    PDPEntry Entries[512];
} PageDirectoryPointerTable;

// Defines the Page Directory Table
typedef struct _PageDirectoryTable
{
    PDEntry Entries[512];
} PageDirectoryTable;

// Defines the Page Table
typedef struct _PageTable
{
    PTEntry Entries[512];
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