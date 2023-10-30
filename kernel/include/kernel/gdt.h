#ifndef GDT_H
#define GDT_H

#include <stddef.h>
#include <stdint.h>

const int GDT_ACCESS_BYTE_A_BIT =   0b00000001;
const int GDT_ACCESS_BYTE_RW_BIT =  0b00000010;
const int GDT_ACCESS_BYTE_DC_BIT =  0b00000100;
const int GDT_ACCESS_BYTE_E_BIT =   0b00001000;
const int GDT_ACCESS_BYTE_S_BIT =   0b00010000;
const int GDT_ACCESS_BYTE_DPL =     0b01100000;
const int GDT_ACCESS_BYTE_P_BIT =   0b10000000;

const int GDT_SYSTEM_ACCESS_BYTE_TYPE = 0b00001111;
const int GDT_SYSTEM_ACCESS_BYTE_S =    0b00010000;
const int GDT_SYSTEM_ACCESS_BYTE_DPL =  0b01100000;
const int GDT_SYSTEM_ACCESS_BYTE_P =    0b10000000;

const int GDT_FLAGS_L = 0b10;
const int GDT_FLAGS_DB = 0b100;
const int GDT_FLAGS_G = 0b1000;


// base is stored in two parts on bits:
// 16-39(24 bits), 56-63(8 bits) - total 32 bits
void GDTSetBase(uint64_t* descriptor, uint32_t base);

// limit is stored in two parts on bits:
// 0-15(16 bits), 48-51(4 bits) - total 20 bits
void GDTSetLimit(uint64_t* descriptor, uint32_t limit);

// Access byte stored on bits 40-47
void GDTSetAccessByte(uint64_t* descriptor, uint8_t accessByte);

// flags stored on bits 52-55
void GDTSetFlags(uint64_t* descriptor, uint8_t flags);

uint64_t GDTCreateDescriptor(uint32_t base, uint32_t limit, uint8_t accessByte, uint8_t flags);


void GDTCreate(void* GDTStart);

uint32_t GDTGetBase(uint64_t* descriptor);
uint32_t GDTGetLimit(uint64_t* descriptor);
uint8_t GDTGetAccessByte(uint64_t* descriptor);
uint8_t GDTGetFlags(uint64_t* descriptor);

#endif
