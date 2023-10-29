#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

// Converts int to string array
// value - number to be converted
// str - buffer in which value converted to string will be stored
// base - base of number system into which the value should be converted, for example 2, 8, 10 or 16
char* itoa(int value, char* str, int base);

// Converts long long to string array
// value - number to be converted
// str - buffer in which value converted to string will be stored
// base - base of number system into which the value should be converted, for example 2, 8, 10 or 16
char* ltoa(long long value, char* str, int base); 

#ifdef __cplusplus
}
#endif

#endif
