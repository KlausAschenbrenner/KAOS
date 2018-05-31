#include "common.h"
#include "screen.h"

// Writes a single char (8 bytes) to the specified port.
void outb(unsigned short Port, unsigned char Value)
{
	asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}

// Reads a single char (8 bytes) from the specified port.
unsigned char inb(unsigned short Port)
{
   unsigned char ret;
   asm volatile("inb %1, %0" : "=a" (ret) : "dN" (Port));
   
   return ret;
}

// Reads a single short (16 bytes) from the specific port.
unsigned short inw(unsigned short Port)
{
   unsigned short ret;
   asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (Port));
   
   return ret;
}

// A simple memset implementation
void *memset(void *s, int c, long n)
{
    unsigned char *p = s;
    
    while (n--)
        *p++ = (unsigned char)c;
    
    return s;
}

// A simple memcpy implementation
void memcpy(void *dest, void *src, int len)
{
    int i;
    char *csrc = (char *)src;
    char *cdest = (char *)dest;

    for (i = 0; i < len; i++)
    {
        cdest[i] = csrc[i];
    }
}

// A simple strcmp implementation
int strcmp(char *s1, char *s2, int len)
{
    int i = 0;

    while (*s1 && (*s1 == *s2) && i < len)
    {
        s1++;
        s2++;
        i++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void strcpy(char *dest, char *src, int len)
{
    int i = 0;

    while (*dest++ = *src++ && i < len)
        i++;
}