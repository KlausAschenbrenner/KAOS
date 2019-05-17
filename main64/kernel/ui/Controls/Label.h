//
//  Label.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_Label_h
#define KAOS_Label_h

#include "../Window.h"

typedef struct _Label
{
    Window Window;
} Label;

// Creates a new Label
Label* NewLabel(int X, int Y);

void LabelPaintHandler(Window *LabelWindow);

void LabelMouseDownHandler(Window *LabelWindow, int X, int Y);

#endif