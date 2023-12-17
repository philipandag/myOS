#ifndef GDT_H
#define GDT_H GDT_H

#include <stddef.h>
#include <stdint.h>

#define  GDT_ACCESS_BYTE_A_1        0b00000001
#define  GDT_ACCESS_BYTE_A_0        0b00000000
#define  GDT_ACCESS_BYTE_RW_0       0b00000000
#define  GDT_ACCESS_BYTE_RW_1       0b00000010
#define  GDT_ACCESS_BYTE_DC_1       0b00000100
#define  GDT_ACCESS_BYTE_DC_0       0b00000000
#define  GDT_ACCESS_BYTE_E_1        0b00001000
#define  GDT_ACCESS_BYTE_E_0        0b00000000
#define  GDT_ACCESS_BYTE_S_0        0b00000000
#define  GDT_ACCESS_BYTE_DPL_3      0b01100000
#define  GDT_ACCESS_BYTE_S_1        0b00010000
#define  GDT_ACCESS_BYTE_DPL_0      0b00000000
#define  GDT_ACCESS_BYTE_P_1        0b10000000
#define  GDT_ACCESS_BYTE_P_0        0b00000000
#define  GDT_SYSTEM_ACCESS_BYTE_TYPE      0b00001111
#define  GDT_SYSTEM_ACCESS_BYTE_S_1       0b00010000
#define  GDT_SYSTEM_ACCESS_BYTE_S_0       0b00000000
#define  GDT_SYSTEM_ACCESS_BYTE_DPL_3     0b01100000
#define  GDT_SYSTEM_ACCESS_BYTE_DPL_0     0b00000000
#define  GDT_SYSTEM_ACCESS_BYTE_P_1       0b10000000
#define  GDT_SYSTEM_ACCESS_BYTE_P_0       0b00000000
#define  GDT_FLAGS_L_1      0b10
#define  GDT_FLAGS_L_0      0b00
#define  GDT_FLAGS_DB_1     0b100
#define  GDT_FLAGS_DB_0     0b000
#define  GDT_FLAGS_G_1      0b1000
#define  GDT_FLAGS_G_0      0b0000


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

uint32_t GDTGetBase(const uint64_t* descriptor);
uint32_t GDTGetLimit(const uint64_t* descriptor);
uint8_t GDTGetAccessByte(const uint64_t* descriptor);
uint8_t GDTGetFlags(const uint64_t* descriptor);

#endif