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
IdtEntry *_idtEntries = 0x8000;

// The pointer that points to the Interrupt Gates
IdtPointer _idtPointer;

// Our generic ISR handler
void IsrHandler(int Number, int cr2)
{
    if (Number == 14)
    {
        char str[32] = "";
        itoa(cr2, 16, str);
        
        // We have triggered a Page Fault!
        printf("Page Fault occurred while accessing virtual address 0x");
        printf(str);
    }
    else
    {
        char str[32] = "";
        itoa(Number, 16, str);

        printf("ISR: ");
        printf("0x");
        printf(str);
    }

    // Halt the system
    for (;;);
}

// Initializes the IDT table
void InitIdt()
{
    _idtPointer.Limit = sizeof(IdtEntry) * 256 - 1;
    _idtPointer.Base = (unsigned long)_idtEntries;
    memset(_idtEntries, 0, sizeof(IdtEntry) * 256);

    // Setup the 32 Exception handler
    IdtSetGate(0, (unsigned long)Isr0);
    IdtSetGate(1, (unsigned long)Isr1);
	IdtSetGate(2, (unsigned long)Isr2);
	IdtSetGate(3, (unsigned long)Isr3);
	IdtSetGate(4, (unsigned long)Isr4);
	IdtSetGate(5, (unsigned long)Isr5);
	IdtSetGate(6, (unsigned long)Isr6);
	IdtSetGate(7, (unsigned long)Isr7);
	IdtSetGate(8, (unsigned long)Isr8);
	IdtSetGate(9, (unsigned long)Isr9);
	IdtSetGate(10, (unsigned long)Isr10);
	IdtSetGate(11, (unsigned long)Isr11);
	IdtSetGate(12, (unsigned long)Isr12);
	IdtSetGate(13, (unsigned long)Isr13);
	IdtSetGate(14, (unsigned long)Isr14);
	IdtSetGate(15, (unsigned long)Isr15);
	IdtSetGate(16, (unsigned long)Isr16);
	IdtSetGate(17, (unsigned long)Isr17);
	IdtSetGate(18, (unsigned long)Isr18);
	IdtSetGate(19, (unsigned long)Isr19);
	IdtSetGate(20, (unsigned long)Isr20);
	IdtSetGate(21, (unsigned long)Isr21);
	IdtSetGate(22, (unsigned long)Isr22);
	IdtSetGate(23, (unsigned long)Isr23);
	IdtSetGate(24, (unsigned long)Isr24);
	IdtSetGate(25, (unsigned long)Isr25);
	IdtSetGate(26, (unsigned long)Isr26);
	IdtSetGate(27, (unsigned long)Isr27);
	IdtSetGate(28, (unsigned long)Isr28);
	IdtSetGate(29, (unsigned long)Isr29);
	IdtSetGate(30, (unsigned long)Isr30);
	IdtSetGate(31, (unsigned long)Isr31);

    // Setup the 15 IRQ handler
    IdtSetGate(32, (unsigned long)Irq0);
    IdtSetGate(33, (unsigned long)Irq1);
    IdtSetGate(34, (unsigned long)Irq2);
    IdtSetGate(35, (unsigned long)Irq3);
    IdtSetGate(36, (unsigned long)Irq4);
    IdtSetGate(37, (unsigned long)Irq5);
    IdtSetGate(38, (unsigned long)Irq6);
    IdtSetGate(39, (unsigned long)Irq7);
    IdtSetGate(40, (unsigned long)Irq8);
    IdtSetGate(41, (unsigned long)Irq9);
    IdtSetGate(42, (unsigned long)Irq10);
    IdtSetGate(43, (unsigned long)Irq11);
    IdtSetGate(44, (unsigned long)Irq12);
    IdtSetGate(45, (unsigned long)Irq13);
    IdtSetGate(46, (unsigned long)Irq14);
    IdtSetGate(47, (unsigned long)Irq15);

    // Loads the IDT table into the processor register (Assembler function)
    IdtFlush((unsigned long)&_idtPointer);
}

// Installs the corresponding ISR routine in the IDT table
void IdtSetGate(unsigned char num, unsigned int base)
{
    _idtEntries[num].OffsetLow = (unsigned short)base & 0xFFFF;
    _idtEntries[num].Selector = 0x8;
    _idtEntries[num].Ist = 0;
    _idtEntries[num].Type = 0xF;
    _idtEntries[num].P = 1;
    _idtEntries[num].OffsetMiddle = (unsigned short)((base >> 16) & 0xFFFF);
    // _idtEntries[num].OffsetHigh = (unsigned int)((base >> 32) & 0xFFFFFFFF);
    _idtEntries[num].OffsetHigh = 0;
    _idtEntries[num].Reserved = 0;
}