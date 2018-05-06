#include "../drivers/common.h"
#include "../drivers/screen.h"

void Sleep();

void k_main()
{
    // Initializes the screen
	InitializeScreen();

	// Initializes the ISR & IRQ routines
    // InitIdt();

	// ScrollScreen();

    printf("Hello World1...");
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
