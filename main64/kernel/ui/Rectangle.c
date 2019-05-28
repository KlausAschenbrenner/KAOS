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
Rectangle *NewRectange(int Top, int Left, int Bottom, int Right)
{
    Rectangle *rect = (Rectangle *)malloc(sizeof(Rectangle));
    rect->Top = Top;
    rect->Left = Left;
    rect->Bottom = Bottom;
    rect->Right = Right;

    return rect;
}