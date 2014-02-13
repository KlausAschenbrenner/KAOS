#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_MEMORY 0xB8000
#define ROWS 25
#define COLS 80

// Text mode color constants
enum VGA_Color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15
};

// This struct contains information about the screen
typedef struct ScreenLocation
{
		// The current row on the screen
		int Row;

		// The current column on the screen
		int Col;

		// The used attributes
		int Attributes;
} ScreenLocation;

// Define a variable for the screen location information
ScreenLocation screenLocation;

// Prints a single character
void print_char(char character);

// Prints a null-terminated string
void printf(char *string);

#endif