#ifndef COMMON_H
#define COMMON_H

// Writes a single char (8 bytes) to the specified port.
void outb(unsigned short Port, unsigned char Value);

// Reads a single char (8 bytes) from the specified port.
unsigned char inb(unsigned short Port);

// Reads a single short (16 bytes) from the specific port.
unsigned short inw(unsigned short Port);

#endif