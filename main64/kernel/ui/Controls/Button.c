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
#include "Bitmap.h"
#include "../../Heap/Heap.h"

// Creates a new Button
Button* NewButton(int X, int Y, int Width, int Height, char *Title, char *BitmapFile, int BitmapFileX, int BitmapFileY, int UseTransparentPixel, unsigned short TransparentPixel, Context *Context)
{
    Button *button = malloc(sizeof(Button));
    WindowInit((Window *)button, X, Y, Width, Height, WINDOW_NODECORATION, Title, Context);
    button->Window.PaintFunction = ButtonPaintHandler;
    button->Window.LeftMouseButtonDownFunction = LeftMouseButtonDownHandler;
    button->Window.LeftMouseButtonUpFunction = LeftMouseButtonUpHandler;
    button->IsPressed = 0;
    
    // Check if we should display a Bitmap on the Button
    if (strcmp(BitmapFile, "", 0) != 0)
    {
        Bitmap *bitmap = NewBitmap(BitmapFile, BitmapFileX, BitmapFileY, UseTransparentPixel, TransparentPixel, Context);
        WindowInsertChild((Window *)button, (Window *)bitmap);
    }

    return button;
}

// Draws the Button
void ButtonPaintHandler(Window *ButtonWindow, Rectangle *DirtyRegion)
{
    Button *button = (Button *)ButtonWindow;
    int borderColor = WINDOW_TITLE_COLOR_INACTIVE;

    // Change the Button appearance according to its pressed state
    if (button->IsPressed)
        borderColor = WINDOW_TITLE_COLOR_ACTIVE;

    ContextFillRect(ButtonWindow->Context, 1, 1, ButtonWindow->Width - 1, ButtonWindow->Height - 1, WINDOW_TITLE_COLOR_INACTIVE, DirtyRegion);
    ContextDrawRectangle(ButtonWindow->Context, 0, 0, ButtonWindow->Width, ButtonWindow->Height, 0xCEE0, DirtyRegion);

    ContextDrawRectangle(ButtonWindow->Context, 3, 3, ButtonWindow->Width - 6, ButtonWindow->Height - 6, borderColor, DirtyRegion);
    ContextDrawRectangle(ButtonWindow->Context, 4, 4, ButtonWindow->Width - 8, ButtonWindow->Height - 8, borderColor, DirtyRegion);

    // Draw the Button Label
    ContextDrawString(ButtonWindow->Context, ButtonWindow->Title, 10, 10, WINDOW_BORDERCOLOR, DirtyRegion);
}

// Handles the Left Mouse Down Event
void LeftMouseButtonDownHandler(Window *ButtonWindow, int X, int Y)
{
    Button *button = (Button *)ButtonWindow;
    button->IsPressed = 1;
}

// Handles the Left Mouse Button Up Event
void LeftMouseButtonUpHandler(Window *ButtonWindow, int X, int Y)
{
    Button *button = (Button *)ButtonWindow;
    button->IsPressed = 0;

    // Call the OnClick function
    if (button->OnClick)
        button->OnClick(button, X, Y);
}