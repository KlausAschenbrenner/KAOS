//
//  window.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//
//  This code is based on http://www.trackze.ro
//

#include "../heap/Heap.h"
#include "window.h"

// This array represents the definition of the Mouse Pointer Image
unsigned int MouseImage[MOUSE_BUFFER_SIZE] = 
{
    cX, c_, c_, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cX, c_, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cX, c_, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cO, cX, c_, c_, c_, c_, c_, c_, c_,
    cX, cO, cO, cO, cX, c_, c_ ,c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cX, c_, c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cX, c_, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cX, c_, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cX, c_, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cO, cX, c_,
    cX, cO, cO, cO, cO, cO, cO, cO, cO, cO, cX,
    cX, cX, cX, cX, cO, cO, cO, cX, cX, cX, cX,
    c_, c_, c_, c_, cX, cO, cO, cX, c_, c_, c_,
    c_, c_, c_, c_, cX, cO, cO, cX, c_, c_, c_,
    c_, c_, c_, c_, c_, cX, cO, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, cX, cO, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, c_, cX, cO, cX, c_, c_,
    c_, c_, c_, c_, c_, c_, c_, cX, cX, c_, c_ 
};

// This array represents our font.
// 128 characters with 8 bits wide and 12 bits height.
// Each bit tells us if the bit should be drawn or not.
char FontArray[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x24, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x24, 0x00, 0x08, 0x00, 0x00, 0x10, 0x10, 0x10, 0x54, 0x00, 0x00, 0x00, 0x00, 0x04, 0x38, 0x08, 0x3c, 0x7e, 0x04, 0x3e, 0x3c, 0x7e, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x70, 0x3c, 0x78, 0x7e, 0x7e, 0x3c, 0x42, 0x7c, 0x7e, 0x44, 0x40, 0x41, 0x42, 0x3c, 0x7c, 0x3c, 0x7c, 0x3c, 0x7f, 0x42, 0x42, 0x41, 0x42, 0x44, 0x7e, 0x1c, 0x40, 0x38, 0x10, 0x00, 0x30, 0x00, 0x40, 0x00, 0x02, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x24, 0x12, 0x1c, 0x40, 0x18, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x04, 0x4c, 0x18, 0x42, 0x02, 0x0c, 0x20, 0x42, 0x02, 0x24, 0x42, 0x10, 0x00, 0x00, 0x00, 0x00, 0x24, 0x38, 0x24, 0x48, 0x42, 0x44, 0x40, 0x40, 0x42, 0x42, 0x10, 0x04, 0x44, 0x40, 0x63, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x08, 0x42, 0x42, 0x41, 0x42, 0x44, 0x02, 0x10, 0x40, 0x08, 0x28, 0x00, 0x10, 0x00, 0x40, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x40, 0x00, 0x00, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x48, 0x12, 0x2a, 0xa2, 0x20, 0x10, 0x20, 0x08, 0x28, 0x10, 0x00, 0x00, 0x00, 0x08, 0x4c, 0x28, 0x42, 0x04, 0x14, 0x40, 0x40, 0x04, 0x24, 0x42, 0x10, 0x10, 0x02, 0x00, 0x40, 0x42, 0x44, 0x42, 0x44, 0x40, 0x42, 0x40, 0x40, 0x40, 0x42, 0x10, 0x04, 0x48, 0x40, 0x63, 0x62, 0x42, 0x42, 0x42, 0x42, 0x40, 0x08, 0x42, 0x42, 0x41, 0x24, 0x44, 0x02, 0x10, 0x20, 0x08, 0x44, 0x00, 0x00, 0x00, 0x40, 0x00, 0x02, 0x00, 0x12, 0x00, 0x40, 0x10, 0x04, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x7f, 0x28, 0xa4, 0x10, 0x00, 0x20, 0x08, 0x28, 0x10, 0x00, 0x00, 0x00, 0x08, 0x4c, 0x08, 0x02, 0x18, 0x24, 0x40, 0x40, 0x08, 0x18, 0x42, 0x00, 0x00, 0x0c, 0x7e, 0x30, 0x02, 0x82, 0x42, 0x44, 0x40, 0x42, 0x40, 0x40, 0x40, 0x42, 0x10, 0x04, 0x50, 0x40, 0x55, 0x52, 0x42, 0x42, 0x42, 0x42, 0x20, 0x08, 0x42, 0x42, 0x41, 0x24, 0x44, 0x04, 0x10, 0x20, 0x08, 0x00, 0x00, 0x00, 0x38, 0x40, 0x00, 0x02, 0x00, 0x10, 0x1e, 0x40, 0x00, 0x00, 0x20, 0x10, 0x54, 0x2c, 0x3c, 0x5c, 0x3c, 0x2c, 0x1c, 0x3e, 0x24, 0x22, 0x44, 0x42, 0x24, 0x3e, 0x10, 0x08, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x24, 0x18, 0x48, 0x20, 0x00, 0x20, 0x08, 0x00, 0x7c, 0x00, 0x7e, 0x00, 0x10, 0x54, 0x08, 0x02, 0x04, 0x44, 0x7c, 0x5c, 0x08, 0x24, 0x3e, 0x00, 0x00, 0x30, 0x00, 0x0c, 0x04, 0x92, 0x42, 0x78, 0x40, 0x42, 0x7c, 0x7c, 0x40, 0x42, 0x10, 0x04, 0x60, 0x40, 0x55, 0x52, 0x42, 0x7c, 0x42, 0x7c, 0x18, 0x08, 0x42, 0x42, 0x49, 0x18, 0x28, 0x08, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x04, 0x5c, 0x3c, 0x3a, 0x3c, 0x10, 0x22, 0x40, 0x00, 0x04, 0x22, 0x10, 0x2a, 0x12, 0x42, 0x22, 0x44, 0x12, 0x22, 0x10, 0x24, 0x22, 0x44, 0x22, 0x24, 0x02, 0x20, 0x08, 0x04, 0x32, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x24, 0x0c, 0x10, 0x52, 0x00, 0x20, 0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x54, 0x08, 0x04, 0x02, 0x44, 0x02, 0x62, 0x10, 0x42, 0x02, 0x00, 0x00, 0x40, 0x00, 0x02, 0x08, 0xaa, 0x7e, 0x44, 0x40, 0x42, 0x40, 0x40, 0x4e, 0x7e, 0x10, 0x04, 0x50, 0x40, 0x49, 0x4a, 0x42, 0x40, 0x42, 0x50, 0x04, 0x08, 0x42, 0x42, 0x49, 0x18, 0x10, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x3c, 0x62, 0x42, 0x46, 0x42, 0x3c, 0x22, 0x5c, 0x10, 0x04, 0x2c, 0x10, 0x2a, 0x12, 0x42, 0x22, 0x44, 0x10, 0x20, 0x10, 0x24, 0x22, 0x54, 0x24, 0x24, 0x04, 0x10, 0x08, 0x08, 0x4c, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xfe, 0x0a, 0x22, 0x4a, 0x00, 0x20, 0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x54, 0x08, 0x08, 0x02, 0x7e, 0x02, 0x42, 0x10, 0x42, 0x02, 0x10, 0x10, 0x30, 0x7e, 0x0c, 0x10, 0xaa, 0x42, 0x42, 0x40, 0x42, 0x40, 0x40, 0x42, 0x42, 0x10, 0x44, 0x48, 0x40, 0x49, 0x4a, 0x42, 0x40, 0x42, 0x4c, 0x02, 0x08, 0x42, 0x24, 0x49, 0x24, 0x10, 0x20, 0x10, 0x08, 0x08, 0x00, 0x00, 0x00, 0x44, 0x42, 0x40, 0x42, 0x7e, 0x10, 0x1e, 0x62, 0x10, 0x04, 0x30, 0x10, 0x2a, 0x12, 0x42, 0x32, 0x3c, 0x10, 0x1c, 0x10, 0x24, 0x22, 0x54, 0x18, 0x1c, 0x08, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x0a, 0x45, 0x44, 0x00, 0x20, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x64, 0x08, 0x10, 0x02, 0x04, 0x42, 0x42, 0x10, 0x42, 0x02, 0x10, 0x10, 0x0c, 0x00, 0x30, 0x10, 0x94, 0x42, 0x42, 0x40, 0x42, 0x40, 0x40, 0x42, 0x42, 0x10, 0x44, 0x44, 0x40, 0x41, 0x46, 0x42, 0x40, 0x4a, 0x42, 0x42, 0x08, 0x42, 0x24, 0x49, 0x24, 0x10, 0x40, 0x10, 0x08, 0x08, 0x00, 0x00, 0x00, 0x44, 0x42, 0x40, 0x42, 0x40, 0x10, 0x02, 0x42, 0x10, 0x04, 0x28, 0x10, 0x2a, 0x12, 0x42, 0x2c, 0x04, 0x10, 0x02, 0x10, 0x24, 0x22, 0x54, 0x24, 0x04, 0x10, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x2a, 0x05, 0x3a, 0x00, 0x10, 0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x40, 0x64, 0x08, 0x20, 0x44, 0x04, 0x42, 0x42, 0x10, 0x42, 0x04, 0x00, 0x20, 0x02, 0x00, 0x40, 0x00, 0x40, 0x42, 0x42, 0x42, 0x44, 0x40, 0x40, 0x42, 0x42, 0x10, 0x44, 0x42, 0x40, 0x41, 0x46, 0x42, 0x40, 0x44, 0x42, 0x42, 0x08, 0x42, 0x24, 0x49, 0x42, 0x10, 0x40, 0x10, 0x04, 0x08, 0x00, 0x00, 0x00, 0x44, 0x62, 0x42, 0x46, 0x42, 0x10, 0x22, 0x42, 0x10, 0x24, 0x24, 0x10, 0x2a, 0x12, 0x42, 0x20, 0x04, 0x10, 0x22, 0x10, 0x24, 0x14, 0x54, 0x44, 0x04, 0x20, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x1c, 0x02, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x20, 0x00, 0x00, 0x40, 0x38, 0x08, 0x7e, 0x38, 0x04, 0x3c, 0x3c, 0x10, 0x3c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x42, 0x7c, 0x3c, 0x78, 0x7e, 0x40, 0x3c, 0x42, 0x7c, 0x38, 0x42, 0x7e, 0x41, 0x42, 0x3c, 0x40, 0x3a, 0x42, 0x3c, 0x08, 0x3c, 0x18, 0x36, 0x42, 0x10, 0x7e, 0x1c, 0x04, 0x38, 0x00, 0x7f, 0x00, 0x3a, 0x5c, 0x3c, 0x3a, 0x3c, 0x10, 0x1c, 0x42, 0x08, 0x18, 0x22, 0x08, 0x2a, 0x12, 0x3c, 0x20, 0x02, 0x10, 0x1c, 0x0e, 0x1a, 0x08, 0x2a, 0x42, 0x38, 0x3e, 0x08, 0x08, 0x10, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x20, 0x00, 0x00, 0x40, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x00, 0x00
};

