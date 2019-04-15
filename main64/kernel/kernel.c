#include "drivers/common.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "kernel.h"
#include "Heap/Heap.h"
#include "Tasks/Task.h"

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
	InitTimer(100000);

	// Initialize the keyboard
    InitKeyboard();

	// Enable the hardware interrupts again
    EnableInterrupts();

	// Initializes the physical Frame Allocator
	InitializeFrameAllocator(1024 * 1024 * 1024);
	InitializePaging();

	// Initializes the Heap Manager
	InitHeap();

	// Initialize the Floppy Disk Controller
	flpydsk_install();

	// Creates the various Kernel Tasks that are executed through Context Switching
	CreateKernelTasks();

	// Initialize the Context Switching through IRQ0
	// As soon as the Context Swichting is in place, we will *never* resume with the code execution here!
	// Everything is done in the various executed Tasks and in the IRQ handlers!
	InitTimerForContextSwitching();

	// Execute the Command Shell
	// CommandLoop();

	printf("Done\n");
	
	// Halt the system
    for (;;);
}



void Dummy()
{
	int cntr = 0;

	while (1 == 1)
	{
		cntr++;
		long *value = (long *)0xFFFF800000700000;
		*value = cntr;

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void TestHeap()
{
	void *ptr1 = malloc(100);
	void *ptr2 = malloc(100);
	void *ptr3 = malloc(100);
	void *ptr4 = malloc(100);
	
	free(ptr2);
	free(ptr3);
	
	void *ptr5 = malloc(5000);
	void *ptr6 = malloc(204);
	void *ptr7 = malloc(2768);

	free(ptr1);
	free(ptr7);
	free(ptr5);
	free(ptr4);
	free(ptr6);

	void *ptr8 = malloc(20000);
	free(ptr8);
	
	DumpHeap();
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

// Implements a simple Command Shell
void CommandLoop()
{
	char input[100] = "";
	ClearScreen();

	while (1 == 1)
	{
		printf("A:\>");
		scanf(input, 98);

		if (strcmp(input, "dir") == 0)
		{
			PrintRootDirectory();
		}
		else if (strcmp(input, "cls") == 0)
		{
			ClearScreen();
		}
		else if (strcmp(input, "shutdown") == 0)
		{
			printf("Shutting down KAOS...\n");
		}
		else if (strcmp(input, "reboot") == 0)
		{
			printf("Rebooting KAOS...\n");
		}
		else if (strcmp(input, "status") == 0)
		{
			// Print out the calculated value from the other running Task...
			long *value = (long *)0xFFFF800000700000;
			printf_long(*value, 10);
		}
		else if (strcmp(input, "ps") == 0)
		{
			DumpTaskState();
		}
		else
		{
			// Try to load the requested program into memory
			if (LoadProgram(input) != 0)
			{
				// The program was loaded successfully into memory.
				// Let's execute it now!
				ExecuteProgram();
			}
			else
			{
				printf("'");
				printf(input);
				printf("' is not recognized as an internal or external command,\n");
				printf("operable program or batch file.\n\n");
			}
		}
	}
}

void CreateKernelTasks()
{
	CreateKernelTask(CommandLoop, 1, 0xFFFF800001100000);
	CreateKernelTask(Dummy, 2, 0xFFFF800001200000);
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