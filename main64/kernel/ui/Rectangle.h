//
//  Rectangle.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 16.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#ifndef KAOS_Rectangle_h
#define KAOS_Rectangle_h

// Defines a simple Rectangle
typedef struct _Rectangle
{
    int Top;
    int Left;
    int Bottom;
    int Right;
} Rectangle;

// Creates a new Rectangle
Rectangle *NewRectange(int Top, int Left, int Bottom, int Right);

#endif