// Creates a new List
List *NewList()
{
    // Creates a new List structure
    List *list = malloc(sizeof(List));
    list->Count = 0;
    list->RootNode = (ListNode *)0x0;

    return list;
}

// Creates a new ListNode
ListNode *NewListNode(void *Payload)
{
    ListNode *node = malloc(sizeof(ListNode));
    node->Previous = (ListNode *)0x0;
    node->Next = (ListNode *)0x0;
    node->Payload = Payload;

    return node;
}

// Creates a new Window
Window *NewWindow(int X, int Y, int Width, int Height, Context *Context, char *Title)
{
    // Create a new Window structure
    Window *window = malloc(sizeof(Window));
    window->X = X;
    window->Y = Y;
    window->Width = Width;
    window->Height = Height;
    window->Context = Context;
    window->Title = Title;

    // Return the newly created Window
    return window;
}

// Creates a new Desktop
Desktop *NewDesktop(Context *Context, int Color)
{
    // Create a new Desktop structure
    Desktop *desktop = malloc(sizeof(Desktop));
    desktop->Children = NewList();
    desktop->Context = Context;
    desktop->Color = Color;
    desktop->LastMouseButtonState = 0;

    return desktop;
}

// Adds a new Window to the Desktop
Window *NewDesktopWindow(Desktop *Desktop, int X, int Y, int Width, int Height, char *Title)
{
    // Create a new Window and add it to the Desktop
    Window *window = NewWindow(X, Y, Width, Height, Desktop->Context, Title);
    AddNodeToList(Desktop->Children, (void *)window);
    
    return window;
}

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

