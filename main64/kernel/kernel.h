//
//  kernel.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 02.06.2018.
//  Copyright (c) 2018 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_kernel_h
#define KAOS_kernel_h

typedef struct MemoryRegion
{
	long Start;
	long Size;
	int	Type;
	int	Reserved;
} MemoryRegion;

char *MemoryRegionType[] =
{
	"Available",
	"Reserved",
	"ACPI Reclaim",
	"ACPI NVS Memory"
};

// Main Entry for the x64 Kernel
void k_main();

// Dumps out the Memory Map
void DumpMemoryMap();

// Tests some Tabular Output
void TestTabs();

// Tests the Keyboard Input
void TestKeyboardInput();

// Tests the scrolling of the Screen
void ScrollScreen();

#endif