//
//  paging.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2018.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "paging.h"

void CreatePagingTables()
{
	Paging_PML4 *pml4 = (Paging_PML4 *)0x0000000000110000;
	Paging_PDP *pdp =   (Paging_PDP * )0x0000000000111000;
	Paging_PD *pd =     (Paging_PD *)  0x0000000000112000;
	Paging_PT *pt =     (Paging_PT *)  0x0000000000113000;
	Paging_PT *pt1 =    (Paging_PT *)  0x0000000000114000;
	int i = 0;

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
		pt->Entries[i] = i * SMALL_PAGE_SIZE;
		pt->Entries[i] = pt->Entries[i] | PDE_PRESENT;
		pt->Entries[i] = pt->Entries[i] | PDE_WRITABLE;
	}

	// Identity Mapping of the next 512 small pages of 4K (2 - 4 MB Virtual Address Space)
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt1->Entries[i] = i * SMALL_PAGE_SIZE * (PT_ENTRIES * 1);
		pt1->Entries[i] = pt1->Entries[i] | PDE_PRESENT;
		pt1->Entries[i] = pt1->Entries[i] | PDE_WRITABLE;
	}

	// Point in the 2nd PD entry to the 2nd PT
	pd->Entries[1] = pt1;
	pd->Entries[1] = pd->Entries[1] | PDE_PRESENT;
	pd->Entries[1] = pd->Entries[1] | PDE_WRITABLE;

	// Stores the Memory Address of PML4 in the CR3 register
	SwitchPageDirectory(pml4);
}

void SwitchPageDirectory(Paging_PML4 *PML4)
{
    asm volatile("mov %0, %%cr3":: "r"(PML4));
}