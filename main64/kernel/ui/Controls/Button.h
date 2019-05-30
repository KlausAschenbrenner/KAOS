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
Button* NewButton(int X, int Y, int Width, int Height, char *Title, char *BitmapFile, int BitmapFileX, int BitmapFileY, int UseTransparentPixel, unsigned short TransparentPixel, Context *Context);

// Draws the Button
void ButtonPaintHandler(Window *ButtonWindow, Rectangle *DirtyRegion);

// Handles the Mouse Down Event
void ButtonMouseDownHandler(Window *ButtonWindow, int X, int Y);

#endif