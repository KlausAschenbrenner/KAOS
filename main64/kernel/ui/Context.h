//
//  Context.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_Context_h
#define KAOS_Context_h

// Font properties
#define FONT_WIDTH 8
#define FONT_HEIGHT 12
#define FONT_CHARACTERS 128

// Defines the Drawing Context
typedef struct _Context
{
    unsigned short *FrameDoubleBuffer;
    unsigned short *VgaFrameBuffer;
    int Width;
    int Height;
    int TranslateX;
    int TranslateY;
} Context;

// Creates a new Context
Context *NewContext(int Width, int Height, unsigned char *FrameDoubleBuffer, unsigned char *VgaFrameBuffer);

// Draws a filled Rectangle
void ContextFillRect(Context *Context, int X, int Y, unsigned int Width, unsigned int Height, int Color);

// Draws a Rectangle
void ContextDrawRectangle(Context *Context, int X, int Y, int Width, int Height, int Color);

// Draws a horizontal line
void ContextDrawHorizontalLine(Context *Context, int X, int Y, int Length, int Color);

// Draws a vertical line
void ContextDrawVerticalLine(Context *Context, int X, int Y, int Length, int Color);

// Draws a null-terminated String at the given location
void DrawString(Context *Context, char *String, int X, int Y, int Color);

// Draws a single Character
static void DrawCharacter(Context *Context, char Character, int X, int Y, int Color);

#endif