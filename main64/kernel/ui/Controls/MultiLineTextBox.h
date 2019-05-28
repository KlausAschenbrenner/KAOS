//
//  MultiLineTextBox.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 21.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_MultiLineTextBox_h
#define KAOS_MultiLineTextBox_h

#include "../Window.h"

#define MULTILINEBOX_SCROLL_BUTTON_WIDTH 20
#define MULTILINEBOX_SCROLL_BUTTON_HEIGHT 20
#define MULTILINEBOX_LINE_HEIGHT 15
#define MULTILINEBOX_PADDING 5

typedef struct _MultiLineTextBox
{
    Window Window;
    List *TextLines;
    int Position;
} MultiLineTextBox;

// Creates a new MultiLineTextBox
MultiLineTextBox* NewMultiLineTextBox(int X, int Y, int Width, int Height, Context *Context);

// Draws the MultiLineTextBox
void MultiLineTextBoxPaintHandler(Window *MultiLineTextBoxWindow, Rectangle *DirtyRegion);

// Handles the OnClick event of the SrollUpButton
void ScrollUpButtonOnClick(Window *ButtonWindow, int X, int Y);

// Handles the OnClick event of the SrollDownButton
void ScrollDownButtonOnClick(Window *ButtonWindow, int X, int Y);

// Handles the Mouse Down Event
void MultiLineTextBoxMouseDownHandler(Window *MultiLineTextBoxWindow, int X, int Y);

#endif