//
//  Window.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_window_h
#define KAOS_window_h

#include "../Tasks/Task.h"
#include "ListNode.h"
#include "List.h"
#include "Rectangle.h"
#include "Context.h"

// Virtual and physical memory adresess
#define WINDOW_FRAME_BUFFER          0xFFFF8000E8000000
#define WINDOW_DOUBLE_BUFFER         0xFFFF800008000000
#define WINDOW_FRAME_BUFFER_PHYSICAL 0x00000000E8000000

// Screen properties
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024
#define WINDOW_BPP 16

// Window properties
#define WINDOW_BACKGROUND_COLOR 0xDF1C
#define WINDOW_TITLE_COLOR_ACTIVE 0x12BA
#define WINDOW_TITLE_COLOR_INACTIVE 0xA555
#define WINDOW_BORDERCOLOR 0
#define WINDOW_TITLEHEIGHT 31
#define WINDOW_BORDERWIDTH 3

// Flags
#define WINDOW_NODECORATION 0x1

// The Paint Handler for a given Window
typedef void (*WindowPaintFunctionHandler)(struct _Window*);

// The Mouse Handler for a given Window
typedef void (*WindowMouseDownFunctionHandler)(struct _Window*, int, int);

// The Key Handler for a given Window
typedef void (*KeyPressFunctionHandler)(struct _Window*, char Key);

// Defines a Window
typedef struct _Window
{
    struct _Window *Parent;
    int X;
    int Y;
    int Width;
    int Height;
    int Flags;
    Context *Context;
    struct _Window *DraggedChild;
    struct _Window *ActiveChild;
    List *Children;
    int DragOffsetX;
    int DragOffsetY;
    int LastMouseButtonState;
    WindowPaintFunctionHandler PaintFunction;
    WindowMouseDownFunctionHandler MouseDownFunction;
    KeyPressFunctionHandler KeyPressFunction;
    char *Title;
    Task *Task;
    struct _TextBox *ActiveTextBox;
} Window;

// Creates a new Window
Window *NewWindow(int X, int Y, int Width, int Height, int Flags, char *Title, Context *Context);

// Initializes a new Window object
void WindowInit(Window *NewWindow, int X, int Y, int Width, int Height, int Flags, char *Title, Context *Context);

// Inserts a Child Window
void WindowInsertChild(Window *InputWindow, Window *Child);

// Raises the given Window to the top of the Desktop
void WindowRaise(Window *InputWindow);

// Draws a Window
void WindowPaint(Window *InputWindow, List *DirtyRegions, int InRecursion);

// Processes the Mouse on the Window
void WindowProcessMouse(Window *InputWindow, int MouseX, int MouseY, int MouseClick, int DragWindow);

// Processes a Key press
void WindowProcessKey(Window *InputWindow, char Key);

// Draws a border around the Window
static void WindowDrawBorder(Window *Window);

// The default paint method
static void WindowPaintHandler(Window *Window);

// The default Mouse Handler does nothing
static void WindowMouseDownHandler(Window *Window, int X, int Y);

// Returns the absolute X coordinate of the given Window
static int WindowScreenX(Window *Window);

// Returns the absolute Y coordinate of the given Window
static int WindowScreenY(Window *Window);

#endif