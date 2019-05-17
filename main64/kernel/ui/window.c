//
//  Window.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "../heap/Heap.h"
#include "Window.h"
#include "Rectangle.h"
#include "Desktop.h"

// Creates a new Window
Window *NewWindow(int X, int Y, int Width, int Height, int Flags, char *Title, Context *Context)
{
    // Create a new Window structure
    Window *window = malloc(sizeof(Window));
    WindowInit(window, X, Y, Width, Height, Flags, Title, Context);

    // Return the newly created Window
    return window;
}

// Initializes a new Window object
void WindowInit(Window *NewWindow, int X, int Y, int Width, int Height, int Flags, char *Title, Context *Context)
{
    NewWindow->Children = NewList();
    NewWindow->X = X;
    NewWindow->Y = Y;
    NewWindow->Width = Width;
    NewWindow->Height = Height;
    NewWindow->Context = Context;
    NewWindow->Flags = Flags;
    NewWindow->Title = Title;
    NewWindow->Parent = (Window *)0x0;
    NewWindow->LastMouseButtonState = 0;
    NewWindow->PaintFunction = WindowPaintHandler;
    NewWindow->DraggedChild = (Window *)0x0;
    NewWindow->ActiveChild = (Window *)0x0;
    NewWindow->DragOffsetX = 0;
    NewWindow->DragOffsetY = 0;
    NewWindow->MouseDownFunction = WindowMouseDownHandler;
}

// Inserts a Child Window
void WindowInsertChild(Window *InputWindow, Window *Child)
{
    Child->Parent = InputWindow;
    Child->Context = InputWindow->Context;

    AddNodeToList(InputWindow->Children, Child);
}

// Raises the given Window to the top of the Desktop
void WindowRaise(Window *InputWindow)
{
    Window *parent, *lastActive;
    int i;

    // We don't have a parent, we don't have children
    if (!InputWindow->Parent)
        return;

    // You can't raise the window that is currently active
    parent = InputWindow->Parent;

    if (parent->ActiveChild == InputWindow)
        return;

    // Get a reference to the active window we are replacing
    lastActive = parent->ActiveChild;

    // Find the window
    for (i = 0; i < parent->Children->Count; i++)
    {
        if ((Window *)GetNodeFromList(parent->Children, i) == InputWindow)
            break;
    }

    // Add the window to the top of the list
    RemoveNodeFromList(parent->Children, i);
    AddNodeToList(parent->Children, (void *)InputWindow);
    parent->ActiveChild = InputWindow;
}

// Draws a Window
void WindowPaint(Window *InputWindow, List *DirtyRegions, int InRecursion)
{
    int i, j, screenX, screenY, childScreenX, childScreenY;
    Window *currentChild;
    Rectangle *tempRectangle;

    screenX = WindowScreenX(InputWindow);
    screenY = WindowScreenY(InputWindow);

    if (!(InputWindow->Flags & WINDOW_NODECORATION))
    {
        // Draw the border
        WindowDrawBorder(InputWindow);
        screenX += WINDOW_BORDERWIDTH;
        screenY += WINDOW_TITLEHEIGHT;
    }

    // Draw the window
    InputWindow->Context->TranslateX = screenX;
    InputWindow->Context->TranslateY = screenY;
    InputWindow->PaintFunction(InputWindow);

    InputWindow->Context->TranslateX = 0;
    InputWindow->Context->TranslateY = 0;

    // Draw all child windows
    /* for (i = 0; i < InputWindow->Children->Count; i++)
    {
        currentChild = (Window *)GetNodeFromList(InputWindow->Children, i);
        WindowPaint(currentChild, 1);
    } */

    // Draw all child windows
    for (i = 0; i < InputWindow->Children->Count; i++)
    {
        currentChild = (Window *)GetNodeFromList(InputWindow->Children, i);

        if (DirtyRegions)
        {
            // Iterate over all dirty regions
            for (j = 0; j < DirtyRegions->Count; j++)
            {
                // Get the Rectangle of the dirty region
                tempRectangle = (Rectangle *)GetNodeFromList(DirtyRegions, j);
                screenX = WindowScreenX(currentChild);
                screenY = WindowScreenY(currentChild);

                // Check if the current Window intersects with a dirty region
                if (tempRectangle->Left <= (screenX + currentChild->Width - 1) &&
                    tempRectangle->Right >= screenX &&
                    tempRectangle->Top <= (screenY + currentChild->Height - 1) &&
                    tempRectangle->Bottom >= screenY)
                {
                    break;
                }

                if (j == DirtyRegions->Count)
                    continue;
            }
        }

        WindowPaint(currentChild, DirtyRegions, 1);
    }
    
    // And finally we paint the Mouse Pointer, and copy the Frame Double Buffer to the VGA Buffer
    if (!InRecursion)
    {
        MousePointerPaint((Desktop *)InputWindow);
        memcpy(InputWindow->Context->VgaFrameBuffer, InputWindow->Context->FrameDoubleBuffer, (InputWindow->Context->Width * InputWindow->Context->Height * WINDOW_BPP / 8) - 1);
    }
}

// Invalidates the given region of the Window and repaints it
void WindowInvalidate(Window *Window, int Top, int Left, int Bottom, int Right)
{
    List *dirtyRegions;
    Rectangle *dirtyRectangle;

    int originX = WindowScreenX(Window);
    int originY = WindowScreenY(Window);
    Top += originY;
    Bottom += originY;
    Left += originX;
    Right += originX;

    // Repaint the dirty region
    dirtyRegions = NewList();
    dirtyRectangle = NewRectange(Top, Left, Bottom, Right);
    AddNodeToList(dirtyRegions, dirtyRectangle);
    WindowPaint(Window, dirtyRegions, 0);
}

