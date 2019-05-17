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
} TextBox;

// Creates a new TextBox
TextBox* NewTextBox(int X, int Y, int Width, int Height);

// Draws the TextBox
void TextBoxPaintHandler(Window *TextBoxWindow);

#endif