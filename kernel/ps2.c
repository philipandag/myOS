#include <ps2.h>
#include <io.h>
#include <stdio.h>

extern void _init_ps2(void);


/*To send a command to the controller, write the command byte to IO port 0x64. 
If there is a "next byte" (the command is 2 bytes) then the next byte needs to 
be written to IO Port 0x60 after making sure that the controller is ready for it 
(by making sure bit 1 of the Status Register is clear). 
If there is a response byte, then the response byte needs to be read 
from IO Port 0x60 after making sure it has arrived 
(by making sure bit 0 of the Status Register is set). */

// 1. out command to 0x64 COMMAND
// 2. in result from 0x60 DATA

void ps2_output_ready()
{
    unsigned char ack = 0;
    while((ack & 0b00000001) != 1)
    {
        ack = inb(COMMAND);
    }
}
void ps2_ready_for_input()
{
    unsigned char ack = 0xFFFF;
    while((ack & 0b00000010) != 0)
    {
        ack = inb(COMMAND);
    }
}

void init_ps2()
{
    //_init_ps2();
    asm("cli");

    // disable first and second ps2 device
    outb(COMMAND, 0xAD);
    outb(COMMAND, 0xA7);

    // flush ps2 buffer
    unsigned char buf = inb(DATA);

    // read controller configuration byte
    outb(COMMAND, 0x20); // Read "byte 0" from internal RAM
    ps2_output_ready();
    unsigned char conf_byte = inb(DATA);

    // write configuration byte to console debug
    //printf("PS/2 initial config: 0x%x\n", conf_byte);

    // write new configuration byte to controller
    // disable IRQs (0, 1) and translation (6)
    conf_byte &= 0b10111100;

    // set new configuration byte
    outb(COMMAND, 0x60); 
    ps2_ready_for_input();
    outb(DATA, conf_byte);

    // controller self test
    outb(COMMAND, 0xAA);
    ps2_output_ready();
    // get self test result
    unsigned char result = inb(DATA);
    if (result != 0x55)
    {
        printf("PS/2 Controller didn't pass self test!\n");
    }
    //printf("PS/2 Controller self test passed!\n");

    //interface tests
    outb(COMMAND, 0xAB);
    ps2_output_ready();
    result = inb(DATA);
    if (result != 0)
    {
        printf("PS/2 device 1 didn't pass interface test!\n");
    }
    //printf("PS/2 device 1 test passed!\n");
    
    // second ps2 port
    // outb(COMMAND, 0xA9);
    // ps2_output_ready();
    // result = inb(DATA);
    // if (result != 0)
    // {
    //     printf("PS/2 device 2 didn't pass interface test!\n");
    // }

    // enable devices back
    outb(COMMAND, 0xAE);
    //outb(COMMAND, 0xA8);

    // enable IRQs (0, 1) and translation (6)
    conf_byte |= 0b01000011;
    // set new configuration byte
    outb(COMMAND, 0x60); 
    ps2_ready_for_input();
    outb(DATA, conf_byte);

    // read controller configuration byte
    outb(COMMAND, 0x20); // Read "byte 0" from internal RAM
    ps2_output_ready();
    // write configuration byte to console debug
    conf_byte = inb(DATA);
    //printf("PS/2 new config: 0x%x\n", conf_byte);


    //reset device 1
    int counter = 10000; // after this many tries we declare the device offline
    for(int i = 0; i < counter; i++)
    {
        result = inb(COMMAND);
        if ((result & 0b0000010) == 0)
        {
            outb(DATA, 0xFF); // reset command
            ps2_output_ready();
            result = inb(DATA);
            if (result == 0xFA)
                {}
            else if (result == 0xFC)
                printf("DEVICE 1 RESET FAILURE!\n");
            else
                printf("DEVICE 1 RESET UNKNOWN! %c\n", result);
            break;
        }
    }

    asm("sti");

    // while(1)
    // {
    //     result = inb(COMMAND) & 0b1;
    //     if(result)
    //     {
    //         buf = inb(DATA);
    //         terminal_putchar(buf);
    //     }
    // }
    


    //asm("sti");

}

#define SCAN_CODES_AMOUNT 197 
static const unsigned char scan_code_to_ascii[] = {
     0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's',
    'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 39, '`', 0, 92, 'z', 'x', 'c', 'v',
    'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, 0, 0, 0, 0, '+',
    0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char scan_code_to_char(unsigned char code)
{
    if(code > SCAN_CODES_AMOUNT)
        return 0;
    return scan_code_to_ascii[code];
}
