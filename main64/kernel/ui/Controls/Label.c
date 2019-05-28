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
#include "../../Heap/Heap.h"
#include "../../drivers/common.h"

// Creates a new Label
Label* NewLabel(int X, int Y, char *Title, Context *Context)
{
    Label *label = malloc(sizeof(Label));
    WindowInit((Window *)label, X, Y, strlen(Title) * FONT_WIDTH, FONT_HEIGHT, WINDOW_NODECORATION, Title, Context);
    label->Window.PaintFunction = LabelPaintHandler;
    label->Window.MouseDownFunction = LabelMouseDownHandler;

    return label;
}

void LabelPaintHandler(Window *LabelWindow, Rectangle *DirtyRegion)
{
    Label *label = (Label *)LabelWindow;

    // Draw the Label
    ContextDrawString(LabelWindow->Context, LabelWindow->Title, LabelWindow->X, LabelWindow->Y + WINDOW_TITLEHEIGHT, WINDOW_BORDERCOLOR, DirtyRegion);
}

void LabelMouseDownHandler(Window *LabelWindow, int X, int Y)
{
}

// Sets the title of the Label
void LabelSetTitle(Label *InputLabel, char *Title)
{
    InputLabel->Window.Title = Title;
    InputLabel->Window.Width = strlen(Title) * FONT_WIDTH;
}