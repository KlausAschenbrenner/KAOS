#include "drivers/common.h"
#include "drivers/screen.h"
#include "drivers/keyboard.h"
#include "drivers/floppy.h"
#include "kaosldr.h"

extern void RaiseInterrupt();
extern void SwitchToLongMode();

// Main function of the Kernel
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
    
    // Initialize the keyboard
    InitKeyboard();
    
    // Enable the hardware interrupts again
    EnableInterrupts();

	flpydsk_install();
    
    // Raise some example interrupts
    // RaiseInterrupt();

	// TestScrolling();

	// TestTabs();

	// CommandLoop();

	LoadRootDirectory();

	SwitchToLongMode();
}

void CommandLoop()
{
	char input[10];

	while (1 == 1)
	{
		printf("Which Floppy Disk Sector do you want to read: ");
    	scanf(input, 10);
		int sector = atoi(input);
		ClearScreen();

		// Read the sector from disk
		ReadSectorFromFloppy(sector);

		scanf(input, 10);
		ClearScreen();
	}
}

void ReadSectorFromFloppy(int sector)
{
	unsigned char *buffer = flpydsk_read_sector(sector);
	flpydsk_reset();

	// Copy the data to somewhere else in memory
	unsigned char *memoryBuffer = 0x30000;
	memcpy(memoryBuffer, buffer, 512);
	
	int i = 0;
	char str[32] = "";

	// Print out the read disk sector
	for (i = 0; i < 512; i++)
	{
		itoa(memoryBuffer[i], 16, str);
		printf("0x");
		printf(str);
		// printf(" ");
	}
}

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

void TestDivideByZeroException()
{
    int i = 1;
    int j = 0;
    
    int k = i / j;
}

void TestTabs()
{
	printf("FirstName\t\t\tLastName\t\t\tCity\n");
	printf("=========================================================================\n");

	printf("Klaus\t\t\t\tAschenbrenner\t\t\tVienna\n");
	printf("John\t\t\t\tDoe\t\t\t\tLondon\n");
	
	printf("\n2 row(s) affected");
}

void TestScrolling()
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
		printf("Line 11\n");
		Sleep();
		printf("Line 12\n");
		Sleep();
		printf("Line 13\n");
		Sleep();
		printf("Line 14\n");
		Sleep();
		printf("Line 15\n");
		Sleep();
		printf("Line 16\n");
		Sleep();
		printf("Line 17\n");
		Sleep();
		printf("Line 18\n");
		Sleep();
		printf("Line 19\n");
		Sleep();
		printf("Line 20\n");
		Sleep();
		printf("Line 21\n");
		Sleep();
		printf("Line 22\n");
		Sleep();
		printf("Line 23\n");
		Sleep();
		printf("Line 24\n");
		Sleep();
		printf("Line 25\n");
		Sleep();
		printf("Line 26\n");
		Sleep();
		printf("Line 27\n");
		Sleep();
		printf("Line 28\n");
		Sleep();
		printf("Line 29\n");
		Sleep();
		printf("Line 30\n");
	}
}

void Sleep(int Count)
{
	int i;
	for (i = 0;i<Count;i++)
	{}
}