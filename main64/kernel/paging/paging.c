//
//  paging.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "paging.h"

// Initializes the Paging Data Structures
void InitializePaging()
{
	int i = 0;

	// Allocate the necessary 4K pages for the Page Table Mapping Structures...
	PageMapLevel4Table *pml4 = (PageMapLevel4Table *)GetPhysicalFrameAddress(AllocateFrame());
	PageDirectoryPointerTable *pdp = (PageDirectoryPointerTable *)GetPhysicalFrameAddress(AllocateFrame());
	PageDirectoryTable *pd = (PageDirectoryTable *)GetPhysicalFrameAddress(AllocateFrame());
	PageTable *pt1 = (PageTable *)GetPhysicalFrameAddress(AllocateFrame());
	PageTable *pt2 = (PageTable *)GetPhysicalFrameAddress(AllocateFrame());
	PageTable *pt3 = (PageTable *)GetPhysicalFrameAddress(AllocateFrame());

	// Save the PML4 Offset in a Global Variable
	KERNEL_PML4_OFFSET = (long)pml4;

	// Zero initialize the allocated 4K pages
	memset(pml4, 0, sizeof(PageMapLevel4Table));
	memset(pdp, 0, sizeof(PageDirectoryPointerTable));
	memset(pd, 0, sizeof(PageDirectoryTable));
	memset(pt1, 0, sizeof(PageTable));
	memset(pt2, 0, sizeof(PageTable));
	memset(pt3, 0, sizeof(PageTable));

	// Point in the 1st PML4 entry to the PDP
	pml4->Entries[0] = pdp;
	pml4->Entries[0] = pml4->Entries[0] | PDE_PRESENT;
	pml4->Entries[0] = pml4->Entries[0] | PDE_WRITABLE;

	// Point in the 1st PDP entry to the PD
	pdp->Entries[0] = pd;
	pdp->Entries[0] = pdp->Entries[0] | PDE_PRESENT;
	pdp->Entries[0] = pdp->Entries[0] | PDE_WRITABLE;

	// Point in the 1st PD entry to the PT
	pd->Entries[0] = pt1;
	pd->Entries[0] = pd->Entries[0] | PDE_PRESENT;
	pd->Entries[0] = pd->Entries[0] | PDE_WRITABLE;

	// Identity Mapping of the first 512 small pages of 4K (0 - 2 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt1->Entries[i].Frame = i;
		pt1->Entries[i].Present = 1;
		pt1->Entries[i].ReadWrite = 1;
	}

	// Point in the 2nd PD entry to the 2nd PT
	pd->Entries[1] = pt2;
	pd->Entries[1] = pd->Entries[1] | PDE_PRESENT;
	pd->Entries[1] = pd->Entries[1] | PDE_WRITABLE;

	// Identity Mapping of the next 512 small pages of 4K (2 - 4 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt2->Entries[i].Frame = i + (PT_ENTRIES * 1);
		pt2->Entries[i].Present = 1;
		pt2->Entries[i].ReadWrite = 1;
	}

	// Point in the 3rd PD entry to the 3rd PT
	pd->Entries[2] = pt3;
	pd->Entries[2] = pd->Entries[2] | PDE_PRESENT;
	pd->Entries[2] = pd->Entries[2] | PDE_WRITABLE;

	// Identity Mapping of the next 512 small pages of 4K (2 - 4 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt3->Entries[i].Frame = i + (PT_ENTRIES * 2);
		pt3->Entries[i].Present = 1;
		pt3->Entries[i].ReadWrite = 1;
	}

	// Stores the Memory Address of PML4 in the CR3 register
	SwitchPageDirectory(pml4);
}

// Handles a Page Fault
void HandlePageFault(unsigned long VirtualAddress)
{
	MapAnotherVirtualAddress();
}

// Hex:    0xFFFF8000FFFF0000
// Binary: 11111111 11111111 10000000 00000000 11111111 11111111 00000000 00000000
// 
//  Sign Extension     PML4      PDP        PD        PT    Page Offset
// 1111111111111111 100000000 000000011 111111111 111110000 000000000000
// PML4: 100000000 => 256d
// PDP:  000000011 =>   3d
// PD:   111111111 => 511d
// PT:	 111110000 => 496d
void MapAnotherVirtualAddress()
{
	PageMapLevel4Table *pml4 = (PageMapLevel4Table *)KERNEL_PML4_OFFSET;
    PageDirectoryPointerTable *pdp = GetPhysicalFrameAddress(AllocateFrame());
    PageDirectoryTable *pd = GetPhysicalFrameAddress(AllocateFrame());
	PageTable *pt = GetPhysicalFrameAddress(AllocateFrame());
    int i = 0;

    // Zero initialize the allocated 4K pages
	memset(pdp, 0, sizeof(PageDirectoryPointerTable));
	memset(pd, 0, sizeof(PageDirectoryTable));
	memset(pt, 0, sizeof(PageTable));

    // Point in the 256th PML4 entry to the PDP
	pml4->Entries[256] = (long)pdp;
	pml4->Entries[256] = pml4->Entries[256] | PDE_PRESENT;
	pml4->Entries[256] = pml4->Entries[256] | PDE_WRITABLE;

    // Point in the 3rd PDP entry to the PD
	pdp->Entries[3] = (long)pd;
	pdp->Entries[3] = pdp->Entries[3] | PDE_PRESENT;
	pdp->Entries[3] = pdp->Entries[3] | PDE_WRITABLE;

    // Point in the 511th PD entry to the PT
	pd->Entries[511] = (long)pt;
	pd->Entries[511] = pd->Entries[511] | PDE_PRESENT;
	pd->Entries[511] = pd->Entries[511] | PDE_WRITABLE;

    // Map the 496th PT entry to a physical memory address
	pt->Entries[496].Frame = AllocateFrame(); // This is just the physical Frame Number, NOT the physical Frame Memory Address!!!
	pt->Entries[496].Present = 1;
	pt->Entries[496].ReadWrite = 1;
}

// Switches the PML4 Page Table Offset in the CR3 Register
void SwitchPageDirectory(PageMapLevel4Table *PML4)
{
    asm volatile("mov %0, %%cr3":: "r"(PML4));
}