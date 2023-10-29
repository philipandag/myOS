#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static bool print(const char* data, size_t length){
    const unsigned char* bytes = (const unsigned char*) data;
    for(size_t i = 0; i < length; i++)
        if(putchar(bytes[i]) == EOF)
            return false;
    return true;
}

int printf(const char* restrict format, ...){
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while(*format != '\0'){
        size_t maxrem = INT_MAX - written;

        if(format[0] != '%' || format[1] == '%'){
            if(format[0] == '%')
                format++;
            size_t amount = 1;
            while(format[amount] && format[amount] != '%')
                amount++;
            
            if(maxrem < amount){
                //TODO: Set errno to EOVERFLOW.
                return -1;
            }

            if(!print(format, amount))
                return -1;
            
            format += amount;
            written += amount;
            continue;
        }

        const char* format_begun_at = format++;

        if(*format == 'c'){
            format++;
            char c = (char) va_arg(parameters, int /* char promotes to int */);
            if(!maxrem){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(&c, sizeof(c)))
                return -1;
            written++;

        } else if(*format == 's'){
            format++;
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(str, len))
                return -1;
            written += len;

        } else if (*format == 'd') { // TODO: make it signed
            format++;
            const int num = va_arg(parameters, const int);
            char buf[11]; // INT_MAX is 10 digits in base 10 4294967296
            buf[10] = '\0';
            itoa(num, buf, 10);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else if(*format == 'l' && *(format+1) == 'd') {
            format += 2;
            const long long num = va_arg(parameters, const long);
            char buf[20]; // 2^64 is 19 digits in base 10 9223372036854775807
            buf[19] = '\0';
            ltoa(num, buf, 10);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else if(*format == 'l' && *(format+1) == 'l' && *(format+2) == 'd') {
            format += 3;
            const long long num = va_arg(parameters, const long long);
            char buf[20]; // 2^64 is 19 digits in base 10 9223372036854775807
            buf[19] = '\0';
            lltoa(num, buf, 10);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else if(*format == 'x') {
            format++;
            const int num = va_arg(parameters, const int);
            char buf[9]; // INT_MAX is 8 digits in base 16 FFFFFFFF
            buf[10] = '\0';
            itoa(num, buf, 16);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else if(*format == 'l' && *(format+1) == 'x') {
            format += 2;
            const long num = va_arg(parameters, const long);
            char buf[17]; // 2^64 is 16 digits in base 16 FFFFFFFFFFFFFFFF
            buf[16] = '\0';
            ltoa(num, buf, 16);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else if(*format == 'l' && *(format+1) == 'l' && *(format+2) == 'x') {
            format += 3;
            const long long num = va_arg(parameters, const long long);
            char buf[17]; // 2^64 is 16 digits in base 16 FFFFFFFFFFFFFFFF
            buf[16] = '\0';
            lltoa(num, buf, 16);
            size_t len = strlen(buf);
            if(maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(buf, len))
                return -1;
            written += len;

        } else {
            format = format_begun_at;
            size_t len = strlen(format);
            if (maxrem < len){
                // TODO: Set errno to EOVERFLOW.
                return -1;
            }
            if(!print(format, len))
                return -1;
            written += len;
            format += len;
        }
        // TODO: Add more formats
    }

    va_end(parameters);
    return written;
}