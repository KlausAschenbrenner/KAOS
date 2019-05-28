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
Label* NewLabel(int X, int Y, char *Title, Context *Context);

void LabelPaintHandler(Window *LabelWindow, Rectangle *DirtyRegion);

void LabelMouseDownHandler(Window *LabelWindow, int X, int Y);

// Sets the title of the Label
void LabelSetTitle(Label *InputLabel, char *Title);

#endif