//
//  Button.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "Button.h"
#include "../../Heap/Heap.h"

// Creates a new Button
Button* NewButton(int X, int Y, int Width, int Height, Context *Context)
{
    Button *button = malloc(sizeof(Button));
    WindowInit((Window *)button, X, Y, Width, Height, WINDOW_NODECORATION, "", Context);
    button->Window.PaintFunction = ButtonPaintHandler;
    button->Window.MouseDownFunction = ButtonMouseDownHandler;
    button->ColorToggle = 0;

    return button;
}

// Draws the Button
void ButtonPaintHandler(Window *ButtonWindow, Rectangle *DirtyRegion)
{
    Button *button = (Button *)ButtonWindow;
    int borderColor = WINDOW_TITLE_COLOR_INACTIVE;

    /* if (button->ColorToggle)
        borderColor = WINDOW_TITLE_COLOR_ACTIVE;
    else
        borderColor = WINDOW_TITLE_COLOR_INACTIVE; */

    ContextFillRect(ButtonWindow->Context, 1, 1, ButtonWindow->Width - 1, ButtonWindow->Height - 1, WINDOW_TITLE_COLOR_INACTIVE, DirtyRegion);
    ContextDrawRectangle(ButtonWindow->Context, 0, 0, ButtonWindow->Width, ButtonWindow->Height, 0xCEE0, DirtyRegion);

    ContextDrawRectangle(ButtonWindow->Context, 3, 3, ButtonWindow->Width - 6, ButtonWindow->Height - 6, borderColor, DirtyRegion);
    ContextDrawRectangle(ButtonWindow->Context, 4, 4, ButtonWindow->Width - 8, ButtonWindow->Height - 8, borderColor, DirtyRegion);

    // Draw the Button Label
    ContextDrawString(ButtonWindow->Context, ButtonWindow->Title, 10, 10, WINDOW_BORDERCOLOR, DirtyRegion);
}

// Handles the Mouse Down Event
void ButtonMouseDownHandler(Window *ButtonWindow, int X, int Y)
{
    Button *button = (Button *)ButtonWindow;
    button->ColorToggle = !button->ColorToggle;

    // Call the OnClick function
    if (button->OnClick)
        button->OnClick(button, X, Y);
}