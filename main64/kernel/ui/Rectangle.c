//
//  Rectangle.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "Rectangle.h"
#include "../Heap/Heap.h"

// Creates a new Rectangle
Rectangle *NewRectangle(int Left, int Top, int Right, int Bottom)
{
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    rect->Left = Left;
    rect->Top = Top;
    rect->Right = Right;
    rect->Bottom = Bottom;

    return rect;
}