//
//  Bitmap.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 29.05.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "../Context.h"
#include "Bitmap.h"
#include "../../drivers/screen.h"
#include "../../fat12/fat12.h"
#include "../../Heap/Heap.h"

// Creates a new Bitmap
Bitmap *NewBitmap(char *FileName, int X, int Y, int UseTransparentPixel, unsigned short TransparentPixel, Context *Context)
{
    Bitmap *bitmap = ReadBitmap(FileName);
    
    WindowInit((Window *)bitmap, X, Y, bitmap->Width, bitmap->Height, WINDOW_NODECORATION, "", Context);
    bitmap->Window.PaintFunction = BitmapPaintHandler;
    bitmap->UseTransparentPixel = UseTransparentPixel;
    bitmap->TransparentPixel = TransparentPixel;

    return bitmap;
}

// Draws the Bitmap
void BitmapPaintHandler(Window *BitmapWindow, Rectangle *DirtyRegion)
{
    Bitmap *bitmap = (Bitmap *)BitmapWindow;
    int x, y, z;

    for (y = 0; y < bitmap->Height; y++)
    {
        unsigned char *imageRow = bitmap->ImageBytes + (y * bitmap->Width * 4);

        z = 0;

        for (x = 0; x < bitmap->Width; x++)
        {
            // Read the RGB color encoded pixel
            unsigned char red = imageRow[z++];
            unsigned char green = imageRow[z++];
            unsigned char blue =  imageRow[z++];

            // Skip the alpha byte
            z++;
            
            // Convert the pixel data to RGB565
            // See https://stackoverflow.com/questions/22937080/32bit-rgba-to-16bit-bgr565-conversion 
            unsigned short color = red >> 3;
            color |= (green & 0xFC) << 3;
            color |= (blue & 0xF8) << 8;

            // Draw the pixel, if it's not a transparent one (if needed)
            if (bitmap->UseTransparentPixel)
            {
                if (color != bitmap->TransparentPixel)
                    ContextFillRect(BitmapWindow->Context, x + BitmapWindow->X, y + BitmapWindow->Y, 1, 1, color, DirtyRegion);
            }
            else
                ContextFillRect(BitmapWindow->Context, x + BitmapWindow->X, y + BitmapWindow->Y, 1, 1, color, DirtyRegion);
        }
    }
}

// Reads a Bitmap file from the File System
Bitmap *ReadBitmap(char *FileName)
{
	BitmapHeader *header = (BitmapHeader *)ReadFile(FileName);
    BitmapInfoHeader *infoHeader = (void *)header + sizeof(BitmapHeader);

    if (infoHeader->Height < 0)
        infoHeader->Height = infoHeader->Height * -1;

    // Initialize the Bitmap
    Bitmap *bitmap = malloc(sizeof(Bitmap));
    bitmap->Width = infoHeader->Width;
    bitmap->Height = infoHeader->Height;
    bitmap->ImageBytes = (void *)((unsigned long)header + header->StartingAddress);

    print_char(header->Type[0]);
	print_char(header->Type[1]);
	printf("\n");

    printf_int(header->Size, 10);
	printf("\n");

	printf_int(header->StartingAddress, 10);
	printf("\n");

    printf("infoHeader->Size: ");
    printf_int(infoHeader->Size, 10);
    printf("\n");

    printf("infoHeader->Width: ");
    printf_int(infoHeader->Width, 10);
    printf("\n");

    printf("infoHeader->Height: ");
    printf_int(infoHeader->Height, 10);
    printf("\n");

    printf("infoHeader->ColorPlanes: ");
    printf_int(infoHeader->ColorPlanes, 10);
    printf("\n");

    printf("infoHeader->BitsPerPixel: ");
    printf_int(infoHeader->BitsPerPixel, 10);
    printf("\n");

    printf("infoHeader->CompressionMethod: ");
    printf_int(infoHeader->CompressionMethod, 10);
    printf("\n");

    return bitmap;
}