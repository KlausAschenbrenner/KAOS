#include "common.h"
#include "screen.h"

// Initializes the screen.
void InitializeScreen()
{
	screenLocation.Row = 1;
	screenLocation.Col = 1;
	screenLocation.Attributes = COLOR_LIGHT_MAGENTA;
}

// Moves the screen cursor to the current location on the screen.
void MoveCursor()
{
   // Calculate the linear offset of the cursor
   short cursorLocation = (screenLocation.Row - 1) * COLS + (screenLocation.Col - 1);

   // Setting the cursor's high byte
   outb(0x3D4, 14);
   outb(0x3D5, cursorLocation >> 8);
   
   // Setting the cursor's low byte
   outb(0x3D4, 15);
   outb(0x3D5, cursorLocation);
}

// Scrolls the screen, when we have used more than 25 rows.
void Scroll()
{
   // Get a space character with the default colour attributes.
   unsigned char attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
   unsigned short blank = 0x20 /* space */ | (attributeByte << 8);
   char* video_memory = (char *)VIDEO_MEMORY;

   // Row 25 is the end, this means we need to scroll up
   if (screenLocation.Row > ROWS)
   {
	   int i;
	   for (i = 0; i < COLS * 2 * (ROWS - 1); i++)
	   {
		   video_memory[i] = video_memory[i + (COLS * 2)];
	   }

	   // Blank the last line
	   for (i = (ROWS - 1) * COLS * 2; i < ROWS * COLS * 2; i += 2)
	   {
		   video_memory[i] = blank;
		   video_memory[i + 1] = attributeByte;
	   }

	   screenLocation.Row = 25;
   }
}

// Prints a single character on the screen.
void print_char(char character)
{
	char* video_memory = (char *)VIDEO_MEMORY;
	
	switch(character)
	{
		case '\n':
		{
			// New line
			screenLocation.Row++;
			screenLocation.Col = 1;

			break;
		}
		case '\t':
		{
			// Tab
			screenLocation.Col = (screenLocation.Col + 8) & ~ (8 - 1);
			break;
		}
		default:
		{
			int offset = (screenLocation.Row - 1) * COLS * 2 + (screenLocation.Col - 1) * 2;
			video_memory[offset] = character;
			video_memory[offset + 1] = screenLocation.Attributes;
			screenLocation.Col++;

			break;
		}
	}

	Scroll();
	MoveCursor();
}

// Prints out a null-terminated string.
void printf(char *string)
{
	while (*string != '\0')
	{
		print_char(*string);
		string++;
	}
}