//
//  Button.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_Button_h
#define KAOS_Button_h

#include "../Window.h"

typedef void (*ButtonMouseDownFunctionHandler)(struct _Button*, int, int);

typedef struct _Button
{
    Window Window;
    int ColorToggle;
    ButtonMouseDownFunctionHandler OnClick;
} Button;

// Creates a new Button
Button* NewButton(int X, int Y, int Width, int Height);

// Draws the Button
void ButtonPaintHandler(Window *ButtonWindow);

// Handles the Mouse Down Event
void ButtonMouseDownHandler(Window *ButtonWindow, int X, int Y);

#endif