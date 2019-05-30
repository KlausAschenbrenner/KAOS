//
//  Button.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 28.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_Bitmap_h
#define KAOS_Bitmap_h

#include "../Window.h"

// Represents the Bitmap Header
typedef struct _BitmapHeader
{
    unsigned char Type[2];
    unsigned int Size;
    unsigned short Reserved1;
    unsigned short Reserved2;
    unsigned int StartingAddress;
} __attribute__((packed)) BitmapHeader;

// Represents the Bitmap Info Header
typedef struct _BitmapInfoHeader
{
    unsigned int Size;
    signed int Width;
    signed int Height;
    unsigned short ColorPlanes;
    unsigned short BitsPerPixel;
    unsigned int CompressionMethod;
} __attribute__((packed)) BitmapInfoHeader;

// Represents the Bitmap
typedef struct _Bitmap
{
    Window Window;
    unsigned int Width;
    unsigned int Height;
    int UseTransparentPixel;
    unsigned short TransparentPixel;
    char *ImageBytes;
} Bitmap;

// Creates a new Bitmap
Bitmap *NewBitmap(char *FileName, int X, int Y, int UseTransparentPixel, unsigned short TransparentPixel, Context *Context);

// Draws the Bitmap
void BitmapPaintHandler(Window *BitmapWindow, Rectangle *DirtyRegion);

// Reads a Bitmap file from the File System
Bitmap *ReadBitmap(char *FileName);

#endif