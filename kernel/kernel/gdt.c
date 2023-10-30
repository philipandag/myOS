#include <kernel/gdt.h>
#include <string.h>

void GDTSetBase(uint64_t* descriptor, uint32_t base){
    uint64_t upperPart = base & 0xFF000000;
    uint64_t lowerPart = base & 0x00FFFFFF;

    // clear bytes 63-56     <8>56
    *descriptor &= 0x00FFFFFFFFFFFFFF;
    // set bytes 63-56 to upper part
    *descriptor |= upperPart << 32;

    // clear bytes 39-16     24<24>16
    *descriptor &= 0xFFFFFF000000FFFF;
    // set bytes 39-16 to lower part
    *descriptor |= lowerPart << 16;
}

void GDTSetLimit(uint64_t* descriptor, uint32_t limit)
{
    //make sure limit is 20 bytes
    limit &= 0x000FFFFF;

    uint64_t upperPart = limit & 0x000F0000;
    uint64_t lowerPart = limit & 0x0000FFFF;

    // clear bytes 51-48    12<4>48
    *descriptor &= 0b1111111111110000111111111111111111111111111111111111111111111111;
    // set bytes 51-48 to upper part
    *descriptor |= upperPart << 48;

    // clear bytes 39-16     48<16>
    *descriptor &= 0xFFFFFFFFFFFF0000;
    // set bytes 39-16 to lower part
    *descriptor |= lowerPart;
}

void GDTSetAccessByte(uint64_t* descriptor, uint8_t accessByte)
{
    // clear bytes 40-40=7 16<8>40
    *descriptor &= 0xFFFF00FFFFFFFFFF;
    // set bytes 40-47 to access byte
    *descriptor |= ((uint64_t)accessByte) << 40;
}

void GDTSetFlags(uint64_t* descriptor, uint8_t flags)
{
    // make sure uppermost 4 bits of flags variable are zeroed, dont want 
    // to use only 4 lower bits
    flags &= 0x00FF;

    //clear bytes 52-55 8<4>52
    *descriptor &= 0xFF0FFFFFFFFFFFFF;
    // set bytes 52-55 to flags
    *descriptor |= ((uint64_t)flags) << 52;
}

uint32_t GDTGetBase(uint64_t* descriptor)
{
    uint64_t upperPart = 0;
    uint64_t lowerPart = 0;

    // extracting upper and lower part by reversing what's done in
    // GDTSetBase
    upperPart = (*descriptor & 0xFF00000000000000) >> 4*8;
    lowerPart = (*descriptor & 0x000000FFFFFF0000) >> 4*4; 

    return lowerPart | upperPart;
}

uint32_t GDTGetLimit(uint64_t* descriptor)
{
    uint64_t upperPart = 0;
    uint64_t lowerPart = 0;

    upperPart = (*descriptor & 0x000FF000000000) >> 4*5;
    lowerPart = (*descriptor & 0x0000000000FFFF);
    
    return lowerPart | upperPart;
}

uint8_t GDTGetAccessByte(uint64_t* descriptor)
{
    return (*descriptor & 0x0000FF0000000000) >> 4*10;
}

uint8_t GDTGetFlags(uint64_t* descriptor)
{
    return (*descriptor & 0x00F0000000000000) >> 4*13;
}

uint64_t GDTCreateDescriptor(uint32_t base, uint32_t limit, uint8_t accessByte, uint8_t flags)
{
    uint64_t descriptor;
    GDTSetBase(&descriptor, base);
    GDTSetLimit(&descriptor, limit);
    GDTSetAccessByte(&descriptor, accessByte);
    GDTSetFlags(&descriptor, flags);
    return descriptor;
}

void GDTCreate(void* GDTStart)
{
    const int GDT_SIZE = 5;
    uint64_t GDT[GDT_SIZE];
    // Null Descriptor
    GDT[0] = GDTCreateDescriptor(
        0,
        0,
        0,
        0
    );
    // Kernel Mode Code Segment
    GDT[1] = GDTCreateDescriptor(
        0,
        0xFFFFF,
        0x9A,
        0xC
    );
    // Kernel Mode Data Segment
    GDT[2] = GDTCreateDescriptor(
        0,
        0xFFFFF,
        0x92,
        0xC
    );
    // User Mode Code Segment
    GDT[3] = GDTCreateDescriptor(
        0,
        0xFFFFF,
        0xFA,
        0xC
    );
    // User Mode Data Segment
    GDT[4] = GDTCreateDescriptor(
        0,
        0xFFFFF,
        0xF2,
        0xC
    );
    // Task State Segment, useful for task switching, not needed for now
    // GDT[5] = GDTCreateDescriptor(
    //     0,
    //     0xFFFFF,
    //     0xF2,
    //     0xC
    // );

    //copy GDT from stack to destination
    memcpy(GDTStart, &GDT, GDT_SIZE * sizeof(uint64_t));
}