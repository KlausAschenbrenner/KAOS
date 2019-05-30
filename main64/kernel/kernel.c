#include "drivers/common.h"
#include "drivers/screen.h"
#include "drivers/timer.h"
#include "drivers/keyboard.h"
#include "kernel.h"
#include "Heap/Heap.h"
#include "Tasks/Task.h"
#include "structs/KPCR.h"
#include "idt/idt.h"
#include "ui/Window.h"
#include "ui/Desktop.h"
#include "ui/Controls/Button.h"
#include "ui/Controls/Label.h"
#include "ui/Controls/TextBox.h"
#include "ui/Controls/MultiLineTextBox.h"
#include "ui/Controls/Bitmap.h"

void Shell();
Context *context = 0x0;
Desktop *desktop = 0x0;
TextBox *textbox = 0x0;
MultiLineTextBox *multiLineTextBox1 = 0x0;
Label *desktopLabel = 0x0;

// Indicates if KAOS is executed with a GUI or in Text Mode
int UIMode = 1;

void k_main()
{
    // Initializes the screen
	InitializeScreen();

	// Initializes the ISR & IRQ routines
    InitIdt();

	// Disable the hardware interrupts
    DisableInterrupts();

	// Initializes the PIC, and remap the IRQ handler
    PICInitialize(0x20, 0x28);

	// Initialize the system timer to 250 Hertz - a 4ms quantum for the Context Switching mechanism
	InitTimer(250);

	// Initialize the keyboard
    InitKeyboard();

	// Enable the hardware interrupts again
    EnableInterrupts();

	// Initializes the physical Frame Allocator
	InitializeFrameAllocator(1024 * 1024 * 1024);
	InitializePaging();
	
	// Initializes the Heap Manager
	InitHeap();

	// Initializes the KPCR Data Structures
	InitKPCR();

	// Initializes the GDT
	// This also includes Selectors for Ring 3 and the TSS
	InitGdt();

	// Initialize the Floppy Disk Controller
	flpydsk_install();

	if (UIMode == 1)
	{
		// Initializes the Window System
		InitWindowSystem();

		// Creates the various Tasks that are executed through Context Switching
		CreateTasksVGA();
	}
	else
	{
		// Creates the various Tasks that are executed through Context Switching
		CreateTasks();
	}
	
	// Initialize the Context Switching through IRQ0
	// As soon as the Context Swichting is in place, we will *never* resume with the code execution here!
	// Everything is done in the various executed Tasks and in the IRQ handlers!
	InitTimerForContextSwitching();

	// Halt the system
    while (1 == 1);
}

void InitWindowSystem()
{
	// Create a new Drawing Context
	context = (Context *)NewContext(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_DOUBLE_BUFFER, WINDOW_FRAME_BUFFER);
	
	// Create a new Desktop and set the intial mouse position
	desktop = (Desktop *)NewDesktop(context, 0x05FF);
	desktop->MouseX = 50;
	desktop->MouseY = 50;

	// Create a Label on the Desktop
	desktopLabel = NewLabel(5, 15, "0", context);
	WindowInsertChild((Window *)desktop, (Window *)desktopLabel);

	Bitmap *bitmap = NewBitmap("logo", 480, 5, 0, 0x0000, context);
	WindowInsertChild((Window *)desktop, (Window *)bitmap);
}

// Initializes the KPCR Data Structure
void InitKPCR()
{
	KPCR *kpcr = malloc(sizeof(KPCR));
	kpcr->IDT = IDT_START_OFFSET;

	// Moves the KPCR pointer to the R14 register for further references
	MoveKPCRToRegister(kpcr);
}

// Handles the OnClick event of the Button
void ButtonOnClick(Window *ButtonWindow, int X, int Y)
{
	// Make a copy of the entered string and store it in the MultiLineTextBox
	char *str = malloc(100);
	strcpy(str, &textbox->Text);
	AddNodeToList(multiLineTextBox1->TextLines, str);
}

