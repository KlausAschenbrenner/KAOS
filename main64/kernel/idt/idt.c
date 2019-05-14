//
//  Idt.c
//  KAOS
//
//  Created by Klaus Aschenbrenner on 17.02.2014.
//  Copyright (c) 2014 Klaus Aschenbrenner. All rights reserved.
//

#include "idt.h"
#include "../drivers/common.h"
#include "../irq/irq.h"
#include "../ui/window.h"

extern int UIMode;

// The 256 possible Interrupt Gates are stored from 0x98000 to 0x98FFF (4096 Bytes long - each Entry is 16 Bytes)
IdtEntry *_idtEntries = (IdtEntry *)IDT_START_OFFSET;

// The pointer that points to the Interrupt Gates
IdtPointer _idtPointer;

// Our generic ISR handler
void IsrHandler(int Number, unsigned long cr2, RegisterState *Registers)
{
    // We have triggered a Page Fault!
    if (Number == 14)
    {
        HandlePageFault(cr2);
        return;
    }
    else
    {
        if (UIMode == 0)
        {
            // We are running in text mode
            DisplayException(Number, Registers);
        }
        else
        {
            // We are running with a GUI
            DisplayBlueScreen(Number, Registers);
        }
        
        // Halt the system
        for (;;);
    }
}

void DisplayException(int Number, RegisterState *Registers)
{
    printf("A fatal error has occured!\n");
    printf("ISR: 0x");
    printf_int(Number, 16);
    printf("\n");

    printf("RIP: 0x");
    printf_long(Registers->RIP, 16);
    printf("\n");

    printf("RDI: 0x");
    printf_long(Registers->RDI, 16);
    printf("\n");

    printf("RSI: 0x");
    printf_long(Registers->RSI, 16);
    printf("\n");

    printf("RBP: 0x");
    printf_long(Registers->RBP, 16);
    printf("\n");

    printf("RSP: 0x");
    printf_long(Registers->RSP, 16);
    printf("\n");

    printf("RAX: 0x");
    printf_long(Registers->RAX, 16);
    printf("\n");

    printf("RBX: 0x");
    printf_long(Registers->RBX, 16);
    printf("\n");

    printf("RCX: 0x");
    printf_long(Registers->RCX, 16);
    printf("\n");

    printf("RDX: 0x");
    printf_long(Registers->RDX, 16);
    printf("\n");

    printf("R8:  0x");
    printf_long(Registers->R8, 16);
    printf("\n");

    printf("R9:  0x");
    printf_long(Registers->R9, 16);
    printf("\n");

    printf("R10: 0x");
    printf_long(Registers->R10, 16);
    printf("\n");

    printf("R11: 0x");
    printf_long(Registers->R11, 16);
    printf("\n");

    printf("R12: 0x");
    printf_long(Registers->R12, 16);
    printf("\n");

    printf("R13: 0x");
    printf_long(Registers->R13, 16);
    printf("\n");

    printf("R14: 0x");
    printf_long(Registers->R14, 16);
    printf("\n");

    printf("R15: 0x");
    printf_long(Registers->R15, 16);
    printf("\n");
}

