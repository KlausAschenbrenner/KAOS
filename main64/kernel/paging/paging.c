//
//  paging.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2018.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "paging.h"

// Initializes the Paging Data Structures
void InitializePaging(long PhysicalMemoryAvailableInKB, unsigned long PhysicalFreeMemoryStartOffset, unsigned long PhysicalFreeMemoryEndOffset)
{
	int i = 0;

	// Initializes the physical Frame Allocator
	InitializeFrameAllocator(PhysicalMemoryAvailableInKB, PhysicalFreeMemoryStartOffset, PhysicalFreeMemoryEndOffset);

	// Allocate the necessary 4K pages for the Page Table Mapping Structures...
	Paging_PML4 *pml4 = (Paging_PML4 *)GetPhysicalFrameAddress(AllocateFrame());
	Paging_PDP *pdp =   (Paging_PDP * )GetPhysicalFrameAddress(AllocateFrame());
	Paging_PD *pd =     (Paging_PD *)  GetPhysicalFrameAddress(AllocateFrame());
	Paging_PT *pt =     (Paging_PT *)  GetPhysicalFrameAddress(AllocateFrame());
	Paging_PT *pt1 =    (Paging_PT *)  GetPhysicalFrameAddress(AllocateFrame());

	// Zero initialize the allocated 4K pages
	memset(pml4, 0, sizeof(Paging_PML4));
	memset(pdp, 0, sizeof(Paging_PDP));
	memset(pd, 0, sizeof(Paging_PD));
	memset(pt, 0, sizeof(Paging_PT));
	memset(pt1, 0, sizeof(Paging_PT));

	// Point in the 1st PML4 entry to the PDP
	pml4->Entries[0] = pdp;
	pml4->Entries[0] = pml4->Entries[0] | PDE_PRESENT;
	pml4->Entries[0] = pml4->Entries[0] | PDE_WRITABLE;

	// Point in the 1st PDP entry to the PD
	pdp->Entries[0] = pd;
	pdp->Entries[0] = pdp->Entries[0] | PDE_PRESENT;
	pdp->Entries[0] = pdp->Entries[0] | PDE_WRITABLE;

	// Point in the 1st PD entry to the PT
	pd->Entries[0] = pt;
	pd->Entries[0] = pd->Entries[0] | PDE_PRESENT;
	pd->Entries[0] = pd->Entries[0] | PDE_WRITABLE;

	// Identity Mapping of the first 512 small pages of 4K (0 - 2 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt->Entries[i].Frame = i;
		pt->Entries[i].Present = 1;
		pt->Entries[i].ReadWrite = 1;
	}

	// Identity Mapping of the next 512 small pages of 4K (2 - 4 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt1->Entries[i].Frame = i * (PT_ENTRIES * 1);
		pt1->Entries[i].Present = 1;
		pt1->Entries[i].ReadWrite = 1;
	}

	// Point in the 2nd PD entry to the 2nd PT
	pd->Entries[1] = pt1;
	pd->Entries[1] = pd->Entries[1] | PDE_PRESENT;
	pd->Entries[1] = pd->Entries[1] | PDE_WRITABLE;

    MapAnotherVirtualAddress(pml4);

	// Stores the Memory Address of PML4 in the CR3 register
	SwitchPageDirectory(pml4);
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
void MapAnotherVirtualAddress(Paging_PML4 *pml4)
{
    Paging_PDP *pdp =   (Paging_PDP * )GetPhysicalFrameAddress(AllocateFrame());
    Paging_PD *pd =     (Paging_PD *)  GetPhysicalFrameAddress(AllocateFrame());
	Paging_PT *pt =     (Paging_PT *)  GetPhysicalFrameAddress(AllocateFrame());
    int i = 0;

    // Zero initialize the allocated 4K pages
	memset(pdp, 0, sizeof(Paging_PDP));
	memset(pd, 0, sizeof(Paging_PD));
	memset(pt, 0, sizeof(Paging_PT));

    // Point in the 256th PML4 entry to the PDP
	pml4->Entries[256] = pdp;
	pml4->Entries[256] = pml4->Entries[256] | PDE_PRESENT;
	pml4->Entries[256] = pml4->Entries[256] | PDE_WRITABLE;

    // Point in the 3rd PDP entry to the PD
	pdp->Entries[3] = pd;
	pdp->Entries[3] = pdp->Entries[3] | PDE_PRESENT;
	pdp->Entries[3] = pdp->Entries[3] | PDE_WRITABLE;

    // Point in the 511th PD entry to the PT
	pd->Entries[511] = pt;
	pd->Entries[511] = pd->Entries[511] | PDE_PRESENT;
	pd->Entries[511] = pd->Entries[511] | PDE_WRITABLE;

    // Map the 496th PT entry to a physical memory address
	pt->Entries[496].Frame = AllocateFrame(); // This is just the physical Frame Number, NOT the physical Frame Memory Address!!!
	pt->Entries[496].Present = 1;
	pt->Entries[496].ReadWrite = 1;
}

void SwitchPageDirectory(Paging_PML4 *PML4)
{
    asm volatile("mov %0, %%cr3":: "r"(PML4));
}