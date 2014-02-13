#include "../drivers/common.h"
#include "../drivers/screen.h"

// Function definitions
void TestTabs();
void TestScrolling();
void Sleep();

// Main function of the Kernel
void k_main()
{
	InitializeScreen();
    
    printf("Build on Mac OSX\n");

	/*unsigned char c = inb(0x64);
	printf(c);

	while (1 == 1)
	{
		c = inb(0x60);
		printf(c);
	}*/

	// outb(inb(0x21)&0xfd, 0x21);
	
	// int com = 0;

	/* char scan_code = inb(0x60);
	outb((com=inb(0x61))|0x80, 0x61);
	outb(com&0x7f, 0x61);
	outb(0x20, 0x20);*/

	// TestScrolling();

	// TestTabs();
    
    printf("\n");
    printf("\n");
    printf("Klaus Aschenbrenner\n");
    printf("OS System programming directly on the Mac :-)");
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