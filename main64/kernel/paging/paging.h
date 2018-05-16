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

// Defines the Page Map Level 4 Table
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
    long Entries[512];
} Paging_PT;

void CreatePagingTables();
void SwitchPageDirectory(Paging_PML4 *PML4);

#endif