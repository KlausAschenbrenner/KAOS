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

// A simple strcpy implementation
void strcpy(char *dest, char *src, int len)
{
    int i = 0;

    while (*dest++ = *src++ && i < len)
        i++;
}

// A "simple" Sleep implementation
void Sleep(int Count)
{
	int i;
	for (i = 0; i < Count; i++) {}
}

char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

// Converts an ASCII string to its integer value
int atoi(char *str)
{
    int res = 0;
    int i;

    for (i = 0; str[i] != '\0'; ++i)
    {
        res = res * 10 + str[i] - '0';
    }

    return res;
}

int atoi_len(char *str, int len)
{
    int res = 0;
    int i;

    for (i = 0; i < len; ++i)
    {
        res = res * 10 + str[i] - '0';
    }

    return res;
}

// Converts an integer value to a string value for a specific base (base 10 => decimal, base 16 => hex)
void itoa(int i, unsigned base, char *buf)
{
    if (base > 16) return;
    
    if (i < 0)
    {
        *buf++ = '-';
        i *= -1;
    }
    
    itoa_s(i, base, buf);
}

void itoa_s(unsigned short i, unsigned base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    
    if (i == 0 || base > 16)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    
    while (i != 0)
    {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    
    top = pos--;
    
    for (opos = 0; opos < top; pos--,opos++)
    {
        buf[opos] = tbuf[pos];
    }
    
    buf[opos] = 0;
}

static void ltoa_s(unsigned long i, unsigned base, char *buf)
{
    int pos = 0;
    int opos = 0;
    int top = 0;
    
    if (i == 0 || base > 16)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    
    while (i != 0)
    {
        tbuf[pos] = bchars[i % base];
        pos++;
        i /= base;
    }
    
    top = pos--;
    
    for (opos = 0; opos < top; pos--,opos++)
    {
        buf[opos] = tbuf[pos];
    }
    
    buf[opos] = 0;
}

// Converts a long value to a string value for a specific base (base 10 => decimal, base 16 => hex)
void ltoa(unsigned long i, unsigned base, char *buf)
{
    if (base > 16) return;
    
    if (i < 0)
    {
        *buf++ = '-';
        i *= -1;
    }
    
    ltoa_s(i, base, buf);
}