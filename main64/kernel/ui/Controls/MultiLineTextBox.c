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
	Button *scrollUpButton = NewButton(Width - SCROLL_BUTTON_WIDTH - 1, 1, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, Context);
    scrollUpButton->OnClick = ScrollUpButtonOnClick;
	WindowInsertChild((Window *)textbox, (Window *)scrollUpButton);

    // Create a new Button for scrolling down
	Button *scrollDownButton = NewButton(Width - SCROLL_BUTTON_WIDTH - 1, Height - SCROLL_BUTTON_HEIGHT - 1, SCROLL_BUTTON_WIDTH, SCROLL_BUTTON_HEIGHT, Context);
    scrollDownButton->OnClick = ScrollDownButtonOnClick;
	WindowInsertChild((Window *)textbox, (Window *)scrollDownButton);

    return textbox;
}

// Draws the MultiLineTextBox
void MultiLineTextBoxPaintHandler(Window *MultiLineTextBoxWindow)
{
    MultiLineTextBox *textbox = (MultiLineTextBox *)MultiLineTextBoxWindow;
    int i, y = 5;

    // White background & black border
    ContextFillRect(MultiLineTextBoxWindow->Context, 1, 1, MultiLineTextBoxWindow->Width - 2, MultiLineTextBoxWindow->Height - 2, 0xFFFF);
    ContextDrawRectangle(MultiLineTextBoxWindow->Context, 0, 0, MultiLineTextBoxWindow->Width, MultiLineTextBoxWindow->Height, 0x0000);

    // Draw a vertical line for the ScrollBar
    ContextDrawVerticalLine(MultiLineTextBoxWindow->Context, MultiLineTextBoxWindow->Width - SCROLL_BUTTON_WIDTH - 2, 0, MultiLineTextBoxWindow->Height, 0x0000);

    // Draw the various text lines
    for (i = 0; i < textbox->TextLines->Count; i++)
    {
        if (y <= textbox->Window.Height - LINE_HEIGHT)
        {
            DrawString(MultiLineTextBoxWindow->Context, GetNodeFromList(textbox->TextLines, i + textbox->Position), 5, y, 0x0000);
            y+= LINE_HEIGHT;
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
    int numberOfVisibleTextLines = 6; // TODO

    if (textbox->Position < textbox->TextLines->Count - numberOfVisibleTextLines)
        textbox->Position++;
}

// Handles the Mouse Down Event
void MultiLineTextBoxMouseDownHandler(Window *MultiLineTextBoxWindow, int X, int Y)
{
    MultiLineTextBox *textbox = (MultiLineTextBox *)MultiLineTextBoxWindow;
}