//
//  mouse.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 24.04.2019.
//  Copyright (c) 2019 Klaus Aschenbrenner. All rights reserved.
//

#include "common.h"

void MouseWait(unsigned char a_type) //unsigned char
{
  unsigned int _time_out=1000; //unsigned int

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

inline void MouseWrite(unsigned char a_write) //unsigned char
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

unsigned char MouseRead()
{
  //Get's response from mouse
  MouseWait(0); 
  return inb(0x60);
}

void MouseHandler1(int Number)
{
  /* unsigned char *p = (unsigned char *)0xFFFF8000000A0000;
	int start = 16000;
	int i = 0;

  // Draw the new line
  for (i = start; i < start + 320; i++)
    p[i] = 1; // red pixel */

    printf("MouseHandler called!");
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
  // RegisterIRQHandler(12, &MouseHandler1);
}