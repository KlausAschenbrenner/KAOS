//
//  Desktop.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "Desktop.h"
#include "../Heap/Heap.h"

// This array represents the definition of the Mouse Pointer Image
unsigned int MouseImage[MOUSE_BUFFER_SIZE] = 
{
    cX, c_, c_, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cX, c_, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cX, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cO, cX, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cO, cO, cX, c_, c_ ,c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cX, c_, c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cX, c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cX, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cX, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cO, cX, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cO, cO, cX,
    cX, cX, cX, cX, cO, cO, cO, cX, cX, cX, cX,
    c_, c_, c_, c_, cX, cO, cO, cX, c_, c_, c_,
    c_, c_, c_, c_, cX, cO, cO, cX, c_, c_, c_,
    c_, c_, c_, c_, c_, cX, cO, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, cX, cO, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, c_, cX, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, c_, c_, cX, cX, c_, c_ 
};

// Creates a new Desktop
Desktop *NewDesktop(Context *Context, int Color)
{
    // Create a new Desktop structure
    Desktop *desktop = malloc(sizeof(Desktop));
    WindowInit((Window *)desktop, 0, 0, Context->Width, Context->Height, WINDOW_NODECORATION, "", Context);
    desktop->Window.PaintFunction = DesktopPaintHandler;
    desktop->MouseX = 50;
    desktop->MouseY = 50;

    return desktop;
}

// Adds a new Window to the Desktop
Window *NewDesktopWindow(Window *InputWindow, int X, int Y, int Width, int Height, char *Title)
{
    // Create a new Window and add it to the Desktop
    Window *window = NewWindow(X, Y, Width, Height, 0x0, Title, InputWindow->Context);
    AddNodeToList(InputWindow->Children, (void *)window);
    window->Parent = InputWindow;

    // The newly added Window is the current Window
    InputWindow->ActiveChild = window;
    
    return window;
}

// Removes the Window from the Desktop and terminates the running Task in the Kernel
void RemoveDesktopWindow(Window *InputWindow)
{
    Window *window;
    int pid = 0;
    int i;

    // Iterate through all Windows on the Desktop
    // InputWindow->Parent: Reference to the Desktop
    for (i = InputWindow->Parent->Children->Count - 1; i >= 0; i--)
    {
        // Get the Window from the Desktop
        window = (Window *)GetNodeFromList(InputWindow->Parent->Children, i);

        // Check if the current Window is the Window to be closed
        if ((window != 0x0) && (window == InputWindow))
        {
            pid = window->Task->PID;
            RemoveNodeFromList(InputWindow->Parent->Children, i);
            break;
        }
    }

    // Terminate the Task
    if (pid != 0)
        TerminateTask(pid);
}

// Processes the mouse on the Desktop
void DesktopProcessMouse(Desktop *Desktop, int MouseX, int MouseY, int MouseClick, int DragWindow)
{
    // Capture the mouse location
    Desktop->MouseX = MouseX;
    Desktop->MouseY = MouseY;

    // Process the mouse
    WindowProcessMouse((Window *)Desktop, MouseX, MouseY, MouseClick, DragWindow);
}

// Processes a Key press
void DesktopProcessKey(Desktop *Desktop, char Key)
{
    WindowProcessKey((Window*)Desktop, Key);
}

// Draws the Mouse Pointer Image onto the Desktop
void MousePointerPaint(Desktop *Desktop)
{
    int x, y;

    for (y = 0; y < MOUSE_HEIGHT; y++)
    {
        for (x = 0; x < MOUSE_WIDTH; x++)
        {
            // Check if we have a transparent pixel
            if (MouseImage[y * MOUSE_WIDTH + x] != 0xDEAD)
                Desktop->Window.Context->FrameDoubleBuffer[(y + Desktop->MouseY) * Desktop->Window.Context->Width + (x + Desktop->MouseX)] = MouseImage[y * MOUSE_WIDTH + x];
        }
    }
}

// Draws the Desktop
static void DesktopPaintHandler(Window *DesktopWindow)
{
    // Fill the Desktop
    ContextFillRect(DesktopWindow->Context, 0, 0, DesktopWindow->Width, DesktopWindow->Height, 0x05FF);
    DrawString(DesktopWindow->Context, "KAOS x64", 10, 10, 0x0000);
    DrawString(DesktopWindow->Context, "(c) 2019 by Klaus Aschenbrenner", 10, 26, 0x0000);

    // Draw a calculated value on the Desktop
    int *value = (int *)0xFFFF800000700000;
    char str[32] = "";
    itoa(*value, 10, str);
    DrawString(DesktopWindow->Context, str, 10, 42, 0x0000);
}