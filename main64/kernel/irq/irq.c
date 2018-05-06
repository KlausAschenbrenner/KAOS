//
//  irq.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 23.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "irq.h"
#include "../idt/idt.h"
#include "../pic/pic.h"

// Defines an array for our various IRQ handlers
IRQ_HANDLER InterruptHandlers[256];

// Common IRQ handler that is called as soon as an IRQ is raised
void IrqHandler(InterruptRegisters registers)
{
    // Signal that we have handled the received interrupt
    if (registers.InterruptNumber >= 40)
    {
        // Send reset signal to slave
        outb(I86_PIC2_REG_COMMAND, I86_PIC_OCW2_MASK_EOI);
    }
    
    // Send reset signal to master
    outb(I86_PIC1_REG_COMMAND, I86_PIC_OCW2_MASK_EOI);
    
    // Call the IRQ callback function, if one is registered
    if (InterruptHandlers[registers.InterruptNumber] != 0)
    {
        IRQ_HANDLER handler = InterruptHandlers[registers.InterruptNumber];
        handler(registers);
    }
}

// Registers a IRQ callback function
void RegisterIRQHandler(int n, IRQ_HANDLER Handler)
{
    InterruptHandlers[n] = Handler;
}