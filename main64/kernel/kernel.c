#include "drivers/common.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "kernel.h"

void k_main()
{
    // Initializes the screen
	InitializeScreen();

	// Initializes the ISR & IRQ routines
    InitIdt();

	// Disable the hardware interrupts
    DisableInterrupts();

	// Initializes the PIC, and remap the IRQ handler
    // 0x20: 32 decimal
    // 0x28: 40 decimal
    PICInitialize(0x20, 0x28);

	// Initialize the system timer to 20 Hertz
    InitTimer(20);

	// Initialize the keyboard
    InitKeyboard();

	// Enable the hardware interrupts again
    EnableInterrupts();

	// Initializes the physical Frame Allocator
	InitializeFrameAllocator(1024 * 1024 * 1024);
	InitializePaging();

	// Initialize the Floppy Disk Controller
	flpydsk_install();
	
	// RaiseInterrupt();

	// Triggers a Divide by Zero Exception...
	// int i = 1;
	// int k = 0;
	// int j = i / k;

	// TestFrameAllocator();

	// ScrollScreen();

	// TestKeyboardInput();

	// ReadSectorFromFloppy();

	TestPageFaults();

	// CommandLoop();
	
	// printf("Done");

	// Halt the system
    for (;;);
}

void TestPageFaults()
{
	char *ptr1 = 0x0000000000600000;
	ptr1[0] = 'A';

	char *ptr2 = 0xFFFFFF1FFFFFFFFF;
	ptr2[0] = 'X';

	char *ptr3 = (char *)0xFFFFF000FFFF0000;
	ptr3[0] = 'K';

	char *ptr = (char *)0xFFFF8000FFFF0000;
	ptr[0] = 'K';
	ptr[1] = 'l';
	ptr[2] = 'a';
	ptr[3] = 'u';
	ptr[4] = 's';

	print_char(*ptr++);
	print_char(*ptr++);
	print_char(*ptr++);
	print_char(*ptr++);
	print_char(*ptr);
}

void CommandLoop()
{
	char input[10] = "";
	int sector;

	while (1 == 1)
	{
		ClearScreen();
		printf("Enter Disk Sector to read: ");
		scanf(input, 8);

		int sector = atoi(input);
		ReadDiskSector(sector);

		scanf(input, 8);
	}
}

void ReadDiskSector(int Sector)
{
	int i = 0;
	char str[32] = "";

	unsigned char *dmaBuffer = (unsigned char *)flpydsk_read_sector(Sector);
	flpydsk_reset();

	// Print out the read disk sector
	for (i = 0; i < 512; i++)
	{
		itoa(dmaBuffer[i], 16, str);

		// unsigned char *Buffer = 0xFFFF8000FFFF0000;
		// memcpy(Buffer, dmaBuffer, 512);
		printf("0x");
		printf(str);
	}
}

// Dumps out the Memory Map
void DumpMemoryMap()
{
	MemoryRegion *region = (MemoryRegion *)0x1000;
	char str[32] = "";
	int i;

	printf("Detected Memory Map:");
	printf("\n");
	printf("=============================================================================");
	printf("\n");

	for (i = 0; i < 7; i++)
	{
		itoa(region[i].Start, 16, str);
		printf("Start: 0x");
		printf(str);

		if (strlen(str) < 6)
		{
			printf("\t");
		}

		printf("\t");
		itoa(region[i].Start + region[i].Size - 1, 16, str);
		printf("End: 0x");
		printf(str);
		printf("\t\t");
		itoa(region[i].Type, 16, str);
		printf("Type: ");
		printf(str);

		printf(" (");
		printf(MemoryRegionType[region[i].Type - 1]);
		printf(")");

		printf("\n");
	}
}

// Tests some Tabular Output
void TestTabs()
{
	printf("FirstName\t\t\tLastName\t\t\tCity\n");
	printf("=========================================================================\n");

	printf("Klaus\t\t\t\tAschenbrenner\t\t\tVienna\n");
	printf("John\t\t\t\tDoe\t\t\t\tLondon\n");
	
	printf("\n2 row(s) affected");
}

// Tests the Keyboard Input
void TestKeyboardInput()
{
    char first_name[80];
    printf("Enter your first name: ");
    scanf(first_name, 78);
    
    char last_name[80];
    printf("Enter your last name: ");
    scanf(last_name, 78);
    
    printf("Your name is ");
    printf(first_name);
    printf(" ");
    printf(last_name);
}

// Tests the scrolling of the Screen
void ScrollScreen()
{
	while (1 == 1)
	{
		printf("Line 1\n");
		Sleep();
		printf("Line 2\n");
		Sleep();
		printf("Line 3\n");
		Sleep();
		printf("Line 4\n");
		Sleep();
		printf("Line 5\n");
		Sleep();
		printf("Line 6\n");
		Sleep();
		printf("Line 7\n");
		Sleep();
		printf("Line 8\n");
		Sleep();
		printf("Line 9\n");
		Sleep();
		printf("Line 10\n");
		Sleep();
	}
}