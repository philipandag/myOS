#include <idt.h>
#include <string.h>
#include <stdint.h>

extern int _interrupt_ignore;

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

    // 0-31 Reserved Protected Mode Exceptions
    // 8-15 default mapping of IRQ0-7 by the BIOS at bootstrap
    // 70h-78h = 112-120 default mapping of IRQ8-15 by the BIOS at bootstrap

    // filling with ignores for now
    for(int i = 0; i < 64; i++)
    {
        IDT[i] = IDTCreateGateDescriptor(_interrupt_ignore, 0x08, 
            IDT_DPL_0 | IDT_GATE_TYPE_32b_INTERRUPT | IDT_P_1
        );
    }


    

    memcpy(IDTStart, &IDT, IDT_SIZE * sizeof(uint64_t));
}

uint32_t IDTGetOffset(const uint64_t* gateDescriptor)
{
    uint32_t upperPart = (*gateDescriptor & 0x0000FFFF00000000) >> 4*8;
    uint32_t lowerPart = (*gateDescriptor & 0x000000000000FFFF);

    return lowerPart | upperPart;
}

uint16_t IDTGetSelector(const uint64_t* gateDescriptor)
{
    return *gateDescriptor & 0x00000000FFFF0000;
}

uint8_t IDTGetAttributes(const uint64_t* gateDescriptor)
{
    return *gateDescriptor & 0x0000FF0000000000;
}