// Creates a new Context
Context *NewContext(int Width, int Height, unsigned char *FrameDoubleBuffer, unsigned char *VgaFrameBuffer)
{
    Context *context = (Context *)malloc(sizeof(Context));
    context->ClipRectangles = NewList();
    context->Width = Width;
    context->Height = Height;
    context->FrameDoubleBuffer = FrameDoubleBuffer;
    context->VgaFrameBuffer = VgaFrameBuffer;
}

// Adds a new Node to the given List
void AddNodeToList(List *List, void *Payload)
{
    ListNode *newNode = NewListNode(Payload);

    if (!List->RootNode)
    {
        // Add the first, initial Node to the List
        List->RootNode = newNode;
    }
    else
    {
        ListNode *currentNode = List->RootNode;
        
        // Move to the end of the List
        while (currentNode->Next)
            currentNode = currentNode->Next;

        // Add the new Node to the end of the List
        currentNode->Next = newNode;
        newNode->Previous = currentNode;
    }
    
    List->Count++;
}

// Removes a Node from the given List
void *RemoveNodeFromList(List *List, int Index)
{
    int currentIndex;
    void *payload;

    if (List->Count == 0 || Index >= List->Count)
        return (void *)0x0;

    ListNode *currentNode = List->RootNode;

    for (currentIndex = 0; (currentIndex < Index) && currentNode; currentIndex++)
        currentNode = (ListNode *)currentNode->Next;

    if (!currentNode)
        return (void *)0x0;

    payload = currentNode->Payload;

    if (currentNode->Previous)
    {
        ListNode *previous = (ListNode *)currentNode->Previous;
        previous->Next = currentNode->Next;
    }
    
    if (currentNode->Next)
    {
        ListNode *next = (ListNode *)currentNode->Next;
        next->Previous = currentNode->Previous;
    }

    if (Index == 0)
        List->RootNode = (ListNode *)currentNode->Next;

    // free(currentNode);

    List->Count--;

    return payload;
}

