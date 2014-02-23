//
//  Idt.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "idt.h"
#include "../irq/irq.h"

// The 256 possible interrupt gates
IdtEntry _idtEntries[256];

// The pointer that points to the interrupt gates
IdtPointer _idtPointer;

// Our generic ISR handler
void IsrHandler(InterruptRegisters registers)
{
    char str[32] = {0};
    itoa(registers.InterruptNumber, 16, str);
    
    printf("Interrupt: ");
    printf("0x");
    printf(str);
    printf("\n");
    printf("Error code: ");
    itoa(registers.ErrorCode, 10, str);
    printf(str);
    printf("\n");
    
    // Halt the system
    for (;;);
}

// Initializes the IDT table
void InitIdt()
{
    _idtPointer.limit = sizeof(IdtEntry) * 256 - 1;
    _idtPointer.base = (unsigned int)&_idtEntries;
    
    memset(&_idtEntries, 0, sizeof(IdtEntry) * 256);
    
    // Setup the 32 Exception handler
    IdtSetGate(0, (unsigned int)Isr0, 0x8, 0x8E);
	IdtSetGate(1, (unsigned int)Isr1, 0x8, 0x8E);
	IdtSetGate(2, (unsigned int)Isr2, 0x8, 0x8E);
	IdtSetGate(3, (unsigned int)Isr3, 0x8, 0x8E);
	IdtSetGate(4, (unsigned int)Isr4, 0x8, 0x8E);
	IdtSetGate(5, (unsigned int)Isr5, 0x8, 0x8E);
	IdtSetGate(6, (unsigned int)Isr6, 0x8, 0x8E);
	IdtSetGate(7, (unsigned int)Isr7, 0x8, 0x8E);
	IdtSetGate(8, (unsigned int)Isr8, 0x8, 0x8E);
	IdtSetGate(9, (unsigned int)Isr9, 0x8, 0x8E);
	IdtSetGate(10, (unsigned int)Isr10, 0x8, 0x8E);
	IdtSetGate(11, (unsigned int)Isr11, 0x8, 0x8E);
	IdtSetGate(12, (unsigned int)Isr12, 0x8, 0x8E);
	IdtSetGate(13, (unsigned int)Isr13, 0x8, 0x8E);
	IdtSetGate(14, (unsigned int)Isr14, 0x8, 0x8E);
	IdtSetGate(15, (unsigned int)Isr15, 0x8, 0x8E);
	IdtSetGate(16, (unsigned int)Isr16, 0x8, 0x8E);
	IdtSetGate(17, (unsigned int)Isr17, 0x8, 0x8E);
	IdtSetGate(18, (unsigned int)Isr18, 0x8, 0x8E);
	IdtSetGate(19, (unsigned int)Isr19, 0x8, 0x8E);
	IdtSetGate(20, (unsigned int)Isr20, 0x8, 0x8E);
	IdtSetGate(21, (unsigned int)Isr21, 0x8, 0x8E);
	IdtSetGate(22, (unsigned int)Isr22, 0x8, 0x8E);
	IdtSetGate(23, (unsigned int)Isr23, 0x8, 0x8E);
	IdtSetGate(24, (unsigned int)Isr24, 0x8, 0x8E);
	IdtSetGate(25, (unsigned int)Isr25, 0x8, 0x8E);
	IdtSetGate(26, (unsigned int)Isr26, 0x8, 0x8E);
	IdtSetGate(27, (unsigned int)Isr27, 0x8, 0x8E);
	IdtSetGate(28, (unsigned int)Isr28, 0x8, 0x8E);
	IdtSetGate(29, (unsigned int)Isr29, 0x8, 0x8E);
	IdtSetGate(30, (unsigned int)Isr30, 0x8, 0x8E);
	IdtSetGate(31, (unsigned int)Isr31, 0x8, 0x8E);
    
    // Setup the 15 IRQ handler
    IdtSetGate(32, (unsigned int)Irq0, 0x08, 0x8E);
    IdtSetGate(33, (unsigned int)Irq1, 0x08, 0x8E);
    IdtSetGate(34, (unsigned int)Irq2, 0x08, 0x8E);
    IdtSetGate(35, (unsigned int)Irq3, 0x08, 0x8E);
    IdtSetGate(36, (unsigned int)Irq4, 0x08, 0x8E);
    IdtSetGate(37, (unsigned int)Irq5, 0x08, 0x8E);
    IdtSetGate(38, (unsigned int)Irq6, 0x08, 0x8E);
    IdtSetGate(39, (unsigned int)Irq7, 0x08, 0x8E);
    IdtSetGate(40, (unsigned int)Irq8, 0x08, 0x8E);
    IdtSetGate(41, (unsigned int)Irq9, 0x08, 0x8E);
    IdtSetGate(42, (unsigned int)Irq10, 0x08, 0x8E);
    IdtSetGate(43, (unsigned int)Irq11, 0x08, 0x8E);
    IdtSetGate(44, (unsigned int)Irq12, 0x08, 0x8E);
    IdtSetGate(45, (unsigned int)Irq13, 0x08, 0x8E);
    IdtSetGate(46, (unsigned int)Irq14, 0x08, 0x8E);
    IdtSetGate(47, (unsigned int)Irq15, 0x08, 0x8E);
    
    // Loads the IDT table into the processor register (Assembler function)
    IdtFlush((unsigned int)&_idtPointer);
}

// Installs the corresponding ISR routine in the IDT table
static void IdtSetGate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags)
{
    _idtEntries[num].base_lo = base & 0xFFFF;
    _idtEntries[num].base_hi = (base >> 16) & 0xFFFF;
    _idtEntries[num].sel = sel;
    _idtEntries[num].always0 = 0;
    _idtEntries[num].flags = flags;
}