//
//  kernel.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 13.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_kernel_h
#define KAOS_kernel_h

// Outputs formatted tabular data
void TestTabs();

// Tests the scrolling functionality of the screen driver
void TestScrolling();

// Tests the functionality of the keyboard driver
void TestKeyboardInput();

// Tests the error handler for the "Divide by Zero" exception
void TestDivideByZeroException();

// Implements a simple sleep function
void Sleep();

#endif
