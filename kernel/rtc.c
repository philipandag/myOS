#include <rtc.h>

void init_rtc()
{
    asm("cli");
    //setting the registers
    outb(0x70, 0x8A);
    outb(0x71, 0x20);

    //turning on IRQ 8
    outb(0x70, 0x8B);
    char prev = inb(0x71);
    outb(0x70, 0x8B);
    outb(0x71, prev | 0b01000000);

    asm("sti");
}