// Returns a Node from the given List
void *GetNodeFromList(List *List, int Index)
{
    if (List->Count == 0 || Index >= List->Count)
        return (void *)0x0;

    ListNode *currentNode = List->RootNode;
    int currentIndex;

    // Iterate through the List until we have found the requested Node
    for (currentIndex = 0; (currentIndex < Index) && currentNode; currentIndex++)
        currentNode = (ListNode *)currentNode->Next;

    // Return the requested Node if found - otherwise a NULL pointer
    return currentNode ? currentNode->Payload : (void *)0x0;
}

// Draws a filled Rectangle
void Context_FillRect(Context *Context, int X, int Y, int Width, int Height, int Color)
{
    int currentX;
    int maxX = X + Width;
    int maxY = Y + Height;

    // Check the width limit
    if (maxX > Context->Width)
        maxX = Context->Width;

    // Check the height limit
    if (maxY > Context->Height)
        maxY = Context->Height;

    // Limits the screen on the left side
    if (X < 0)
        X = 0;

    // Draw the Rectangle
    for (; Y < maxY; Y++)
    {
        for (currentX = X; currentX < maxX; currentX++)
        {
            Context->FrameDoubleBuffer[Y * Context->Width + currentX] = Color;
        }
    }

    /* int startX, currentX, currentY, endX, endY;
    int maxX = X + Width;
    int maxY = Y + Height;
    int i;

    Rectangle *clipArea;
    Rectangle screenArea;

    if (Context->ClipRectangles->Count > 0)
    {
        for (i = 0; i < Context->ClipRectangles->Count; i++)
        {
            clipArea = (Rectangle *)GetNodeFromList(Context->ClipRectangles, i);
            ContextClippedRectangle(Context, X, Y, Width, Height, clipArea, Color);
        }
    }
    else
    {
        screenArea.Top = 0;
        screenArea.Left = 0;
        screenArea.Bottom = Context->Height - 1;
        screenArea.Right = Context->Width - 1;
        ContextClippedRectangle(Context, X, Y, Width, Height, &screenArea, Color);
    } */
}

