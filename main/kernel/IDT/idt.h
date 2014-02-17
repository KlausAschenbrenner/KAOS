//
//  idt.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_idt_h
#define KAOS_idt_h

// Represents an interrupt gate
struct IdtEntry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__ ((packed));
typedef struct IdtEntry IdtEntry;

// Represents the pointer to the interrupt gates
struct IdtPointer
{
    unsigned short limit;
    unsigned int base;
} __attribute((packed));
typedef struct IdtPointer IdtPointer;

// Represents the registers that are passed as a parameter to our ISR function
typedef struct InterruptRegisters
{
    unsigned int ds;
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
    unsigned int InterruptNumber;
    unsigned int ErrorCode;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
    unsigned int useresp;
    unsigned int ss;
} InterruptRegisters;

// A simple memset function
static void *memset(void *s, int c, long n);

// Installs the corresponding ISR routine in the IDT table
static void IdtSetGate(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags);

// Initializes the IDT table for the ISR routines.
void InitIdt();

// Loads the IDT table into the processor register (implemented in Assembler)
extern void IdtFlush(unsigned int);

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
