#include "common.h"
#include "screen.h"

// Initializes the screen.
void InitializeScreen()
{
	screenLocation.Row = 1;
	screenLocation.Col = 1;
	screenLocation.Attributes = COLOR_LIGHT_MAGENTA;
}

// Returns the current cursor position
void GetCursorPosition(int *Row, int *Col)
{
    *Row = screenLocation.Row;
    *Col = screenLocation.Col;
}

// Sets the current cursor position
void SetCursorPosition(int Row, int Col)
{
    screenLocation.Row = Row;
    screenLocation.Col = Col;
    MoveCursor();
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

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// Converts an integer value to a string value for a specific base (base 10 => decimal, base 16 => hex)
void itoa(int i, unsigned base, char *buf)
{
    if (base > 16) return;
    
    if (i < 0)
    {
        *buf++ = '-';
        i *= -1;
    }
    
    itoa_s(i, base, buf);
}

static void itoa_s(unsigned i, unsigned base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    
    if (i == 0 || base > 16)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    
    while (i != 0)
    {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    
    top = pos--;
    
    for (opos = 0; opos < top; pos--,opos++)
    {
        buf[opos] = tbuf[pos];
    }
    
    buf[opos] = 0;
}