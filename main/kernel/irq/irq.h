//
//  irq.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_irq_h
#define KAOS_irq_h

#include "../../drivers/common.h"

// Our 15 IRQ routines (implemented in Assembler)
extern void Irq0();
extern void Irq1();
extern void Irq2();
extern void Irq3();
extern void Irq4();
extern void Irq5();
extern void Irq6();
extern void Irq7();
extern void Irq8();
extern void Irq9();
extern void Irq10();
extern void Irq11();
extern void Irq12();
extern void Irq13();
extern void Irq14();
extern void Irq15();

// IRQ handler that is called as soon as an IRQ is raised
void IrqHandler(InterruptRegisters registers);

// Callback function pointer for handling the various IRQs
typedef void (*IRQ_HANDLER)(InterruptRegisters);

// Registers a IRQ callback function
void RegisterIRQHandler(int n, IRQ_HANDLER Handler);

#endif
