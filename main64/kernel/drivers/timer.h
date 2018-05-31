//
//  timer.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_timer_h
#define KAOS_timer_h

// Initializes the hardware timer
void InitTimer(int Frequency);

// IRQ callback function
static void TimerCallback(int Number);

#endif