void DesktopWindow1()
{
	char str1[32] = "";
	char str2[32] = "";
	int cntr = 0;
	int i;
	Window *window = NewDesktopWindow((Window *)desktop, 50, 50, 400, 720, "Window Title 1");
	window->Task = (Task *)GetTaskState();
	
	// Create a new Button
	Button *button = NewButton(10, 100, 100, 35, "Button 1", "", 0, 0, 0, 0x0000, context);
	button->OnClick = ButtonOnClick;
	WindowInsertChild(window, (Window *)button);

	// Create a new Label
	Label *label = NewLabel(5, 5, "PID: ", context);
	WindowInsertChild(window, (Window *)label);

	// Create a new Label
	ltoa(window->Task->PID, 10, str1);
	Label *lbl2 = NewLabel(25, 5, str1, context);
	WindowInsertChild(window, (Window *)lbl2);

	// Create a new Label
	Label *lbl3 = NewLabel(5, 15, "Number of Context Switches:", context);
	WindowInsertChild(window, (Window *)lbl3);

	// Create a new Label
	Label *lbl4 = NewLabel(115, 15, "0", context);
	WindowInsertChild(window, (Window *)lbl4);

	for (i = 0; i < 15; i++)
	{
		// Create a new TextBox
		TextBox *textbox = NewTextBox(10, 150 + (i * 30), 100, 20, context);
		WindowInsertChild(window, (Window *)textbox);
	}

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox1 = NewMultiLineTextBox(10, 330, 200, 100, context);
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox1);

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox2 = NewMultiLineTextBox(10, 450, 200, 100, context);
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox2);

	while (1 == 1)
	{
		// Change a Control content and invalidate the Control
		ltoa(window->Task->ContextSwitches, 10, str2);
		LabelSetTitle(lbl4, str2);
		WindowInvalidate((Window *)desktop, (Window *)lbl4);

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void DesktopWindow2()
{
	char str1[32] = "";
	char str2[32] = "";
	int i;
	Window *window = NewDesktopWindow((Window *)desktop, 200, 200, 400, 720, "Window Title 2");
	window->Task = (Task *)GetTaskState();
	
	// Create a new Button
	Button *button = NewButton(10, 100, 100, 35, "Button 1", "", 0, 0, 0, 0x0000, context);
	WindowInsertChild(window, (Window *)button);

	// Create a new Label
	Label *label = NewLabel(5, 5, "PID: ", context);
	WindowInsertChild(window, (Window *)label);

	// Create a new Label
	ltoa(window->Task->PID, 10, str1);
	Label *lbl2 = NewLabel(25, 5, str1, context);
	WindowInsertChild(window, (Window *)lbl2);

	// Create a new Label
	Label *lbl3 = NewLabel(5, 15, "Number of Context Switches:", context);
	WindowInsertChild(window, (Window *)lbl3);

	// Create a new Label
	Label *lbl4 = NewLabel(115, 15, "0", context);
	WindowInsertChild(window, (Window *)lbl4);

	for (i = 0; i < 6; i++)
	{
		// Create a new TextBox
		TextBox *textbox = NewTextBox(10, 150 + (i * 30), 100, 20, context);
		WindowInsertChild(window, (Window *)textbox);
	}

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox1 = NewMultiLineTextBox(10, 330, 200, 100, context);
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox1);

	while (1 == 1)
	{
		// Change a Control content and invalidate the Control
		ltoa(window->Task->ContextSwitches, 10, str2);
		LabelSetTitle(lbl4, str2);
		WindowInvalidate((Window *)desktop, (Window *)lbl4);

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void DesktopWindow3()
{
	char str1[32] = "";
	char str2[32] = "";
	int cntr = 0;
	Window *window = NewDesktopWindow((Window *)desktop, 300, 300, 400, 720, "Window Title 3");
	window->Task = (Task *)GetTaskState();
	
	// Create a new Button
	Button *button = NewButton(10, 100, 100, 35, "Button 1", "", 0, 0, 0, 0x0000, context);
	WindowInsertChild(window, (Window *)button);

	// Create a new Label
	Label *label = NewLabel(5, 5, "PID: ", context);
	WindowInsertChild(window, (Window *)label);

	// Create a new Label
	ltoa(window->Task->PID, 10, str1);
	Label *lbl2 = NewLabel(25, 5, str1, context);
	WindowInsertChild(window, (Window *)lbl2);

	// Create a new Label
	Label *lbl3 = NewLabel(5, 15, "Number of Context Switches:", context);
	WindowInsertChild(window, (Window *)lbl3);

	// Create a new Label
	Label *lbl4 = NewLabel(115, 15, "0", context);
	WindowInsertChild(window, (Window *)lbl4);

	// Create a new TextBox
	TextBox *textbox1_window3 = NewTextBox(10, 150, 100, 20, context);
	WindowInsertChild(window, (Window *)textbox1_window3);

	// Create a new TextBox
	TextBox *textbox2_window3 = NewTextBox(10, 180, 100, 20, context);
	WindowInsertChild(window, (Window *)textbox2_window3);

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox1 = NewMultiLineTextBox(10, 210, 200, 100, context);
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox1);

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox2 = NewMultiLineTextBox(10, 330, 200, 100, context);
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 3");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 4");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 5");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 6");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 7");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 8");
	AddNodeToList(multiLineTextBox2->TextLines, "Test Line 9");
	WindowInsertChild(window, (Window *)multiLineTextBox2);

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox3 = NewMultiLineTextBox(10, 450, 200, 100, context);
	AddNodeToList(multiLineTextBox3->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox3->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox3->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox3);

	// Create a new MultiLineTextBox
	MultiLineTextBox *multiLineTextBox4 = NewMultiLineTextBox(10, 570, 200, 100, context);
	AddNodeToList(multiLineTextBox4->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox4->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox4->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox4);

	while (1 == 1)
	{
		// Change a Control content and invalidate the Control
		ltoa(window->Task->ContextSwitches, 10, str2);
		LabelSetTitle(lbl4, str2);
		WindowInvalidate((Window *)desktop, (Window *)lbl4);

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void DesktopWindow4()
{
	char str1[32] = "";
	char str2[32] = "";
	int i;
	Window *window = NewDesktopWindow((Window *)desktop, 750, 200, 400, 720, "Window Title 4");
	window->Task = (Task *)GetTaskState();

	// Create a new Label
	Label *label = NewLabel(5, 5, "PID: ", context);
	WindowInsertChild(window, (Window *)label);

	// Create a new Label
	ltoa(window->Task->PID, 10, str1);
	Label *lbl2 = NewLabel(25, 5, str1, context);
	WindowInsertChild(window, (Window *)lbl2);

	// Create a new Button
	Button *button = NewButton(10, 80, 100, 35, "Add Item", "", 0, 0, 0, 0x0000, context);
	button->OnClick = ButtonOnClick;
	WindowInsertChild(window, (Window *)button);

	// Create a new TextBox
	textbox = NewTextBox(10, 130, 100, 20, context);
	WindowInsertChild(window, (Window *)textbox);

	// Create a new MultiLineTextBox
	multiLineTextBox1 = NewMultiLineTextBox(10, 160, 200, 100, context);
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 1");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 2");
	AddNodeToList(multiLineTextBox1->TextLines, "Test Line 3");
	WindowInsertChild(window, (Window *)multiLineTextBox1);

	while (1 == 1)
	{
		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void CalculateSomething()
{
	char str[32] = "";
	int cntr = 0;

	while (1 == 1)
	{
		// Increment the calculated value
		cntr++;
		long *value = (long *)0xFFFF800000700000;
		*value = cntr;

		// Display the value on the Desktop
		itoa(*value, 10, str);
		LabelSetTitle(desktopLabel, str);
		WindowInvalidate((Window *)desktop, (Window *)desktopLabel);

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

void Dummy()
{
	while (1 == 1)
	{
		// Bitmap *bitmap = ReadBitmap("Delete");

		// Introduce some delay in the calculation...
		Sleep(99999999);
	}
}

// Simulates a simple Mouse through various keystrokes
void MouseHandler()
{
	int MouseX = 50;
	int MouseY = 50;
	int mouseClick = 0;
	int dragWindow = 0;

	// Prior making updates to the screen, we disable the Interrupts, so that no Context Switching happens in the mean time.
	// This makes everything more smoother...
	DisableInterrupts();

	// Draw initially the whole Desktop
	WindowPaint((Window *)desktop, 0x0, 0);

	// Enable the Interrupts again
	EnableInterrupts();

	while (1 == 1)
	{
		// Get the next keystroke that moves the mouse on the Desktop
		char originalInput = getchar();
		char input = KeyboardKeyToASCII(originalInput, 1);
		
		if (input != 0)
		{
			// Left + 1
			if (input == 'a')
			{
				MouseX--;
			}
			// Left + 10
			else if (input == 'j')
			{
				MouseX -= 10;
			}
			// Right + 1
			else if (input == 'f')
			{
				MouseX++;
			}
			// Right + 10
			else if (input == 'l')
			{
				MouseX += 10;
			}
			// Up + 1
			else if (input == 'e')
			{
				MouseY--;
			}
			// Up + 10
			else if (input == 'i')
			{
				MouseY -= 10;
			}
			// Down + 1
			else if (input == 'x')
			{
				MouseY++;
			}
			// Down + 10
			else if (input == 'm')
			{
				MouseY += 10;
			}
			// Mouse Click
			else if (input == ' ')
			{
				mouseClick = 1;
			}
			// Dragging Left + 1
			else if (input == 'A')
			{
				MouseX -= 1;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Left + 10
			else if (input == 'J')
			{
				MouseX -= 10;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Right + 1
			else if (input == 'F')
			{
				MouseX++;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Right + 10
			else if (input == 'L')
			{
				MouseX += 10;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Up + 1
			else if (input == 'E')
			{
				MouseY--;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Up + 10
			else if (input == 'I')
			{
				MouseY -= 10;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Down + 1
			else if (input == 'X')
			{
				MouseY++;
				mouseClick = 1;
				dragWindow = 1;
			}
			// Dragging Down + 10
			else if (input == 'M')
			{
				MouseY += 10;
				mouseClick = 1;
				dragWindow = 1;
			}
		}

		// Limit the Mouse to the current screen area
		if (MouseX < 0)
			MouseX = 0;

		if (MouseY < 0)
			MouseY = 0;

		if (MouseX > WINDOW_WIDTH - MOUSE_WIDTH)
			MouseX = WINDOW_WIDTH - MOUSE_WIDTH;

		if (MouseY > WINDOW_HEIGHT - 5)
			MouseY = WINDOW_HEIGHT - 5;

		// Prior making updates to the screen, we disable the Interrupts, so that no Context Switching happens in the mean time.
		// This makes everything more smoother...
		DisableInterrupts();
		
		// Process the Mouse Event
		DesktopProcessMouse(desktop, MouseX, MouseY, mouseClick, dragWindow);
		mouseClick = 0;
		dragWindow = 0;

		// Process the Key Press Event
		DesktopProcessKey(desktop, originalInput);

		// Update the whole screen
    	WindowPaint((Window *)desktop, 0x0, 0);

		// Enable the Interrupts again
		EnableInterrupts();
		
		// Print the mouse coordinates out to the console
		printf_int(MouseX, 16);
		printf(", ");
		printf_int(MouseY, 16);
		printf("\n");
	}
}

void CreateTasksVGA()
{
	CreateKernelTask(MouseHandler, 1, 0xFFFF800001100000);
	CreateKernelTask(CalculateSomething, 2, 0xFFFF800001200000);

	// CreateUserTask(DesktopWindow1, 3, 0xFFFF800001300000, 0xFFFF800001310000);
	// CreateUserTask(DesktopWindow2, 4, 0xFFFF800001400000, 0xFFFF800001410000);
	// CreateUserTask(DesktopWindow3, 5, 0xFFFF800001500000, 0xFFFF800001510000);
	
	/* CreateUserTask(DesktopWindow1, 3, 0xFFFF800001300000, 0xFFFF800000030000);
	CreateUserTask(DesktopWindow2, 4, 0xFFFF800001400000, 0xFFFF800000040000);
	CreateUserTask(DesktopWindow3, 5, 0xFFFF800001500000, 0xFFFF800000050000); */

	CreateKernelTask(DesktopWindow1, 3, 0xFFFF800001300000);
	CreateKernelTask(DesktopWindow2, 4, 0xFFFF800001400000);
	CreateKernelTask(DesktopWindow3, 5, 0xFFFF800001500000);
	CreateKernelTask(DesktopWindow4, 6, 0xFFFF800001600000);
}

void CreateTasks()
{
	// The Command Shell is running in Ring 0
	CreateKernelTask(Shell, 1, 0xFFFF800001100000);

	// All the remaining Tasks are running in Ring 3
	CreateKernelTask(Dummy, 2, 0xFFFF800001200000);

	/* CreateKernelTask(DesktopWindow1, 3, 0xFFFF800001300000);
	CreateKernelTask(DesktopWindow2, 4, 0xFFFF800001400000);
	CreateKernelTask(DesktopWindow3, 5, 0xFFFF800001500000); */

	/* CreateUserTask(DesktopWindow1, 4, 0xFFFF800001400000, 0xFFFF800000040000);
	CreateUserTask(DesktopWindow2, 5, 0xFFFF800001500000, 0xFFFF800000050000);
	CreateUserTask(DesktopWindow3, 6, 0xFFFF800001600000, 0xFFFF800000060000); */
}

/* void TestScheduler()
{
	char input[10] = "";
	CreateKernelTask(CommandLoop, 1, 0xFFFF800001100000);
	CreateKernelTask(Program1, 2, 0xFFFF800001200000);
	CreateKernelTask(Program2, 3, 0xFFFF800001300000);
	CreateKernelTask(Program3, 4, 0xFFFF800001400000);
	CreateKernelTask(Program4, 5, 0xFFFF800001500000);
	CreateKernelTask(Program5, 6, 0xFFFF800001600000);
	CreateKernelTask(Program6, 7, 0xFFFF800001700000);
	CreateKernelTask(Program7, 8, 0xFFFF800001800000);
	CreateKernelTask(Program8, 9, 0xFFFF800001900000);

	DumpRunnableQueue();
	printf("Continue?\n");
	printf("\n");
	scanf(input, 8);

	while (1 == 1)
	{
		// ClearScreen();
		DumpRunnableQueue();
		printf("Enter PID to delete:\n");
		scanf(input, 8);

		int pid = atoi(input);

		if (pid > 0)
			TerminateTask(pid);

		MoveToNextTask();
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
} */