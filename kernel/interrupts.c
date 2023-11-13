#include <interrupts.h>

#include <io.h>
#include <pic.h>
#include <ps2.h>
#include <tty.h>
#include <stdio.h>
#include <stdlib.h>
#include <vga.h>
#include <rtc.h>
#include <string.h>

void __IRQ0()
{
    terminal_writestring_at("Filip G 188776", 0, VGA_HEIGHT-2);

    // Writing system time
    
    outb(0x70, 0x0C); // select RTC register C
    inb(0x71); // read type of interrupt, ignore value

    char disable_nmi = 0x80; // 0x80
    outb(0x70, disable_nmi | 0x00); // seconds
    int seconds = BCD2BIN(inb(0x71));

    outb(0x70, disable_nmi | 0x02); // minutes
    int minutes = BCD2BIN(inb(0x71));

    outb(0x70, disable_nmi | 0x04); // hours
    int hours = BCD2BIN(inb(0x71));


    // those ugly ifs are there to make 
    char buffer [32];
    uitoa(hours, buffer, 10);
    if(buffer[1] == '\0')
    {
        buffer[1] = buffer[0];
        buffer[0] = ' ';
    }
    buffer[2] = ':';

    uitoa(minutes, buffer+3, 10);

    if(buffer[4] == '\0')
    {
        buffer[4] = buffer[3];
        buffer[3] = '0';
    }

    buffer[5] = ':';
    uitoa(seconds, buffer+6, 10);
    if(buffer[7] == '\0')
    {
        buffer[7] = buffer[6];
        buffer[6] = '0';
    }
    buffer[8] = '\0';

    terminal_writestring_at(buffer, 0, VGA_HEIGHT-1);
}

void __IRQ1()
{
    char byte = inb(DATA);
    //printf("Keyboard interrupt! (%c)\n", byte);
    terminal_putchar(scan_code_to_char(byte));
}

void __IRQ8()
{
   
}