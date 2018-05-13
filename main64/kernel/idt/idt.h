//
//  idt.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_idt_h
#define KAOS_idt_h

// Represents an Interrupt Gate - 128 Bit long
struct IdtEntry
{
    unsigned short OffsetLow;       // 16 Bit
    unsigned short Selector;        // 16 Bit
    unsigned Ist: 3;                // Interrupt Stack Table - 3 Bits
    unsigned:5;                     // Reserved - 5 Bits
    unsigned Type: 4;               // Type - 4 Bits
    unsigned: 1;                    // 1 Bit
    unsigned Dpl: 2;                // DPL - 2 Bit
    unsigned P: 1;                  // 1 Bit
    unsigned short OffsetMiddle;    // 16 Bit
    unsigned int OffsetHigh;        // 32 Bit
    unsigned int Reserved;          // 32 Bit
} __attribute__ ((packed));
typedef struct IdtEntry IdtEntry;

// Represents the pointer to the interrupt gates
struct IdtPointer
{
    unsigned short Limit;
    unsigned long Base;
} __attribute((packed));
typedef struct IdtPointer IdtPointer;

// Installs the corresponding ISR routine in the IDT table
static void IdtSetGate(unsigned char num, unsigned int base);

// Initializes the IDT table for the ISR routines.
void InitIdt();

// Loads the IDT table into the processor register (implemented in Assembler)
extern void IdtFlush(unsigned long);

// Our 32 ISR routines (implemented in Assembler)
extern void Isr0();
extern void Isr1();
extern void Isr2();
extern void Isr3();
extern void Isr4();
extern void Isr5();
extern void Isr6();
extern void Isr7();
extern void Isr8();
extern void Isr9();
extern void Isr10();
extern void Isr11();
extern void Isr12();
extern void Isr13();
extern void Isr14();
extern void Isr15();
extern void Isr16();
extern void Isr17();
extern void Isr18();
extern void Isr19();
extern void Isr20();
extern void Isr21();
extern void Isr22();
extern void Isr23();
extern void Isr24();
extern void Isr25();
extern void Isr26();
extern void Isr27();
extern void Isr28();
extern void Isr29();
extern void Isr30();
extern void Isr31();

#endif
