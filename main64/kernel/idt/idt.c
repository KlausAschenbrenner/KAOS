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
    _idtPointer.base = (unsigned long)&_idtEntries;
    
    memset(&_idtEntries, 0, sizeof(IdtEntry) * 256);
    
    // Setup the 32 Exception handler
    IdtSetGate(0, (unsigned long)Isr0, 0x8, 0x8E);
	IdtSetGate(1, (unsigned long)Isr1, 0x8, 0x8E);
	IdtSetGate(2, (unsigned long)Isr2, 0x8, 0x8E);
	IdtSetGate(3, (unsigned long)Isr3, 0x8, 0x8E);
	IdtSetGate(4, (unsigned long)Isr4, 0x8, 0x8E);
	IdtSetGate(5, (unsigned long)Isr5, 0x8, 0x8E);
	IdtSetGate(6, (unsigned long)Isr6, 0x8, 0x8E);
	IdtSetGate(7, (unsigned long)Isr7, 0x8, 0x8E);
	IdtSetGate(8, (unsigned long)Isr8, 0x8, 0x8E);
	IdtSetGate(9, (unsigned long)Isr9, 0x8, 0x8E);
	IdtSetGate(10, (unsigned long)Isr10, 0x8, 0x8E);
	IdtSetGate(11, (unsigned long)Isr11, 0x8, 0x8E);
	IdtSetGate(12, (unsigned long)Isr12, 0x8, 0x8E);
	IdtSetGate(13, (unsigned long)Isr13, 0x8, 0x8E);
	IdtSetGate(14, (unsigned long)Isr14, 0x8, 0x8E);
	IdtSetGate(15, (unsigned long)Isr15, 0x8, 0x8E);
	IdtSetGate(16, (unsigned long)Isr16, 0x8, 0x8E);
	IdtSetGate(17, (unsigned long)Isr17, 0x8, 0x8E);
	IdtSetGate(18, (unsigned long)Isr18, 0x8, 0x8E);
	IdtSetGate(19, (unsigned long)Isr19, 0x8, 0x8E);
	IdtSetGate(20, (unsigned long)Isr20, 0x8, 0x8E);
	IdtSetGate(21, (unsigned long)Isr21, 0x8, 0x8E);
	IdtSetGate(22, (unsigned long)Isr22, 0x8, 0x8E);
	IdtSetGate(23, (unsigned long)Isr23, 0x8, 0x8E);
	IdtSetGate(24, (unsigned long)Isr24, 0x8, 0x8E);
	IdtSetGate(25, (unsigned long)Isr25, 0x8, 0x8E);
	IdtSetGate(26, (unsigned long)Isr26, 0x8, 0x8E);
	IdtSetGate(27, (unsigned long)Isr27, 0x8, 0x8E);
	IdtSetGate(28, (unsigned long)Isr28, 0x8, 0x8E);
	IdtSetGate(29, (unsigned long)Isr29, 0x8, 0x8E);
	IdtSetGate(30, (unsigned long)Isr30, 0x8, 0x8E);
	IdtSetGate(31, (unsigned long)Isr31, 0x8, 0x8E);
    
    // Setup the 15 IRQ handler
    IdtSetGate(32, (unsigned long)Irq0, 0x08, 0x8E);
    IdtSetGate(33, (unsigned long)Irq1, 0x08, 0x8E);
    IdtSetGate(34, (unsigned long)Irq2, 0x08, 0x8E);
    IdtSetGate(35, (unsigned long)Irq3, 0x08, 0x8E);
    IdtSetGate(36, (unsigned long)Irq4, 0x08, 0x8E);
    IdtSetGate(37, (unsigned long)Irq5, 0x08, 0x8E);
    IdtSetGate(38, (unsigned long)Irq6, 0x08, 0x8E);
    IdtSetGate(39, (unsigned long)Irq7, 0x08, 0x8E);
    IdtSetGate(40, (unsigned long)Irq8, 0x08, 0x8E);
    IdtSetGate(41, (unsigned long)Irq9, 0x08, 0x8E);
    IdtSetGate(42, (unsigned long)Irq10, 0x08, 0x8E);
    IdtSetGate(43, (unsigned long)Irq11, 0x08, 0x8E);
    IdtSetGate(44, (unsigned long)Irq12, 0x08, 0x8E);
    IdtSetGate(45, (unsigned long)Irq13, 0x08, 0x8E);
    IdtSetGate(46, (unsigned long)Irq14, 0x08, 0x8E);
    IdtSetGate(47, (unsigned long)Irq15, 0x08, 0x8E);
    
    // Loads the IDT table into the processor register (Assembler function)
    IdtFlush((unsigned long)&_idtPointer);
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