// Draws a Window
void WindowPaint(Window *Window)
{
    char str[32] = "";

    // Draw the Window border
    ContextDrawRectangle(Window->Context, Window->X, Window->Y, Window->Width, Window->Height, WINDOW_BORDERCOLOR);
    ContextDrawRectangle(Window->Context, Window->X + 1, Window->Y + 1, Window->Width - 2, Window->Height - 2, WINDOW_BORDERCOLOR);
    ContextDrawRectangle(Window->Context, Window->X + 2, Window->Y + 2, Window->Width - 4, Window->Height - 4, WINDOW_BORDERCOLOR);

    ContextDrawHorizontalLine(Window->Context, Window->X + 3, Window->Y + 28, Window->Width - 6, WINDOW_BORDERCOLOR);
    ContextDrawHorizontalLine(Window->Context, Window->X + 3, Window->Y + 29, Window->Width - 6, WINDOW_BORDERCOLOR);
    ContextDrawHorizontalLine(Window->Context, Window->X + 3, Window->Y + 30, Window->Width - 6, WINDOW_BORDERCOLOR);

    // Draw the Title Bar
    Context_FillRect(Window->Context, Window->X + 3, Window->Y + 3, Window->Width - 6, 25, WINDOW_TITLE_COLOR_ACTIVE);

    // Draw the Window Title
    DrawString(Window->Context, Window->Title, Window->X + 10, Window->Y + 10, 0xFFFF);

    // Draw the Window background
    Context_FillRect(Window->Context, Window->X + 3, Window->Y + 31, Window->Width - 6, Window->Height - 34, WINDOW_BACKGROUND_COLOR);

    // Draw the PID
    DrawString(Window->Context, "PID: ", Window->X + 10, Window->Y + 38, 0x0000);
    ltoa(Window->Task->PID, 10, str);
    DrawString(Window->Context, &str, Window->X + 42, Window->Y + 38, 0x0000);

    // Draw the number of Context Switches
    DrawString(Window->Context, "Number of Context Switches: ", Window->X + 10, Window->Y + 56, 0x0000);
	ltoa(Window->Task->ContextSwitches, 10, str);
    DrawString(Window->Context, &str, Window->X + 234, Window->Y + 56, 0x0000);

    DrawString(Window->Context, "RIP: 0x", Window->X + 10, Window->Y + 74, 0x0000);
	ltoa(Window->Task->rip, 16, str);
    DrawString(Window->Context, &str, Window->X + 66, Window->Y + 74, 0x0000);
}

// Draws the Mouse Pointer Image onto the Desktop
void MousePointerPaint(Desktop *Desktop)
{
    int x, y;

    for (y = 0; y < MOUSE_HEIGHT; y++)
    {
        for (x = 0; x < MOUSE_WIDTH; x++)
        {
            // Check if we have a transparent pixel
            if (MouseImage[y * MOUSE_WIDTH + x] != 0xDEAD)
                Desktop->Context->FrameDoubleBuffer[(y + Desktop->MouseY) * Desktop->Context->Width + (x + Desktop->MouseX)] = MouseImage[y * MOUSE_WIDTH + x];
        }
    }
}

