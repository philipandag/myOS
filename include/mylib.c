#include <stddef.h>
#include <stdint.h>
#include <mylib.h>
#include <tty.h>
#include <stdlib.h>
void waitTicks(unsigned int amount)
{
    //printf("waitTicks: %d\n", amount);
    size_t start;

    size_t msr;
    asm volatile(
        "rdtsc\n\t"
        "mov %%eax, %[out]"
        : [out] "=r" (msr)
        :
        : "eax"
    );
    start = msr;

    //printf("msr: %d, start: %d\n", msr, start);
    while(msr-start < (size_t)amount)
    {
        asm volatile(
        "rdtsc\n\t"
        "mov %%eax, %[out]"
        : [out] "=r" (msr)
        :
        : "eax"
        );
    }


}
void printDword(uint32_t value)
{
    char buff[16];
    uitoa(value, buff, 16);
    terminal_writestring(buff);
    return;
}