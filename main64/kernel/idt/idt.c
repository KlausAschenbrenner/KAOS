//
//  Idt.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "idt.h"
#include "../irq/irq.h"

// The 256 possible Interrupt Gates are stored from 0x8000 to 0x8FFF (4096 Bytes long - each Entry is 16 Bytes)
IdtEntry *_idtEntries = (IdtEntry *)IDT_START_OFFSET;

// The pointer that points to the Interrupt Gates
IdtPointer _idtPointer;

// Our generic ISR handler
void IsrHandler(int Number, unsigned long cr2)
{
    // We have triggered a Page Fault!
    if (Number == 14)
    {
        HandlePageFault(cr2);
        return;
    }
    else
    {
        char str[32] = "";
        itoa(Number, 16, str);

        printf("ISR: ");
        printf("0x");
        printf(str);

        // Halt the system
        for (;;);
    }
}

// Initializes the IDT table
void InitIdt()
{
    _idtPointer.Limit = sizeof(IdtEntry) * 256 - 1;
    _idtPointer.Base = (unsigned long)_idtEntries;
    memset(_idtEntries, 0, sizeof(IdtEntry) * 256);

    // Setup the 32 Exception handler
    IdtSetGate(0, (unsigned long)Isr0, 0xF);
    IdtSetGate(1, (unsigned long)Isr1, 0xF);
	IdtSetGate(2, (unsigned long)Isr2, 0xF);
	IdtSetGate(3, (unsigned long)Isr3, 0xF);
	IdtSetGate(4, (unsigned long)Isr4, 0xF);
	IdtSetGate(5, (unsigned long)Isr5, 0xF);
	IdtSetGate(6, (unsigned long)Isr6, 0xF);
	IdtSetGate(7, (unsigned long)Isr7, 0xF);
	IdtSetGate(8, (unsigned long)Isr8, 0xE);    // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(9, (unsigned long)Isr9, 0xF);
	IdtSetGate(10, (unsigned long)Isr10, 0xE);  // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(11, (unsigned long)Isr11, 0xE);  // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(12, (unsigned long)Isr12, 0xE);  // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(13, (unsigned long)Isr13, 0xE);  // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(14, (unsigned long)Isr14, 0xE);  // Interrupt Gate: Interrupts are disabled/enabled automatically!
	IdtSetGate(15, (unsigned long)Isr15, 0xF);
	IdtSetGate(16, (unsigned long)Isr16, 0xF);
	IdtSetGate(17, (unsigned long)Isr17, 0xF);
	IdtSetGate(18, (unsigned long)Isr18, 0xF);
	IdtSetGate(19, (unsigned long)Isr19, 0xF);
	IdtSetGate(20, (unsigned long)Isr20, 0xF);
	IdtSetGate(21, (unsigned long)Isr21, 0xF);
	IdtSetGate(22, (unsigned long)Isr22, 0xF);
	IdtSetGate(23, (unsigned long)Isr23, 0xF);
	IdtSetGate(24, (unsigned long)Isr24, 0xF);
	IdtSetGate(25, (unsigned long)Isr25, 0xF);
	IdtSetGate(26, (unsigned long)Isr26, 0xF);
	IdtSetGate(27, (unsigned long)Isr27, 0xF);
	IdtSetGate(28, (unsigned long)Isr28, 0xF);
	IdtSetGate(29, (unsigned long)Isr29, 0xF);
	IdtSetGate(30, (unsigned long)Isr30, 0xF);
	IdtSetGate(31, (unsigned long)Isr31, 0xF);

    // Setup the 15 IRQ handler
    IdtSetGate(32, (unsigned long)Irq0, 0xE);
    IdtSetGate(33, (unsigned long)Irq1, 0xE);
    IdtSetGate(34, (unsigned long)Irq2, 0xE);
    IdtSetGate(35, (unsigned long)Irq3, 0xE);
    IdtSetGate(36, (unsigned long)Irq4, 0xE);
    IdtSetGate(37, (unsigned long)Irq5, 0xE);
    IdtSetGate(38, (unsigned long)Irq6, 0xE);
    IdtSetGate(39, (unsigned long)Irq7, 0xE);
    IdtSetGate(40, (unsigned long)Irq8, 0xE);
    IdtSetGate(41, (unsigned long)Irq9, 0xE);
    IdtSetGate(42, (unsigned long)Irq10, 0xE);
    IdtSetGate(43, (unsigned long)Irq11, 0xE);
    IdtSetGate(44, (unsigned long)Irq12, 0xE);
    IdtSetGate(45, (unsigned long)Irq13, 0xE);
    IdtSetGate(46, (unsigned long)Irq14, 0xE);
    IdtSetGate(47, (unsigned long)Irq15, 0xE);

    // Loads the IDT table into the processor register (Assembler function)
    IdtFlush((unsigned long)&_idtPointer);
}

// Installs the corresponding ISR routine in the IDT table
void IdtSetGate(unsigned char num, unsigned long base, unsigned char Type)
{
    _idtEntries[num].OffsetLow = (unsigned short)base & 0xFFFF;
    _idtEntries[num].Selector = 0x8;
    _idtEntries[num].Type = Type;
    _idtEntries[num].OffsetMiddle = (unsigned short)((base >> 16) & 0xFFFF);
    _idtEntries[num].OffsetHigh = (unsigned int)((base >> 32) & 0xFFFFFFFF);
    _idtEntries[num].Reserved1 = 0;
    _idtEntries[num].Reserved2 = 0;
    _idtEntries[num].InterruptStackTable = 0;
    _idtEntries[num].DPL = 0;
    _idtEntries[num].Present = 1;
    _idtEntries[num].Reserved3 = 0;
}