// Draws the Desktop
void DesktopPaint(Desktop *Desktop)
{
    Window *currentWindow;
    int i;

    // Reset the Frame Double Buffer
    memset(Desktop->Context->FrameDoubleBuffer, 0, Desktop->Context->Width * Desktop->Context->Height * WINDOW_BPP / 8);

    // Draw the Desktop
    Context_FillRect(Desktop->Context, 0, 0, Desktop->Context->Width, Desktop->Context->Height, Desktop->Color);
    DrawString(Desktop->Context, "KAOS x64\0", 10, 10, 0x0000);
    DrawString(Desktop->Context, "(c) 2019 by Klaus Aschenbrenner\0", 10, 26, 0x0000);

    // Draw a calculated value on the Desktop
    int *value = (int *)0xFFFF800000700000;
    char str[32] = "";
    itoa(*value, 10, str);
    DrawString(Desktop->Context, &str, 10, 42, 0x0000);

    // Draw each Window on top of the Desktop
    for (i = 0; (currentWindow = (Window *)GetNodeFromList(Desktop->Children, i)); i++)
        WindowPaint(currentWindow);

    // And finally we draw the Mouse on top of the Desktop
    MousePointerPaint(Desktop);

    // Copy the Frame Double Buffer to the VGA Buffer
    memcpy(Desktop->Context->VgaFrameBuffer, Desktop->Context->FrameDoubleBuffer, Desktop->Context->Width * Desktop->Context->Height * WINDOW_BPP / 8);




    /* // Reset the Frame Double Buffer
    memset(Desktop->Context->FrameDoubleBuffer, 0, Desktop->Context->Width * Desktop->Context->Height * WINDOW_BPP / 8);

    int i, j;
    Window *currentWindow, *clippingWindow;
    Rectangle *tempRectangle;
    List *clipWindows;

    tempRectangle = NewRectange(0, 0, Desktop->Context->Height - 1, Desktop->Context->Width - 1);
    ContextAddClipRectangle(Desktop->Context, tempRectangle);

    for (i = 0; i < Desktop->Children->Count; i++)
    {
        currentWindow = (Window *)GetNodeFromList(Desktop->Children, i);
        tempRectangle = NewRectange(currentWindow->Y, currentWindow->X, currentWindow->Y + currentWindow->Height - 1, currentWindow->X + currentWindow->Width - 1);
        ContextSubtractClipRectangle(Desktop->Context, tempRectangle);
        // free(tempRectangle);   
    }

    Context_FillRect(Desktop->Context, 0, 0, Desktop->Context->Width, Desktop->Context->Height, Desktop->Color);

    ContextClearClipRectangle(Desktop->Context);

    for (i = 0; i < Desktop->Children->Count; i++)
    {
        currentWindow = (Window *)GetNodeFromList(Desktop->Children, i);
        tempRectangle = NewRectange(currentWindow->Y, currentWindow->X, currentWindow->Y + currentWindow->Height - 1, currentWindow->X + currentWindow->Width - 1);
        ContextAddClipRectangle(Desktop->Context, tempRectangle);

        clipWindows = DesktopGetWindowsAbove(Desktop, currentWindow);

        while (clipWindows->Count > 0)
        {
            clippingWindow = (Window *)RemoveNodeFromList(clipWindows, 0);
            
            if (clippingWindow == currentWindow)
                continue;

            tempRectangle = NewRectange(clippingWindow->Y, clippingWindow->X, clippingWindow->Y + clippingWindow->Height - 1, clippingWindow->X + clippingWindow->Width - 1);
            ContextSubtractClipRectangle(Desktop->Context, tempRectangle);
            // free(tempRectangle);
        }

        WindowPaint(currentWindow);

        // free(clippingWindow);
        ContextClearClipRectangle(Desktop->Context);
    }

    // Draw the Mouse
    Context_FillRect(Desktop->Context, Desktop->MouseX, Desktop->MouseY, 5, 5, 0x0000);

    // Copy the Frame Double Buffer to the VGA Buffer
    memcpy(Desktop->Context->VgaFrameBuffer, Desktop->Context->FrameDoubleBuffer, Desktop->Context->Width * Desktop->Context->Height * WINDOW_BPP / 8); */
}

// Processes the Mouse on the Desktop
void DesktopProcessMouse(Desktop *Desktop, int MouseX, int MouseY, int MouseClick, int DragWindow)
{
    Window *child;
    int i;

    Desktop->MouseX = MouseX;
    Desktop->MouseY = MouseY;

    if (MouseClick)
    {
        if (!Desktop->LastMouseButtonState)
        {
            // Iterate through all Windows backwards
            for (i = Desktop->Children->Count - 1; i >= 0; i--)
            {
                // Get a reference to the Window
                child = (Window *)GetNodeFromList(Desktop->Children, i);

                // Check if the Mouse was within the current Window
                if (MouseX >= child->X && MouseX < (child->X + child->Width) &&
                    MouseY >= child->Y && MouseY < (child->Y + 31))
                {
                    // Remove and re-add the Window at the top
                    RemoveNodeFromList(Desktop->Children, i);
                    AddNodeToList(Desktop->Children, (void *)child);

                    if (DragWindow)
                    {
                        Desktop->DragOffsetX = MouseX - child->X;
                        Desktop->DragOffsetY = MouseY - child->Y;
                        Desktop->DraggedChild = child;
                    }

                    break;
                }
            }
        }
    }
    else
    {
        Desktop->DraggedChild = (Window *)0x0;
    }
    
    if (Desktop->DraggedChild != 0x0)
    {
        // Drag the Window to the new position
        Desktop->DraggedChild->X = MouseX - Desktop->DragOffsetX;
        Desktop->DraggedChild->Y = MouseY - Desktop->DragOffsetY;
    }

    Desktop->LastMouseButtonState = MouseClick;
}

