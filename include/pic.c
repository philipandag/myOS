#include <pic.h>
#include <stdint.h>
#include <io.h>

void PIC_remap(int offsetMaster, int offsetSlave)
{
    unsigned char a1, a2;

    a1 = inb(PIC1_COMMAND);

    //a2 = inb(PIC2_COMMAND);
    asm("in %[p]\t\n"
        "mov %al, $[a1]"
        :[a1] "=r" (a2)
        :[p] "r" (PIC2_COMMAND));

    
    //outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    asm("out %[p], %[i]\t\n"
        :
        :[p] "r" (PIC1_COMMAND)), [i] "r" (ICW1_INIT | ICW1_ICW4));

    //outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    asm("out %[p], %[i]\t\n"
        :
        :[p] "r" (PIC2_COMMAND)), [i] "r" (ICW1_INIT | ICW1_ICW4));

    //outb(PIC1_DATA, offsetMaster);
    asm("out %[p], %[i]\t\n"
        :
        :[p] "r" (PIC1_DATA), [i] "r" (offsetMaster));

    //outb(PIC2_DATA, offsetSlave);
    asm("out %[p], %[i]\t\n"
        :
        :[p] "r" (PIC2_DATA), [i] "r" (offsetSlave));


    //outb(PIC1_DATA, 4);
    asm("out %[p], $4\t\n"
        :
        :[p] "r" (PIC1_DATA));
    //outb(PIC2_DATA, 2);
    asm("out %[p], $2\t\n"
        :
        :[p] "r" (PIC2_DATA));

    //outb(PIC1_DATA, ICW4_8086);
    asm("out %[p], $[i]\t\n"
        :
        :[p] "r" (PIC1_DATA), [i] "r" (ICW4_8086));
    //outb(PIC2_DATA, ICW4_8086);
    asm("out %[p], $[i]\t\n"
        :
        :[p] "r" (PIC2_DATA), [i] "r" (ICW4_8086));

    //outb(PIC1_DATA, a1);
    asm("out %[p], $[i]\t\n"
        :
        :[p] "r" (PIC1_DATA), [i] "r" (a1));
    //outb(PIC2_DATA, a2);
    asm("out %[p], $[i]\t\n"
        :
        :[p] "r" (PIC2_DATA), [i] "r" (ICW4_8086));

}

void PIC_set_mask(unsigned char IRQLine)
{
    uint16_t port;
    uint8_t value;

    if(IRQLine < 8){
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQLine -= 8;
    }

    //value = inb(port) | (1 << IRQLine);
    asm("in %[p]\t\n"
        "mov %al, $[a1]"
        :[a1] "=r" (a1)
        :[p] "r" (PIC1_COMMAND));
    outb(port, value);
}

void PIC_clear_mask(unsigned char IRQLine)
{
    uint16_t port;
    uint8_t value;

    if(IRQLine < 8){
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQLine -= 8;
    }

    value = inb(port) & -(1 << IRQLine);
    outb(port, value);
}
