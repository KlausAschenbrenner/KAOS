#include "../drivers/common.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"
#include "kernel.h"

extern void RaiseInterrupt();

// Main function of the Kernel
void k_main()
{
    // Initializes the screen
	InitializeScreen();
    
    // Initializes the ISR & IRQ routines
    InitIdt();
    
    // Disable the hardware interrupts
    DisableInterrupts();
    
    // Initializes the PIC
    // 0x20: 32 decimal
    // 0x28: 40 decimal
    PICInitialize(0x20, 0x28);
    
    // Initialize the system timer to 20 Hertz
    InitTimer(20);
    
    // Enable the hardware interrupts again
    EnableInterrupts();
    
    printf("Build on Mac OSX\n");
    
    // int i = 1;
    // int j = 0;
    
    // int k = i / j;
    
    // Raise some example interrupts
    // RaiseInterrupt();

	// TestScrolling();

	// TestTabs();
    
    printf("\n");
    printf("\n");
    printf("Klaus Aschenbrenner\n");
    printf("OS System programming directly on the Mac\n");
    printf("The source code is stored in a GitHub repository\n");
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

void Sleep()
{
	int i;
	for (i = 0;i<2097152;i++)
	{}
}