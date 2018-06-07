#ifndef COMMON_H
#define COMMON_H

#define CRLF "\n"
#define TAB "\t"

// Represents the registers that are passed as a parameter to our ISR/IRQ function
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
void *memset(void *s, int c, long n);

// Writes a single char (8 bytes) to the specified port.
void outb(unsigned short Port, unsigned char Value);

// Reads a single char (8 bytes) from the specified port.
unsigned char inb(unsigned short Port);

// Reads a single short (16 bytes) from the specific port.
unsigned short inw(unsigned short Port);

#endif