// Processes the Mouse on the Desktop
void WindowProcessMouse(Window *InputWindow, int MouseX, int MouseY, int MouseClick, int DragWindow)
{
    int i, innerX1, innerY1, innerX2, innerY2;
    Window *child;

    // Iterate through all Windows backwards
    for (i = InputWindow->Children->Count - 1; i >= 0; i--)
    {
        // Get a reference to the Window
        child = (Window *)GetNodeFromList(InputWindow->Children, i);

        // Check if the Mouse was not within the current Window
        if (!(MouseX >= child->X && MouseX < (child->X + child->Width) &&
            MouseY >= child->Y && MouseY < (child->Y + child->Height)))
        {
            continue;
        }    

        if (MouseClick && !InputWindow->LastMouseButtonState)
        {
            // Raise the Window to the top of the Desktop
            WindowRaise(child);

            // Check if the mouse pointer is within the titlebar
            if (!(child->Flags & WINDOW_NODECORATION) && MouseY >= child->Y && MouseY < (child->Y + WINDOW_TITLEHEIGHT))
            {
                InputWindow->DragOffsetX = MouseX - child->X;
                InputWindow->DragOffsetY = MouseY - child->Y;
                InputWindow->DraggedChild = child;

                break;
            }
        }

        // Forward the mouse event to the child window
        WindowProcessMouse(child, MouseX - child->X, MouseY - child->Y, MouseClick, DragWindow);
        break;
    }

    if (!MouseClick)
        InputWindow->DraggedChild = (Window *)0x0;

    if (InputWindow->DraggedChild != 0x0)
    {
        // Move the Window to the new position
        InputWindow->DraggedChild->X = MouseX - InputWindow->DragOffsetX;
        InputWindow->DraggedChild->Y = MouseY - InputWindow->DragOffsetY;
    }

    // Call the Mouse Down Function Handler
    if (InputWindow->MouseDownFunction && MouseClick && InputWindow->LastMouseButtonState)
        InputWindow->MouseDownFunction(InputWindow, MouseX, MouseY);

    InputWindow->LastMouseButtonState = MouseClick;
}

// Adds additional characters to the Window Title
void WindowAppendTitle(Window *Window, char *AdditionalChars)
{
    char *newString;
    int originalLength, additionalLength, i;

    originalLength = strlen(Window->Title);
    additionalLength = strlen(AdditionalChars);

    newString = (char *)malloc(sizeof(char) * (originalLength + additionalLength + 1));

    // Copy the original string to the new string
    for (i = 0; Window->Title[i]; i++)
        newString[i] = Window->Title[i];

    // Add the additional characters to the new string
    for (i = 0; AdditionalChars[i]; i++)
        newString[originalLength + i] = AdditionalChars[i];

    // Null terminate the new string
    newString[originalLength + i] = 0;

    // Set the new Window title
    Window->Title = newString;
}

// Draws a border around the Window
static void WindowDrawBorder(Window *Window)
{
    int i;
    int screenX = WindowScreenX(Window);
    int screenY = WindowScreenY(Window);

    ContextDrawRectangle(Window->Context, screenX, screenY, Window->Width, Window->Height, WINDOW_BORDERCOLOR);
    ContextDrawRectangle(Window->Context, screenX + 1, screenY + 1, Window->Width - 2, Window->Height - 2, WINDOW_BORDERCOLOR);
    ContextDrawRectangle(Window->Context, screenX + 2, screenY + 2, Window->Width - 4, Window->Height - 4, WINDOW_BORDERCOLOR);

    // Draw a border line under the titlebar
    for (i = 0; i < WINDOW_BORDERWIDTH; i++)
    {
        ContextDrawHorizontalLine(Window->Context, screenX + WINDOW_BORDERWIDTH, screenY + i + WINDOW_TITLEHEIGHT - WINDOW_BORDERWIDTH, Window->Width - (2 * WINDOW_BORDERWIDTH), WINDOW_BORDERCOLOR);
    }

    // Fill the titlebar background
    ContextFillRect(Window->Context, screenX + WINDOW_BORDERWIDTH, screenY + WINDOW_BORDERWIDTH, Window->Width - 6, 25,
        Window->Parent->ActiveChild == Window ? WINDOW_TITLE_COLOR_ACTIVE : WINDOW_TITLE_COLOR_INACTIVE);
}

// The default paint method
static void WindowPaintHandler(Window *Window)
{
    char str[32] = "";

    // Fill the Window Background
    ContextFillRect(Window->Context, 0, 0, Window->Width - 6, Window->Height - 34, WINDOW_BACKGROUND_COLOR);

    // Draw the Window Title
    DrawString(Window->Context, Window->Title, 10, -21, 0xFFFF);
}

// The default Mouse Handler does nothing
static void WindowMouseDownHandler(Window *Window, int X, int Y)
{
    return;
}

// Returns the absolute X coordinate of the given Window
static int WindowScreenX(Window *Window)
{
    if (Window->Parent)
        return Window->X + WindowScreenX(Window->Parent);

    return Window->X;
}

// Returns the absolute Y coordinate of the given Window
static int WindowScreenY(Window *Window)
{
    if (Window->Parent)
        return Window->Y + WindowScreenY(Window->Parent);

    return Window->Y;
}