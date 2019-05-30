//
//  mouse.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "common.h"
#include "screen.h"
#include "../ui/Desktop.h"
#include "../ui/window.h"

static char mouseData[3];

// Stores the current X mouse coordinate
int MouseX = 0;

// Stores the current Y mouse coordinate
int MouseY = 0;

// Stores if the left mouse button is pressed
int LeftMouseButtonDown = 0;

// Stores if the left mouse button was released
int LeftMouseButtonUp = 0;

static void MouseWait(unsigned char a_type) //unsigned char
{
  unsigned int _time_out=100000; //unsigned int

  if(a_type==0)
  {
    while(_time_out--) //Data
    {
      if((inb(0x64) & 1)==1)
      {
        return;
      }
    }
    return;
  }
  else
  {
    while(_time_out--) //Signal
    {
      if((inb(0x64) & 2)==0)
      {
        return;
      }
    }
    return;
  }
}

static void MouseWrite(unsigned char a_write) //unsigned char
{
  //Wait to be able to send a command
  MouseWait(1);
  //Tell the mouse we are sending a command
  outb(0x64, 0xD4);
  //Wait for the final part
  MouseWait(1);
  //Finally write
  outb(0x60, a_write);
}

static unsigned char MouseRead()
{
  //Get's response from mouse
  MouseWait(0); 
  return inb(0x60);
}

static void MouseIRQHandler(int Number)
{
    signed int x, y;

    mouseData[0] = inb(0x60);
    mouseData[1] = inb(0x60);
    mouseData[2] = inb(0x60);
    x = mouseData[1];
    y = mouseData[2];
    
    /* printf_int(mouseData[0], 16);
    printf("\n");
    printf_int(mouseData[1], 16);
    printf("\n");
    printf_int(mouseData[2], 16);
    printf("\n");
    printf("\n"); */

    if (mouseData[0] == 0x8 && LeftMouseButtonDown == 1)
    {
        printf("Left Mouse Button up!");
        printf("\n");
        LeftMouseButtonDown = 0;
        LeftMouseButtonUp = 1;
        return;
    }

    if (mouseData[0] == 0x9 && LeftMouseButtonDown == 0)
    {
        printf("Left Mouse Button down!");
        printf("\n");
        LeftMouseButtonDown = 1;
    }

    if (mouseData[0] == 0x8 || mouseData[0] == 0x18 || mouseData[0] == 0x28 || mouseData[0] == 0x38 ||
        mouseData[0] == 0x9 || mouseData[0] == 0x19 || mouseData[0] == 0x29 || mouseData[0] == 0x39)
    {
      if (x != y)
      {
        MouseX += x;
        MouseY -= y;

        printf_int(MouseX, 10);
        printf(", ");
        printf_int(MouseY, 10);
        printf("\n");
        return;
      }
    }

    // Limit the Mouse to the current screen area
		if (MouseX < 0)
			MouseX = 0;

		if (MouseY < 0)
			MouseY = 0;

		if (MouseX > WINDOW_WIDTH - MOUSE_WIDTH)
			MouseX = WINDOW_WIDTH - MOUSE_WIDTH;

		if (MouseY > WINDOW_HEIGHT - 5)
			MouseY = WINDOW_HEIGHT - 5;
}

void MouseInstall()
{
  unsigned char _status;  //unsigned char

  //Enable the auxiliary mouse device
  MouseWait(1);
  outb(0x64, 0xA8);

  //Enable the interrupts
  MouseWait(1);
  outb(0x64, 0x20);
  MouseWait(0);
  _status=(inb(0x60) | 2);
  MouseWait(1);
  outb(0x64, 0x60);
  MouseWait(1);
  outb(0x60, _status);

  //Tell the mouse to use default settings
  MouseWrite(0xF6);
  MouseRead();  //Acknowledge

  //Enable the mouse
  MouseWrite(0xF4);
  MouseRead();  //Acknowledge

  // Setup the mouse handler
  RegisterIRQHandler(44, &MouseIRQHandler);
}