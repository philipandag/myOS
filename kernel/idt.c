#include "pic.h"
#include <idt.h>
#include <string.h>
#include <stdint.h>
#include <tty.h>
#include <mylib.h>

#include <interrupts.h>

void IDTSetOffset(uint64_t* gateDescriptor, uint32_t offset)
{
    uint64_t upperPart = (offset & 0xFFFF0000) >> 4*4;
    uint64_t lowerPart = offset & 0x0000FFFF;

    // clear bytes 0-15 for lower part
    *gateDescriptor &= 0xFFFFFFFFFFFF0000;
    // set bytes
    *gateDescriptor |= lowerPart;

    //cleat bytes 48-63 for upper part
    *gateDescriptor &= 0x0000FFFFFFFFFFFF;
    // set bytes
    *gateDescriptor |= (upperPart << 48);

}

void IDTSetSelector(uint64_t* gateDescriptor, uint16_t selector)
{
    *gateDescriptor &= 0xFFFFFFFF0000FFFF;
    *gateDescriptor |= ((uint64_t)selector << 4*4);
}

void IDTSetAttributes(uint64_t* gateDescriptor, uint8_t attributes)
{
    attributes &= 0b11101111; // making sure one reserved byte is not set
    *gateDescriptor &= 0xFFFF00FFFFFFFFFF;
    *gateDescriptor |= ((uint64_t)attributes << 40); 
}
void IDTSetP(uint64_t* gateDescriptor, uint8_t p);


uint64_t IDTCreateGateDescriptor(uint32_t offset, uint16_t selector, uint8_t attributes)
{
    uint64_t gate = 0;
    IDTSetOffset(&gate, offset);
    IDTSetSelector(&gate, selector);
    IDTSetAttributes(&gate, attributes);

    return gate;
}


void IDTCreate(void* IDTStart)
{
    const int IDT_SIZE = 256;
    uint64_t IDT[IDT_SIZE];
    int IRQ1_Offset, IRQ2_Offset;
    asm volatile (
        "mov IRQ1_Offset, %0"
        : "=r" (IRQ1_Offset)
    );
    asm volatile (
        "mov IRQ2_Offset, %0"
        : "=r" (IRQ2_Offset)
    );


    int interrupt_ignore_offset;
    asm volatile (
        "mov $_interrupt_ignore, %0"
        : "=r" (interrupt_ignore_offset)
    );

    int interrupt_print_int_offset;
    asm volatile (
        "mov $_interrupt_print_int, %0"
        : "=r" (interrupt_print_int_offset)
    );

    int interrupt_13_general_protection_fault_offset;
    asm volatile (
        "mov $_interrupt_13_general_protection_fault, %0"
        : "=r" (interrupt_13_general_protection_fault_offset)
    );

    int interrupt_IRQ_ignore_offset;
    asm volatile (
        "mov $_interrupt_IRQ_ignore, %0"
        : "=r" (interrupt_IRQ_ignore_offset)
    );

    int interrupt_IRQ_0_offset;
    asm volatile (
        "mov $_interrupt_IRQ_0, %0"
        : "=r" (interrupt_IRQ_0_offset)
    );
    int interrupt_IRQ_1_offset;
    asm volatile (
        "mov $_interrupt_IRQ_1, %0"
        : "=r" (interrupt_IRQ_1_offset)
    );
    int interrupt_IRQ_8_offset;
    asm volatile (
        "mov $_interrupt_IRQ_8, %0"
        : "=r" (interrupt_IRQ_8_offset)
    );

    // 0-31 Reserved Protected Mode Exceptions
    // 8-15 default mapping of IRQ0-7 by the BIOS at bootstrap
    // 70h-78h = 112-120 default mapping of IRQ8-15 by the BIOS at bootstrap

    int attributes = IDT_DPL_0 | IDT_GATE_TYPE_32b_INTERRUPT | IDT_P_1;
    // filling with ignores for now
    for(int i = 0; i < 32; i++)   
        IDT[i] = IDTCreateGateDescriptor(interrupt_ignore_offset, 0x08, attributes);

    for(int i = 32; i < 256; i++)
        IDT[i] = IDTCreateGateDescriptor(interrupt_ignore_offset, 0x08, attributes);
    

    // filling IRQ gates for now
    for(int i = IRQ1_Offset; i < IRQ1_Offset+8; i++)
        IDT[i] = IDTCreateGateDescriptor(interrupt_IRQ_ignore_offset, 0x08, attributes);
    for(int i = IRQ2_Offset; i < IRQ2_Offset+2; i++)
        IDT[i] = IDTCreateGateDescriptor(interrupt_IRQ_ignore_offset, 0x08, attributes);
   
    // Keyboard interrupt
    IDT[IRQ1_Offset + 0] = IDTCreateGateDescriptor(interrupt_IRQ_0_offset, 0x08, attributes);
    IDT[IRQ1_Offset + 1] = IDTCreateGateDescriptor(interrupt_IRQ_1_offset, 0x08, attributes);
    IDT[IRQ1_Offset + 8] = IDTCreateGateDescriptor(interrupt_IRQ_8_offset, 0x08, attributes);
    IDT[IRQ1_Offset + 13] = IDTCreateGateDescriptor(interrupt_13_general_protection_fault_offset, 0x08, attributes);


    // IRQ8-15 at 78-85

    memcpy(IDTStart, &IDT, IDT_SIZE * sizeof(uint64_t));
}

uint32_t IDTGetOffset(const uint64_t* gateDescriptor)
{
    uint32_t upperPart = (*gateDescriptor & 0xFFFF000000000000) >> 8*4;
    uint32_t lowerPart = (*gateDescriptor & 0x000000000000FFFF);

    return lowerPart | upperPart;
}

uint16_t IDTGetSelector(const uint64_t* gateDescriptor)
{
    return (*gateDescriptor & 0x00000000FFFF0000) >> 4*4;
}

uint8_t IDTGetAttributes(const uint64_t* gateDescriptor)
{
    return (*gateDescriptor & 0x0000FF0000000000) >> 4*10;
}