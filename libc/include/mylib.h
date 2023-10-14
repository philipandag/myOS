#ifndef _MYLIB_H
#define _MYLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

void uitoa(char* buf, unsigned int num);
// Waits for AT LEAST amount of processor ticks. Most processors work at over a couble GHz, so 1mld ticks is often less than a second.
void waitTicks(unsigned int amount);

#ifdef __cplusplus
}
#endif

#endif
