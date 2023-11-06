#ifndef _STRING_H
#define _STRING_H 1
 
#include <sys/cdefs.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif



int memcmp(const void* string1, const void* string2, size_t length);

void* memcpy(void* destination, const void* source, size_t length);

void* memmove(void* destination, const void* source, size_t length);

void* memset(void* string, int value, size_t length);

size_t strlen(const char* string);



#ifdef __cplusplus
}
#endif
 
#endif