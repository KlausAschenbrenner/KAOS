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

#define SCROLL_BUTTON_WIDTH 20
#define SCROLL_BUTTON_HEIGHT 20
#define LINE_HEIGHT 15

typedef struct _MultiLineTextBox
{
    Window Window;
    List *TextLines;
    int Position;
} MultiLineTextBox;

// Creates a new MultiLineTextBox
MultiLineTextBox* NewMultiLineTextBox(int X, int Y, int Width, int Height, Context *Context);

// Draws the MultiLineTextBox
void MultiLineTextBoxPaintHandler(Window *MultiLineTextBoxWindow);

// Handles the OnClick event of the SrollUpButton
void ScrollUpButtonOnClick(Window *ButtonWindow, int X, int Y);

// Handles the OnClick event of the SrollDownButton
void ScrollDownButtonOnClick(Window *ButtonWindow, int X, int Y);

#endif