// Displays a blue screen with the occured exception
void DisplayBlueScreen(int Number, RegisterState *Registers)
{   
    char str[32] = "";
    itoa(Number, 16, str);

    // Fill the whole display with a blue color
    Context *context = NewContext(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FRAME_BUFFER, WINDOW_FRAME_BUFFER);;
    Context_FillRect(context, 0, 0, context->Width, context->Height, 0x025B);
    DrawString(context, "A fatal has error occured! ", 10, 10, 0xFFFF);
    DrawString(context, "ISR: 0x", 10, 26, 0xFFFF);
    DrawString(context, str, 66, 26, 0xFFFF);

    ltoa(Registers->RIP, 16, str);
    DrawString(context, "RIP: 0x", 10, 42, 0xFFFF);
    DrawString(context, str, 66, 42, 0xFFFF);

    ltoa(Registers->RDI, 16, str);
    DrawString(context, "RDI: 0x", 10, 58, 0xFFFF);
    DrawString(context, str, 66, 58, 0xFFFF);

    ltoa(Registers->RSI, 16, str);
    DrawString(context, "RSI: 0x", 10, 74, 0xFFFF);
    DrawString(context, str, 66, 74, 0xFFFF);

    ltoa(Registers->RBP, 16, str);
    DrawString(context, "RBP: 0x", 10, 90, 0xFFFF);
    DrawString(context, str, 66, 90, 0xFFFF);

    ltoa(Registers->RSP, 16, str);
    DrawString(context, "RSP: 0x", 10, 106, 0xFFFF);
    DrawString(context, str, 66, 106, 0xFFFF);

    ltoa(Registers->RAX, 16, str);
    DrawString(context, "RAX: 0x", 10, 122, 0xFFFF);
    DrawString(context, str, 66, 122, 0xFFFF);

    ltoa(Registers->RBX, 16, str);
    DrawString(context, "RBX: 0x", 10, 138, 0xFFFF);
    DrawString(context, str, 66, 138, 0xFFFF);

    ltoa(Registers->RCX, 16, str);
    DrawString(context, "RCX: 0x", 10, 154, 0xFFFF);
    DrawString(context, str, 66, 154, 0xFFFF);

    ltoa(Registers->RDX, 16, str);
    DrawString(context, "RDX: 0x", 10, 170, 0xFFFF);
    DrawString(context, str, 66, 170, 0xFFFF);

    ltoa(Registers->R8, 16, str);
    DrawString(context, "R8:  0x", 10, 186, 0xFFFF);
    DrawString(context, str, 66, 186, 0xFFFF);

    ltoa(Registers->R9, 16, str);
    DrawString(context, "R9:  0x", 10, 202, 0xFFFF);
    DrawString(context, str, 66, 202, 0xFFFF);

    ltoa(Registers->R10, 16, str);
    DrawString(context, "R10: 0x", 10, 218, 0xFFFF);
    DrawString(context, str, 66, 218, 0xFFFF);

    ltoa(Registers->R11, 16, str);
    DrawString(context, "R11: 0x", 10, 234, 0xFFFF);
    DrawString(context, str, 66, 234, 0xFFFF);

    ltoa(Registers->R12, 16, str);
    DrawString(context, "R12: 0x", 10, 250, 0xFFFF);
    DrawString(context, str, 66, 250, 0xFFFF);

    ltoa(Registers->R13, 16, str);
    DrawString(context, "R13: 0x", 10, 266, 0xFFFF);
    DrawString(context, str, 66, 266, 0xFFFF);

    ltoa(Registers->R14, 16, str);
    DrawString(context, "R14: 0x", 10, 282, 0xFFFF);
    DrawString(context, str, 66, 282, 0xFFFF);

    ltoa(Registers->R15, 16, str);
    DrawString(context, "R15: 0x", 10, 298, 0xFFFF);
    DrawString(context, str, 66, 298, 0xFFFF);

    ltoa(GetHeapEndOffset(), 16, str);
    DrawString(context, "Heap 0x", 10, 314, 0xFFFF);
    DrawString(context, str, 66, 314, 0xFFFF);

    // Produce a Stack Trace
    StackTrace(context);
}

// Produces a Stack Trace
void StackTrace(Context *context)
{
    char str[32] = "";
    StackFrame *frame;
    int pos = 346;

    // Get the current RBP value
    asm volatile("mov %%rbp, %0" : "=r" (frame));
    DrawString(context, "Stack Trace:", 10, pos, 0xFFFF);
    pos += 16;

    // Walk the Stack
    while (frame != 0x0)
    {
        ltoa(frame->rip, 16, str);
        DrawString(context, "RIP: 0x", 10, pos, 0xFFFF);
        DrawString(context, str, 66, pos, 0xFFFF);
        frame = frame->rbp;
        pos += 16;
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

    // The INT 0x80 can be raised from Ring 3
    IdtSetGate(128, (unsigned long)SysCallHandlerAsm, 0xE);
    _idtEntries[128].DPL = 3;

    // Loads the IDT table into the processor register (Assembler function)
    IdtFlush((unsigned long)&_idtPointer);
}

// Installs the IRQ0 interrupt handler that performs the Context Switching between the various tasks
void InitTimerForContextSwitching()
{
    IdtSetGate(32, (unsigned long)Irq0_ContextSwitching, 0xE);

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