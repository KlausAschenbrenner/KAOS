//
//  Desktop.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_Desktop_h
#define KAOS_Desktop_h

#include "window.h"

// Mouse properties
#define MOUSE_WIDTH 11
#define MOUSE_HEIGHT 18
#define MOUSE_BUFFER_SIZE (MOUSE_WIDTH * MOUSE_HEIGHT)
#define cX 0x0000   // A black pixel for the Mouse Pointer
#define cO 0xFFFF   // A white pixel for the Mouse Pointer
#define c_ 0xDEAD   // The transparent pixel for the Mouse Pointer

// Defines the Desktop
typedef struct _Desktop
{
    Window Window;
    int MouseX;
    int MouseY;
} Desktop;

// Creates a new Desktop
Desktop *NewDesktop(Context *Context, int Color);

// Adds a new Window to the Desktop
Window *NewDesktopWindow(Window *InputWindow, int X, int Y, int Width, int Height, char *Title);

// Processes the mouse on the Desktop
void DesktopProcessMouse(Desktop *Desktop, int MouseX, int MouseY, int MouseClick, int DragWindow);

// Draws the Mouse Pointer Image onto the Desktop
void MousePointerPaint(Desktop *Desktop);

// Draws the Desktop
static void DesktopPaintHandler(Window *DesktopWindow);

#endif