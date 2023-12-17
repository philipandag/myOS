#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mylib.h>

#include <tty.h>
#include <idt.h>
#include <gdt.h>
#include <pic.h>
#include <ps2.h>
#include <rtc.h>


extern void* _interrupt_ignore;
uint64_t* GDT;
uint64_t* IDT;


void printDescriptor(uint64_t* descriptor)
{
    printf("Base       : %x\n", GDTGetBase(descriptor));
    printf("Limit      : %x\n", GDTGetLimit(descriptor));
    printf("Access Byte: %x\n", GDTGetAccessByte(descriptor));
    printf("Flags      : %x\n", GDTGetFlags(descriptor));

    return;
}

void printGate(uint64_t* gate)
{
    printf("Offset:     : %x\n", IDTGetOffset(gate));
    printf("Selector:   : %x\n", IDTGetSelector(gate));
    printf("Parameters: : %x\n", IDTGetAttributes(gate));
}


void configuration()
{
    // Saving pointers to gdt and idt to use in C code
    asm("mov $GDT_Pointer, %[G]\t\n"
        "mov $IDT_Pointer, %[I]"
        :[I]"=r" (IDT), [G]"=r" (GDT)
    );
    printf("GDT and IDT - OK\n");

    PIC_remap(IRQ1_Offset, IRQ2_Offset);
    PIC_clear_mask(0); // PIT timer
    PIC_clear_mask(1); // PS/2 keyboard
    // PIC_clear_mask(8); // RTC(Real Time Clock)
    printf("PIC - OK\n");

    init_ps2();
    //init_rtc();

    printf("Config succeeded!\n\n");
}

void kernel_main()
{
    //terminal_initialize(); // its already called as early as in boot.asm to enable debug messages

    configuration();

    for(int i = 0;; i += 1)
    {
        //printf("%d: Hello, kernel World!\n", i);
        //waitTicks(-1000);
        //asm("int $33"); // causes keyboard interrupt
    }

}