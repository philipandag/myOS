#include <io.h>

char inb(unsigned short port)
{
    unsigned char data;
    asm volatile (
    "in %[p], %[d]\t\n"
    : [d] "=a" (data)
    : [p] "d" (port));

    return data;
}

void outb(unsigned short port, unsigned char data)
{
    asm volatile (
    "out %[d], %[p]\t\n"
    : 
    : [p] "d" (port), [d] "a" (data));
}