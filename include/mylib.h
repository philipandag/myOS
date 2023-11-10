#ifndef _MYLIB_H
#define _MYLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif



// Waits for AT LEAST amount of processor ticks. Most processors work at over a couble GHz, so 1mld ticks is often less than a second.
void waitTicks(unsigned int amount);
void printDword(uint32_t value);



#ifdef __cplusplus
}
#endif

#endif