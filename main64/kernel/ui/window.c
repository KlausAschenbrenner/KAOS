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
#include "Controls/Button.h"

// Creates a new Window
Window *NewWindow(int X, int Y, int Width, int Height, int Flags, char *Title, Context *Context)
{
    // Create a new Window structure
    Window *window = malloc(sizeof(Window));
    WindowInit(window, X, Y, Width, Height, Flags, Title, Context);

    // Add a Close Button to the TitleBar
    Button *closeButton = NewButton(Width - WINDOW_CLOSE_BUTTON_WIDTH - WINDOW_BORDERWIDTH, WINDOW_BORDERWIDTH, WINDOW_CLOSE_BUTTON_WIDTH, WINDOW_CLOSE_BUTTON_HEIGHT - (2 * WINDOW_BORDERWIDTH), Context);
    closeButton->Window.Title = "X";
    closeButton->OnClick = CloseButtonOnClick;
    WindowInsertChild(window, (Window *)closeButton);

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
    NewWindow->ActiveTextBox = 0x0;
}

// Inserts a Child Window
void WindowInsertChild(Window *InputWindow, Window *Child)
{
    Child->Parent = InputWindow;
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

    for (i = 0; i < InputWindow->Children->Count; i++)
    {
        currentChild = (Window *)GetNodeFromList(InputWindow->Children, i);
        WindowPaint(currentChild, DirtyRegions, 1);
    }
    
    // And finally we paint the Mouse Pointer, and copy the Frame Double Buffer to the VGA Buffer
    if (!InRecursion)
    {
        MousePointerPaint((Desktop *)InputWindow);
        memcpy(InputWindow->Context->VgaFrameBuffer, InputWindow->Context->FrameDoubleBuffer, (InputWindow->Context->Width * InputWindow->Context->Height * WINDOW_BPP / 8) - 1);
    }
}

// Processes the Mouse on the Desktop
void WindowProcessMouse(Window *InputWindow, int MouseX, int MouseY, int MouseClick, int DragWindow)
{
    Window *child;
    int i;

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

// Processes a Key press
void WindowProcessKey(Window *InputWindow, char Key)
{
    Window *child;
    int i;

    // Iterate through all Windows backwards
    for (i = InputWindow->Children->Count - 1; i >= 0; i--)
    {
        // Get a reference to the Window
        child = (Window *)GetNodeFromList(InputWindow->Children, i);
        
        // Forward the Key Press event to the child window
        WindowProcessKey(child, Key);
    }

    // Call the Key Press Function Handler
    if (InputWindow->KeyPressFunction)
        InputWindow->KeyPressFunction(InputWindow, Key);
}

// Handles the OnClick event of the CloseButton
void CloseButtonOnClick(Window *CloseButton, int X, int Y)
{
    RemoveDesktopWindow(CloseButton->Parent);
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