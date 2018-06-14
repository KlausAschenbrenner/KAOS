//
//  paging.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#include "paging.h"
#include "../drivers/screen.h"

static void PageFaultDebugPrint(unsigned long PageTableIndex, char *PageTableName, unsigned long PhysicalFrame)
{
	char str[32] = "";

	// Log the Page Fault to the Console Window
	ltoa(PageTableIndex, 16, str);
	printf("Allocated the " );
	printf(PageTableName);
	printf(" entry 0x");
	printf(str);
	ltoa(PhysicalFrame, 16, str);
	printf(" at physical frame 0x");
	printf(str);
	printf("\n");
}

// Initializes the Paging Data Structures
void InitializePaging()
{
	int i = 0;

	// Allocate the necessary 4K pages at specific hardcoded locations for the Page Table Mapping Structures...
	// These Virtual Addresses are currently mapped to the physical frames 0x90000 - 0x97FFF through the
	// Identity Mapping of 0 - 4 MB that was setup in EnterLongMode.asm before entering the x64 Long Mode
	PageMapLevel4Table *pml4 = (PageMapLevel4Table *)0x90000;
	PageDirectoryPointerTable *pdp = (PageDirectoryPointerTable *)0x91000;
	PageDirectoryTable *pd = (PageDirectoryTable *)0x92000;
	PageTable *pt1 = (PageTable *)0x93000;
	PageTable *pt2 = (PageTable *)0x94000;
	PageDirectoryPointerTable *pdpIdentityMapped = (PageDirectoryPointerTable *)0x95000;
	PageDirectoryTable *pdIdentityMapped = (PageDirectoryTable *)0x96000;
	PageTable *ptIdentityMapped = (PageTable *)0x97000;
	
	// Zero initialize the allocated 4K pages
	memset(pml4, 0, sizeof(PageMapLevel4Table));
	memset(pdp, 0, sizeof(PageDirectoryPointerTable));
	memset(pd, 0, sizeof(PageDirectoryTable));
	memset(pt1, 0, sizeof(PageTable));
	memset(pt2, 0, sizeof(PageTable));
	memset(pdpIdentityMapped, 0, sizeof(PageDirectoryPointerTable));
	memset(pdIdentityMapped, 0, sizeof(PageDirectoryTable));
	memset(ptIdentityMapped, 0, sizeof(PageTable));

	// Point in the 1st PDP entry to the PD
	pdpIdentityMapped->Entries[0].Frame = (unsigned long)pdIdentityMapped / SMALL_PAGE_SIZE;
	pdpIdentityMapped->Entries[0].Present = 1;
	pdpIdentityMapped->Entries[0].ReadWrite = 1;

	// Point in the 1st PD entry to the PT
	pdIdentityMapped->Entries[0].Frame = (unsigned long)ptIdentityMapped / SMALL_PAGE_SIZE;
	pdIdentityMapped->Entries[0].Present = 1;
	pdIdentityMapped->Entries[0].ReadWrite = 1;

	// Identity Mapping of the first 256 small pages of 4K (0 - 1 MB Virtual Address Space)
	// In that area we have all the various I/O ports and the above allocated Page Table Structure
	for (i = 0; i < 256; i++)
	{
		ptIdentityMapped->Entries[i].Frame = i;
		ptIdentityMapped->Entries[i].Present = 1;
		ptIdentityMapped->Entries[i].ReadWrite = 1;
	}

	// Identity Mapping of 0 - 1 MB (up to 0x100000 - just below the Kernel), so that the above allocated Page Tables can be still accessed
	// after we have switched the Page Directory
	pml4->Entries[0].Frame = (unsigned long)pdpIdentityMapped / SMALL_PAGE_SIZE;
	pml4->Entries[0].Present = 1;
	pml4->Entries[0].ReadWrite = 1;

	// Point in the 1st PML4 entry to the PDP
	pml4->Entries[256].Frame = (unsigned long)pdp / SMALL_PAGE_SIZE;
	pml4->Entries[256].Present = 1;
	pml4->Entries[256].ReadWrite = 1;

	// Install the Recursive Page Table Mapping
	pml4->Entries[511].Frame = (unsigned long)pml4 / SMALL_PAGE_SIZE;
	pml4->Entries[511].Present = 1;
	pml4->Entries[511].ReadWrite = 1;

	// Point in the 1st PDP entry to the PD
	pdp->Entries[0].Frame = (unsigned long)pd / SMALL_PAGE_SIZE;
	pdp->Entries[0].Present = 1;
	pdp->Entries[0].ReadWrite = 1;

	// Point in the 1st PD entry to the PT
	pd->Entries[0].Frame = (unsigned long)pt1 / SMALL_PAGE_SIZE;
	pd->Entries[0].Present = 1;
	pd->Entries[0].ReadWrite = 1;

	// Mapping of the first 512 small pages of 4K (0 - 2 MB Virtual Address Space)
	// with a base offset of 0xFFFF800000000000
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt1->Entries[i].Frame = i;
		pt1->Entries[i].Present = 1;
		pt1->Entries[i].ReadWrite = 1;
	}

	// Point in the 2nd PD entry to the 2nd PT
	pd->Entries[1].Frame = (unsigned long)pt2 / SMALL_PAGE_SIZE;;
	pd->Entries[1].Present = 1;
	pd->Entries[1].ReadWrite = 1;

	// Mapping of the next 512 small pages of 4K (2 - 4 MB Virtual Address Space)
	// with a base offset of 0xFFFF800000000000
	for (i = 0; i < PT_ENTRIES; i++)
	{
		pt2->Entries[i].Frame = i + (PT_ENTRIES * 1);
		pt2->Entries[i].Present = 1;
		pt2->Entries[i].ReadWrite = 1;
	}

	// Stores the Memory Address of PML4 in the CR3 register
	SwitchPageDirectory(pml4);
}

