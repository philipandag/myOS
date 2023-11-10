#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mylib.h>

#include <tty.h>
#include <idt.h>
#include <gdt.h>

extern void* _interrupt_ignore;

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


void kernel_main()
{
    uint64_t* GDT, IDT;
    asm("mov $GDT_Pointer, %[G]\t\n"
        "mov $IDT_Pointer, %[I]"
        :[I]"=r" (IDT), [G]"=r" (GDT)
    );
    printf("IDT: %x\n GDT: %x\n", IDT, GDT);

    terminal_initialize();

    for(int i = 0;; i += 1)
    {
        printf("%d: Hello, kernel World!\n", i);
        waitTicks(-1000);
        asm("int $69");
    }

}