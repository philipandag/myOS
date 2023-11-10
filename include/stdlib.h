#ifndef _STDLIB_H
#define _STDLIB_H 1
 
#include <sys/cdefs.h>
 
#ifdef __cplusplus
extern "C" {
#endif



 
__attribute__((__noreturn__))
void abort(void);

char* itoa(int value, char* destination, int base);
char* ltoa(long value, char* destination, int base);
char* lltoa(long long value, char* destination, int base);
char* uitoa(unsigned int value, char* destinatino, int base);
char* ulltoa(unsigned long long value, char* destination, int base);



 
#ifdef __cplusplus
}
#endif
 
#endif