#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <mylib.h>

#include <tty.h>

//extern void _load_gdt(void*, int, int, int);
// extern void* _load_gdt;
// extern void* _start;
// extern void* _KERNEL_BEGINNING;
// void printDescriptor(uint64_t* descriptor)
// {
//     printf("Base       : %x\n", GDTGetBase(descriptor));
//     printf("Limit      : %x\n", GDTGetLimit(descriptor));
//     printf("Access Byte: %x\n", GDTGetAccessByte(descriptor));
//     printf("Flags      : %x\n", GDTGetFlags(descriptor));

//     return;
// }

void kernel_main(){
    terminal_initialize();

    // printf("%ld: Null Descriptor\n", GDT[0]);
    // printDescriptor(&GDT[0]);
    // printf("%lld: Kernel Mode Code Segment\n", GDT[1]);
    // printDescriptor(&GDT[1]);
    // printf("%lld: Kernel Mode Data Segment\n", GDT[2]);
    // printDescriptor(&GDT[2]);
    // printf("%lld: User Mode Data Segment\n", GDT[3]);
    // printDescriptor(&GDT[3]);
    // printf("%lld: User Mode Data Segment\n", GDT[4]);
    // printDescriptor(&GDT[4]);
    // printf("Start function: %x\n", _start);
    // printf("load_gdt pointer: %x\n", _load_gdt);
    for(int i = 0;; i += 1)
    {
        printf("%d: Hello, kernel World!\n", i);
        waitTicks(-1000);
    }

}