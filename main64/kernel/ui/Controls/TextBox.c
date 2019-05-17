//
//  TextBox.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "TextBox.h"

// Creates a new TextBox
TextBox* NewTextBox(int X, int Y, int Width, int Height)
{
    TextBox *textbox = malloc(sizeof(TextBox));
    WindowInit((Window *)textbox, X, Y, Width, Height, WINDOW_NODECORATION, "", (Context *)0x0);
    textbox->Window.PaintFunction = TextBoxPaintHandler;
    
    return textbox;
}

// Draws the TextBox
void TextBoxPaintHandler(Window *TextBoxWindow)
{
    int titleLen = strlen(TextBoxWindow->Title) * 8;

    // White background
    ContextFillRect(TextBoxWindow->Context, 1, 1, TextBoxWindow->Width - 2, TextBoxWindow->Height - 2, 0xFFFF);

    // Black border
    ContextDrawRectangle(TextBoxWindow->Context, 0, 0, TextBoxWindow->Width, TextBoxWindow->Height, 0x0000);
    
    // Draw the title
    if (TextBoxWindow->Title)
        DrawString(TextBoxWindow->Context, TextBoxWindow->Title, 6, (TextBoxWindow->Height / 2) - 6, 0x0000);
}   