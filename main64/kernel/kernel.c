#include "../drivers/common.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"

void Sleep();
void TestKeyboardInput();

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

	// RaiseInterrupt();

	// Triggers a Divide by Zero Exception...
	// int i = 1;
	// int k = 0;
	// int j = i / k;

	// ScrollScreen();

    // printf("Hello World1...");

	TestKeyboardInput();
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

void Sleep()
{
	int i;
	for (i = 0;i<20971520;i++)
	{
        /*int a;
        int b;
        int c;
        a = 1;
        b = 1;
        c = a + b;*/
    }
}
