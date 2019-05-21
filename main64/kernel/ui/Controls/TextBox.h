//
//  TextBox.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_TextBox_h
#define KAOS_TextBox_h

#include "../Window.h"

typedef struct _TextBox
{
    Window Window;
    int HasFocus;
    char Text[100];
    int Pos;
} TextBox;

// Creates a new TextBox
TextBox* NewTextBox(int X, int Y, int Width, int Height, Context *Context);

// Draws the TextBox
void TextBoxPaintHandler(Window *TextBoxWindow);

// Handles the Mouse Down Event
void TextBoxMouseDownHandler(Window *TextBoxWindow, int X, int Y);

// Handles the Key Press Event
void TextBoxKeyPressHandler(Window *TextBoxWindow, char Key);

#endif