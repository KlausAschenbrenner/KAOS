//
//  idt.h
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#ifndef KAOS_idt_h
#define KAOS_idt_h

#define IDT_START_OFFSET 0x98000

// Represents an Interrupt Gate - 128 Bit long
struct _IdtEntry
{
    unsigned short OffsetLow;           // 16 Bit
    unsigned short Selector;            // 16 Bit
    unsigned InterruptStackTable : 3;
    unsigned Reserved1 : 5;
    unsigned Type : 4;
    unsigned Reserved2 : 1;
    unsigned DPL : 2;
    unsigned Present : 1;
    unsigned short OffsetMiddle;        // 16 Bit
    unsigned int OffsetHigh;            // 32 Bit
    unsigned int Reserved3;             // 32 Bit
} __attribute__ ((packed));
typedef struct _IdtEntry IdtEntry;

typedef struct _RegisterState
{
    unsigned long RIP;
    unsigned long ErrorCode;
    unsigned long RDI;
    unsigned long RSI;
    unsigned long RBP;
    unsigned long RSP;
    unsigned long RBX;
    unsigned long RDX;
    unsigned long RCX;
    unsigned long RAX;
    unsigned long R8;
    unsigned long R9;
    unsigned long R10;
    unsigned long R11;
    unsigned long R12;
    unsigned long R13;
    unsigned long R14;
    unsigned long R15;
} RegisterState;

// Represents the pointer to the interrupt gates
struct _IdtPointer
{
    unsigned short Limit;
    unsigned long Base;
} __attribute((packed));
typedef struct _IdtPointer IdtPointer;

// Represents a x64 Stack Frame
typedef struct _StackFrame
{
    struct StackFrame *rbp;
    unsigned long rip;
} StackFrame;

// Installs the corresponding ISR routine in the IDT table
void IdtSetGate(unsigned char num, unsigned long base, unsigned char Type);

// Initializes the IDT table for the ISR routines.
void InitIdt();

// Installs the IRQ0 interrupt handler that performs the Context Switching between the various tasks
void InitTimerForContextSwitching();

// Loads the IDT table into the processor register (implemented in Assembler)
extern void IdtFlush(unsigned long);

// Handles the INT 0x80 SysCall
extern void SysCallHandlerAsm();

// Produces a Stack Trace
void StackTrace();

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