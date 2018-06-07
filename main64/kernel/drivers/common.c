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

int strlen(char *string)
{
    int len = 0;

    while (*string != '\0')
	{
		len++;
        string++;
	}

    return len;
}

char tbuf[64];
char tbuf_long[64];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

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

static void itoa_s(unsigned i, unsigned base, char *buf)
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