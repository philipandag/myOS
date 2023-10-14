#include <stdlib.h>

// buf has to have at least 11 bytes of length
void uitoa(char* buf, unsigned int num)
{
    if(num == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }

    unsigned int n = num;
    int digits = 0;
    while(n > 0)
    {
        n /= 10;
        digits++;
    }

    for(int i = 0; i < digits; i++)
    {
        buf[digits-i-1] = '0' + (num % 10);
        num /= 10;
    }
    buf[digits] = '\0';
}