// Switches the PML4 Page Table Offset in the CR3 Register
void SwitchPageDirectory(PageMapLevel4Table *PML4)
{
    asm volatile("mov %0, %%cr3":: "r"(PML4));
}

// Handles a Page Fault
void HandlePageFault(unsigned long VirtualAddress)
{
	// Get references to the various Page Tables through the Recursive Page Table Mapping
	PageMapLevel4Table *pml4 = (PageMapLevel4Table *)PML4_TABLE;
	PageDirectoryPointerTable *pdp = (PageDirectoryPointerTable *)PML3_TABLE(VirtualAddress);
	PageDirectoryTable *pd = (PageDirectoryTable *)PML2_TABLE(VirtualAddress);
	PageTable *pt = (PageTable *)PML1_TABLE(VirtualAddress);
	char str[32] = "";

	// Set the screen text color to Green
	int color = SetColor(COLOR_GREEN);

	// Debugging Output
	ltoa(VirtualAddress, 16, str);
	printf("Page Fault at Virtual Address 0x");
	printf(str);
	printf("\n");

	if (pml4->Entries[PML4_INDEX(VirtualAddress)].Present == 0)
	{
		// Allocate a physical frame for the missing PML4 entry
		pml4->Entries[PML4_INDEX(VirtualAddress)].Frame = AllocatePhysicalFrame();
		pml4->Entries[PML4_INDEX(VirtualAddress)].Present = 1;
		pml4->Entries[PML4_INDEX(VirtualAddress)].ReadWrite = 1;

		// Debugging Output
		PageFaultDebugPrint(PML4_INDEX(VirtualAddress), "PML4", pml4->Entries[PML4_INDEX(VirtualAddress)].Frame);
	}

	if (pdp->Entries[PML3_INDEX(VirtualAddress)].Present == 0)
	{
		// Allocate a physical frame for the missing PDP entry
		pdp->Entries[PML3_INDEX(VirtualAddress)].Frame = AllocatePhysicalFrame();
		pdp->Entries[PML3_INDEX(VirtualAddress)].Present = 1;
		pdp->Entries[PML3_INDEX(VirtualAddress)].ReadWrite = 1;

		// Debugging Output
		PageFaultDebugPrint(PML3_INDEX(VirtualAddress), "PDP", pdp->Entries[PML3_INDEX(VirtualAddress)].Frame);
	}

	if (pd->Entries[PML2_INDEX(VirtualAddress)].Present == 0)
	{
		// Allocate a physical frame for the missing PD entry
		pd->Entries[PML2_INDEX(VirtualAddress)].Frame = AllocatePhysicalFrame();
		pd->Entries[PML2_INDEX(VirtualAddress)].Present = 1;
		pd->Entries[PML2_INDEX(VirtualAddress)].ReadWrite = 1;

		// Debugging Output
		PageFaultDebugPrint(PML2_INDEX(VirtualAddress), "PD", pd->Entries[PML2_INDEX(VirtualAddress)].Frame);
	}

	if (pt->Entries[PML1_INDEX(VirtualAddress)].Present == 0)
	{
		// Allocate a physical frame for the missing PT entry
		pt->Entries[PML1_INDEX(VirtualAddress)].Frame = AllocatePhysicalFrame();
		pt->Entries[PML1_INDEX(VirtualAddress)].Present = 1;
		pt->Entries[PML1_INDEX(VirtualAddress)].ReadWrite = 1;

		// Debugging Output
		PageFaultDebugPrint(PML1_INDEX(VirtualAddress), "PT", pt->Entries[PML1_INDEX(VirtualAddress)].Frame);
	}

	printf("\n");

	// Reset the screen tet color
	SetColor(color);
}