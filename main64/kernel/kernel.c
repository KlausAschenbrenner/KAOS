#include "../drivers/common.h"
#include "../drivers/screen.h"
#include "../drivers/timer.h"
#include "../drivers/keyboard.h"

void Sleep();
void TestKeyboardInput();
void DumpMemoryMap();
void CreatePagingTables();

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

	// Print out the detected Memory Map
	DumpMemoryMap();

	// Initializes the Physical Frame Allocator and the Paging Tables in the CR3 Register
	InitializePaging(1024 * 1024 * 1024, 0x0000000000110000, 0x000000003FEEFFFF);

	// RaiseInterrupt();

	// Triggers a Divide by Zero Exception...
	// int i = 1;
	// int k = 0;
	// int j = i / k;

	// ScrollScreen();

	// Up to this address both characters are shown correctly
	// char *ptr = 0x000000000019FFFE;

	// At the adrdess 0x0000000000200000 we get a Page Fault (0xE), because we have only Identity-Mapped the first 2 MB of Virtual Address Space
	// char *ptr = 0x00000000001FFFFE;
	// char *ptr = (char *)0x000000000030FF00;
	char *ptr = (char *)0xFFFF8000FFFF0000;
	ptr[0] = 'a';
	ptr[1] = 'b';
	print_char(*ptr++);
	print_char(*ptr);

	// Halt the system
    for (;;);
}

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

void TestTabs()
{
	printf("FirstName\t\t\tLastName\t\t\tCity\n");
	printf("=========================================================================\n");

	printf("Klaus\t\t\t\tAschenbrenner\t\t\tVienna\n");
	printf("John\t\t\t\tDoe\t\t\t\tLondon\n");
	
	printf("\n2 row(s) affected");
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