// Draws a Rectangle
void ContextDrawRectangle(Context *Context, int X, int Y, int Width, int Height, int Color)
{
    ContextDrawHorizontalLine(Context, X, Y, Width, Color);
    ContextDrawVerticalLine(Context, X, Y + 1, Height - 2, Color);
    ContextDrawHorizontalLine(Context, X, Y + Height - 1, Width, Color);
    ContextDrawVerticalLine(Context, X + Width - 1, Y + 1, Height - 2, Color);
}

// Draws a horizontal line
void ContextDrawHorizontalLine(Context *Context, int X, int Y, int Length, int Color)
{
    // Limits the screen on the left side
    if (X < 0)
    {
        Length = Length + X;
        X = 0;
    }

    Context_FillRect(Context, X, Y, Length, 1, Color);
}

// Draws a vertical line
void ContextDrawVerticalLine(Context *Context, int X, int Y, int Length, int Color)
{
    Context_FillRect(Context, X, Y, 1, Length, Color);
}

// Draws a single Character
static void DrawCharacter(Context *Context, char Character, int X, int Y, int Color)
{
    int fontX, fontY;
    char shiftLine;

    for (fontY = 0; fontY < FONT_HEIGHT; fontY++)
    {
        shiftLine = FontArray[fontY * FONT_CHARACTERS + Character];

        for (fontX = 0; fontX < FONT_WIDTH; fontX ++)
        {
            if (shiftLine & 0x80 && ((fontX + X) >= 0 && fontX + X <= Context->Width))
            {
                Context->FrameDoubleBuffer[(fontY + Y) * Context->Width + (fontX + X)] = Color;
            }

            shiftLine <<= 1;
        }
    }
}

// Draws a null-terminated String at the given location
void DrawString(Context *Context, char *String, int X, int Y, int Color)
{
    int i = 0;

    while (*String != '\0')
	{
		DrawCharacter(Context, *String, X + (i * FONT_WIDTH), Y, Color);
		String++;
        i++;
	}
}

// Gets a list of windows overlapping the passed in window
/* List *DesktopGetWindowsAbove(Desktop *Desktop, Window *InputWindow)
{
    int i;
    List *returnList = NewList();
    Window *currentWindow;

    for (i = 0; i < Desktop->Children->Count; i++)
    {
        if (InputWindow == (Window *)GetNodeFromList(Desktop->Children, i))
            break;
    }

    for (; i < Desktop->Children->Count; i++)
    {
        currentWindow = (Window *)GetNodeFromList(Desktop->Children, i);

        if (currentWindow->X <= (InputWindow->X + InputWindow->Width - 1) &&
            (currentWindow->X + currentWindow->Width - 1) >= InputWindow->X &&
            currentWindow->Y <= (InputWindow->Y + InputWindow->Height - 1) &&
            (InputWindow->Y + InputWindow->Height - 1) >= InputWindow->Y)
        {
            AddNodeToList(returnList, currentWindow);   
        }
    }

    return returnList;
} */

