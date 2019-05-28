//
//  MultiLineTextBox.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 21.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "MultiLineTextBox.h"
#include "Button.h"
#include "../../drivers/keyboard.h"
#include "../../Heap/Heap.h"

// Creates a new MultiLineTextBox
MultiLineTextBox* NewMultiLineTextBox(int X, int Y, int Width, int Height, Context *Context)
{
    MultiLineTextBox *textbox = malloc(sizeof(MultiLineTextBox));
    WindowInit((Window *)textbox, X, Y, Width, Height, WINDOW_NODECORATION, "", Context);
    textbox->Window.PaintFunction = MultiLineTextBoxPaintHandler;
    textbox->Window.MouseDownFunction = MultiLineTextBoxMouseDownHandler;
    textbox->TextLines = NewList();
    textbox->Position = 0;

    // Create a new Button for scrolling up
	Button *scrollUpButton = NewButton(Width - MULTILINEBOX_SCROLL_BUTTON_WIDTH - 1, 1, MULTILINEBOX_SCROLL_BUTTON_WIDTH, MULTILINEBOX_SCROLL_BUTTON_HEIGHT, Context);
    scrollUpButton->OnClick = ScrollUpButtonOnClick;
	WindowInsertChild((Window *)textbox, (Window *)scrollUpButton);

    // Create a new Button for scrolling down
	Button *scrollDownButton = NewButton(Width - MULTILINEBOX_SCROLL_BUTTON_WIDTH - 1, Height - MULTILINEBOX_SCROLL_BUTTON_HEIGHT - 1, MULTILINEBOX_SCROLL_BUTTON_WIDTH, MULTILINEBOX_SCROLL_BUTTON_HEIGHT, Context);
    scrollDownButton->OnClick = ScrollDownButtonOnClick;
	WindowInsertChild((Window *)textbox, (Window *)scrollDownButton);

    return textbox;
}

// Draws the MultiLineTextBox
void MultiLineTextBoxPaintHandler(Window *MultiLineTextBoxWindow, Rectangle *DirtyRegion)
{
    MultiLineTextBox *textbox = (MultiLineTextBox *)MultiLineTextBoxWindow;
    int i, y = MULTILINEBOX_PADDING;

    // White background & black border
    ContextFillRect(MultiLineTextBoxWindow->Context, 1, 1, MultiLineTextBoxWindow->Width - 2, MultiLineTextBoxWindow->Height - 2, 0xFFFF, DirtyRegion);
    ContextDrawRectangle(MultiLineTextBoxWindow->Context, 0, 0, MultiLineTextBoxWindow->Width, MultiLineTextBoxWindow->Height, 0x0000, DirtyRegion);

    // Draw a vertical line for the ScrollBar
    ContextDrawVerticalLine(MultiLineTextBoxWindow->Context, MultiLineTextBoxWindow->Width - MULTILINEBOX_SCROLL_BUTTON_WIDTH - 2, 0, MultiLineTextBoxWindow->Height, 0x0000, DirtyRegion);

    // Draw the various text lines
    for (i = 0; i < textbox->TextLines->Count; i++)
    {
        if (y <= textbox->Window.Height - MULTILINEBOX_LINE_HEIGHT)
        {
            ContextDrawString(MultiLineTextBoxWindow->Context, GetNodeFromList(textbox->TextLines, i + textbox->Position), MULTILINEBOX_PADDING, y, 0x0000, DirtyRegion);
            y+= MULTILINEBOX_LINE_HEIGHT;
        }
    }
}

// Handles the OnClick event of the SrollUpButton
void ScrollUpButtonOnClick(Window *ButtonWindow, int X, int Y)
{
	MultiLineTextBox *textbox = (MultiLineTextBox *)ButtonWindow->Parent;

    if (textbox->Position > 0)
        textbox->Position--;
}

// Handles the OnClick event of the SrollDownButton
void ScrollDownButtonOnClick(Window *ButtonWindow, int X, int Y)
{
	MultiLineTextBox *textbox = (MultiLineTextBox *)ButtonWindow->Parent;
    int numberOfVisibleTextLines = (textbox->Window.Height - (2 * MULTILINEBOX_PADDING)) / MULTILINEBOX_LINE_HEIGHT;

    if (textbox->Position < textbox->TextLines->Count - numberOfVisibleTextLines)
        textbox->Position++;
}

// Handles the Mouse Down Event
void MultiLineTextBoxMouseDownHandler(Window *MultiLineTextBoxWindow, int X, int Y)
{
    MultiLineTextBox *textbox = (MultiLineTextBox *)MultiLineTextBoxWindow;
}