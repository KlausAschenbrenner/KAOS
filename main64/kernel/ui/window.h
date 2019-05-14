//
//  window.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "../Tasks/Task.h"

#ifndef KAOS_window_h
#define KAOS_window_h

// Virtual and physical memory adresess
#define WINDOW_FRAME_BUFFER 0xFFFF8000E8000000
#define WINDOW_DOUBLE_BUFFER 0xFFFF800008000000
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

// Mouse properties
#define MOUSE_WIDTH 11
#define MOUSE_HEIGHT 18
#define MOUSE_BUFFER_SIZE (MOUSE_WIDTH * MOUSE_HEIGHT)
#define cX 0x0000   // A black pixel for the Mouse Pointer
#define cO 0xFFFF   // A white pixel for the Mouse Pointer
#define c_ 0xDEAD   // The transparent pixel for the Mouse Pointer

// Font properties
#define FONT_WIDTH 8
#define FONT_HEIGHT 12
#define FONT_CHARACTERS 128

// Defines a Node in a Double Linked List
typedef struct _ListNode
{
    void *Payload;
    struct _List *Previous;
    struct _List *Next;
} ListNode;

// Defines a simple Doube Linked List
typedef struct _List
{
    int Count;
    ListNode *RootNode;
} List;

typedef struct _Context
{
    unsigned short *FrameDoubleBuffer;
    unsigned short *VgaFrameBuffer;
    int Width;
    int Height;
} Context;

// Defines a Window
typedef struct _Window
{
    int X;
    int Y;
    int Width;
    int Height;
    Context *Context;
    char *Title;
    Task *Task;
} Window;

// Defines the Desktop
typedef struct _Desktop
{
    List *Children;
    Context *Context;
    int Color;
    int MouseX;
    int MouseY;
    int LastMouseButtonState;
    Window *DraggedChild;
    int DragOffsetX;
    int DragOffsetY;
} Desktop;

typedef struct _Rectangle
{
    int Top;
    int Left;
    int Bottom;
    int Right;
} Rectangle;

// Creates a new Window
Window *NewWindow(int X, int Y, int Width, int Height, Context *Context, char *Title);

// Draws a filled Rectangle
void Context_FillRect(Context *Context, int X, int Y, unsigned int Width, unsigned int Height, int Color);

// Draws a Window
void WindowPaint(Window *Window);

// Creates a new List
List *NewList();

// Creates a new ListNode
ListNode *NewListNode(void *Payload);

// Adds a new Node to the given List
void AddNodeToList(List *List, void *Payload);

// Removes a Node from the given List
void *RemoveNodeFromList(List *List, int Index);

// Returns a Node from the given List
void *GetNodeFromList(List *List, int Index);

// Creates a new Desktop
Desktop *NewDesktop(Context *Context, int Color);

// Adds a new Window to the Desktop
Window *NewDesktopWindow(Desktop *Desktop, int X, int Y, int Width, int Height, char *Title);

// Draws the Desktop
void DesktopPaint(Desktop *Desktop);

// Processes the Mouse on the Desktop
void DesktopProcessMouse(Desktop *Desktop, int MouseX, int MouseY, int MouseClick, int DragWindow);

// Gets a list of windows overlapping the passed in window
List *DesktopGetWindowsAbove(Desktop *Desktop, Window *InputWindow);

// Creates a new Rectangle
Rectangle *NewRectange(int Top, int Left, int Bottom, int Right);

// Splits the 2 given Rectangles
List *RectangleSplit(Rectangle *SubjectRectangle, Rectangle *CuttingRectangle);

// Creates a new Context
Context *NewContext(int Width, int Height, unsigned char *FrameDoubleBuffer, unsigned char *VgaFrameBuffer);

// Adds a new clipped Rectangle to the Context
void ContextAddClipRectangle(Context *Context, Rectangle *AddedRectangle);

void ContextSubtractClipRectangle(Context *Context, Rectangle *SubtractedRectangle);

// Clears the clipped Rectangles from the Context
void ContextClearClipRectangle(Context *Context);

// Draws a Rectangle
void ContextDrawRectangle(Context *Context, int X, int Y, int Width, int Height, int Color);

// Draws a horizontal line
void ContextDrawHorizontalLine(Context *Context, int X, int Y, int Length, int Color);

// Draws a vertical line
void ContextDrawVerticalLine(Context *Context, int X, int Y, int Length, int Color);

// Draws a single Character
static void DrawCharacter(Context *Context, char Character, int X, int Y, int Color);

// Draws a null-terminated String at the given location
void DrawString(Context *Context, char *String, int X, int Y, int Color);

#endif