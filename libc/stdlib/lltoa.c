#include <stdlib.h>

char* lltoa(long long value, char* str, int base)
{
    char* symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int MAX_BASE = 36; // strlen(symbols)
    const int MIN_BASE = 2;

    // Preventing unsupported bases from being used
    if (base < MIN_BASE)
        base = MIN_BASE;
    if (base > MAX_BASE)
        base = MAX_BASE;

    // value=0 is a special case
    if (value == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    // for negative values add '-' sign and write the number as a positive after '-' sign
    if (value < 0)
    {
        str[0] = '-';
        return ltoa(-value, str+1, base);
    }

    // main conversion
    int characters_stored = 0;
    while(value > 0)
    {
        str[characters_stored++] = symbols[value % base];
        value /= base;
    }

    // Now the number is stored backwards, we need to reverse it
    // It could be prevented by calculating the amount of characters the number would take
    // and writing it backwards starting from there, but i doubt it would be faster
    // reverse number string
    for(int i = 0; i < characters_stored/2; i++)
    {
        int temp = str[i];
        str[i] = str[characters_stored-i-1];
        str[characters_stored-i-1] = temp;
    }

    // ending the string properly
    str[characters_stored] = '\0';

    return str;
}