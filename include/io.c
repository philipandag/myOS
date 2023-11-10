#include <io.h>

char inb(int port)
{
    char ret;
    asm("in %[p]\t\n"
        "mov %al, $[a1]"
    :[a1] "=r" (ret)
    :[p] "r" (port));

    return ret;
}

void outb(int port, char byte)
{
    asm("out %[p], %[i]\t\n"
        :
        :[p] "r" (port)), [i] "r" (byte));
}