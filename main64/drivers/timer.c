//
//  timer.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "common.h"
#include "timer.h"

int counter = 0;

// Initializes the hardware timer
void InitTimer(int Frequency)
{
    // Registers the IRQ callback function for the hardware timer
    RegisterIRQHandler(32, &TimerCallback);

    int divisor = 1193180 / Frequency;
    
    // Send the command byte
    outb(0x43, 0x36);
    
    // Divisor has to be sent byte-wise, so split here into upper/lower bytes
    unsigned char l = (unsigned char)(divisor & 0xFF);
    unsigned char h = (unsigned char)((divisor >> 8) & 0xFF);
    
    // Send the frequency divisor
    outb(0x40, l);
    outb(0x40, h);
}

// IRQ callback function
static void TimerCallback(int Number)
{
    counter++;
    
    /* char str[32] = {0};
    itoa(counter, 10, str);
    
    printf("Timer counter: ");
    printf(str);
    printf("\n"); */
}