// Splits the 2 given Rectangles
/* List *RectangleSplit(Rectangle *SubjectRectangle, Rectangle *CuttingRectangle)
{
    List *outputRectangles = NewList();

    // Clone the Subject Rectangle
    Rectangle subjectCopy;
    subjectCopy.Top = SubjectRectangle->Top;
    subjectCopy.Left = SubjectRectangle->Left;
    subjectCopy.Bottom = SubjectRectangle->Bottom;
    subjectCopy.Right = SubjectRectangle->Right;

    Rectangle *tempRectangle;

    // 1. Split by left edge if that edge is between the subject's left and right edges
    if (CuttingRectangle->Left >= subjectCopy.Left && CuttingRectangle->Left <= subjectCopy.Right)
    {
        tempRectangle = NewRectange(subjectCopy.Top, subjectCopy.Left, subjectCopy.Bottom, CuttingRectangle->Left - 1);
        AddNodeToList(outputRectangles, tempRectangle);

        // Shrink the subject rectangle to exclude the split portion
        subjectCopy.Left = CuttingRectangle->Left;
    }

    // 2. Split by top edge if that edge is between the subjects' top and bottom edges
    if (CuttingRectangle->Top >= subjectCopy.Top && CuttingRectangle->Top <= subjectCopy.Bottom)
    {
        tempRectangle = NewRectange(subjectCopy.Top, subjectCopy.Left, CuttingRectangle->Top - 1, subjectCopy.Right);
        AddNodeToList(outputRectangles, tempRectangle);

        // Shrink the subject rectangle to exclude the split portion
        subjectCopy.Top = CuttingRectangle->Top;
    }

    // 3. Split by right edge if that edge is between the subject's left and right edges
    if (CuttingRectangle->Right >= subjectCopy.Left && CuttingRectangle->Right <= subjectCopy.Right)
    {
        tempRectangle = NewRectange(subjectCopy.Top, CuttingRectangle->Right + 1, subjectCopy.Bottom, subjectCopy.Right);
        AddNodeToList(outputRectangles, tempRectangle);

        // Shrink the subject rectangle to exclude the split portion
        subjectCopy.Right = CuttingRectangle->Right;
    }

    // 4. Split by bottom edge if that edge is between the subject's top and bottom edges
    if (CuttingRectangle->Bottom >= subjectCopy.Top && CuttingRectangle->Bottom <= subjectCopy.Bottom)
    {
        tempRectangle = NewRectange(CuttingRectangle->Bottom + 1, subjectCopy.Left, subjectCopy.Bottom, subjectCopy.Right);
        AddNodeToList(outputRectangles, tempRectangle);

        // Shrink the subject rectangle to exclude the split portion
        subjectCopy.Bottom = CuttingRectangle->Bottom;
    }

    return outputRectangles;
} */

// Adds a new clipped Rectangle to the Context
/* void ContextAddClipRectangle(Context *Context, Rectangle *AddedRectangle)
{
    ContextSubtractClipRectangle(Context, AddedRectangle);
    AddNodeToList(Context->ClipRectangles, AddedRectangle);
}

void ContextSubtractClipRectangle(Context *Context, Rectangle *SubtractedRectangle)
{
    int i, j;
    Rectangle *currentRectangle;
    List *splitRectangles;

    for (i = 0; i < Context->ClipRectangles->Count > 0;)
    {
        currentRectangle = GetNodeFromList(Context->ClipRectangles, i);

        if (!(currentRectangle->Left <= SubtractedRectangle->Right &&
            currentRectangle->Right >= SubtractedRectangle->Left &&
            currentRectangle->Top <= SubtractedRectangle->Bottom &&
            currentRectangle->Bottom >= SubtractedRectangle->Top))
        {
            i++;
            continue;
        }

        RemoveNodeFromList(Context->ClipRectangles, i);
        splitRectangles = RectangleSplit(currentRectangle, SubtractedRectangle);
        free(currentRectangle);

        while (splitRectangles->Count > 0)
        {
            currentRectangle = (Rectangle *)RemoveNodeFromList(splitRectangles, 0);
            AddNodeToList(Context->ClipRectangles, currentRectangle);
        }

        free(splitRectangles);
        i = 0;
    }
}

// Clears the clipped Rectangles from the Context
void ContextClearClipRectangle(Context *Context)
{
    Rectangle *currentRectangle;

    while (Context->ClipRectangles->Count)
    {
        currentRectangle = (Rectangle *)RemoveNodeFromList(Context->ClipRectangles, 0);
        free(currentRectangle);
    }
} */

/* void ContextClippedRectangle(Context *Context, int X, int Y, int Width, int Height, Rectangle *ClipArea, int Color)
{
    int currentX;
    int maxX = X + Width;
    int maxY = Y + Height;

    if (X < ClipArea->Left)
        X = ClipArea->Left;

    if (Y < ClipArea->Top)
        Y = ClipArea->Top;

    if (maxX > ClipArea->Right + 1)
        maxX = ClipArea->Right + 1;

    if (maxY > ClipArea->Bottom + 1)
        maxY = ClipArea->Bottom + 1;

    for (; Y < maxY; Y++)
    {
        for (currentX = X; currentX < maxX; currentX++)
        {
            Context->FrameDoubleBuffer[Y * Context->Width + currentX] = Color;
        }
    }
} */