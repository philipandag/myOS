#ifndef IDT_H
#define IDT_H IDT_H

#include <stddef.h>
#include <stdint.h>

const int IDT_GATE_TYPE_TASK =           0b0101;
const int IDT_GATE_TYPE_16b_INTERRUPT =  0b0110;
const int IDT_GATE_TYPE_16b_TRAP =       0b0111;
const int IDT_GATE_TYPE_32b_INTERRUPT =  0b1110;
const int IDT_GATE_TYPE_32b_TRAP =       0b1111;

const int IDT_DPL_3 =   0b1100000;
const int IDT_DPL_0 =   0b0000000;
const int IDT_P_1 =     0b10000000;
const int IDT_P_0 =     0b00000000;



// base is stored in two parts on bits:
// 16-39(24 bits), 56-63(8 bits) - total 32 bits
void IDTSetOffset(uint64_t* gateDescriptor, uint32_t offset);
void IDTSetSelector(uint64_t* gateDescriptor, uint16_t selector);
void IDTSetAttributes(uint64_t* gateDescriptor, uint8_t attributes);

uint64_t IDTCreateGateDescriptor(uint32_t offset, uint16_t selector, uint8_t attributes);


void IDTCreate(void* IDTStart);

uint32_t IDTGetOffset(const uint64_t* gateDescriptor);
uint16_t IDTGetSelector(const uint64_t* gateDescriptor);
uint8_t IDTGetAttributes(const uint64_t* gateDescriptor);

#endif