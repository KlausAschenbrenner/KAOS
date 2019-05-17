//
//  Label.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "Label.h"

// Creates a new Label
Label* NewLabel(int X, int Y)
{
    Label *label = malloc(sizeof(Label));
    WindowInit((Window *)label, X, Y, 0, 0, WINDOW_NODECORATION, "", (Context *)0x0);
    label->Window.PaintFunction = LabelPaintHandler;
    label->Window.MouseDownFunction = LabelMouseDownHandler;

    return label;
}

void LabelPaintHandler(Window *LabelWindow)
{
    Label *label = (Label *)LabelWindow;

    // Draw the Label
    DrawString(LabelWindow->Context, LabelWindow->Title, LabelWindow->X, LabelWindow->Y + WINDOW_TITLEHEIGHT, WINDOW_BORDERCOLOR);
}

void LabelMouseDownHandler(Window *LabelWindow, int X, int Y)
{
}