#include <stdlib.h>

static const char* symbols = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char* itoa(int value, char* destination, int base)
{
    const int MAX_BASE = 36; // destinationlen(symbols)
    const int MIN_BASE = 2;

    // Preventing unsupported bases from being used
    if (base < MIN_BASE)
        base = MIN_BASE;
    if (base > MAX_BASE)
        base = MAX_BASE;

    // value=0 is a special case
    if (value == 0)
    {
        destination[0] = '0';
        destination[1] = '\0';
        return destination;
    }

    // for negative values add '-' sign and write the number as a positive after '-' sign
    if (value < 0)
    {
        destination[0] = '-';
        return itoa(-value, destination+1, base);
    }

    // main conversion
    int characters_stored = 0;
    while(value > 0)
    {
        destination[characters_stored++] = symbols[value % base];
        value /= base;
    }

    // Now the number is stored backwards, we need to reverse it
    // It could be prevented by calculating the amount of characters the number would take
    // and writing it backwards starting from there, but i doubt it would be faster
    // reverse number destinationing
    for(int i = 0; i < characters_stored/2; i++)
    {
        int temp = destination[i];
        destination[i] = destination[characters_stored-i-1];
        destination[characters_stored-i-1] = temp;
    }

    // ending the destinationing properly
    destination[characters_stored] = '\0';

    return destination;
}

char* ltoa(long value, char* destination, int base)
{
    const int MAX_BASE = 36; // destinationlen(symbols)
    const int MIN_BASE = 2;

    // Preventing unsupported bases from being used
    if (base < MIN_BASE)
        base = MIN_BASE;
    if (base > MAX_BASE)
        base = MAX_BASE;

    // value=0 is a special case
    if (value == 0)
    {
        destination[0] = '0';
        destination[1] = '\0';
        return destination;
    }

    // for negative values add '-' sign and write the number as a positive after '-' sign
    if (value < 0)
    {
        destination[0] = '-';
        return ltoa(-value, destination+1, base);
    }

    // main conversion
    int characters_stored = 0;
    while(value > 0)
    {
        destination[characters_stored++] = symbols[value % base];
        value /= base;
    }

    // Now the number is stored backwards, we need to reverse it
    // It could be prevented by calculating the amount of characters the number would take
    // and writing it backwards starting from there, but i doubt it would be faster
    // reverse number destinationing
    for(int i = 0; i < characters_stored/2; i++)
    {
        int temp = destination[i];
        destination[i] = destination[characters_stored-i-1];
        destination[characters_stored-i-1] = temp;
    }

    // ending the destinationing properly
    destination[characters_stored] = '\0';

    return destination;
}

char* lltoa(long long value, char* destination, int base)
{
    const int MAX_BASE = 36; // destinationlen(symbols)
    const int MIN_BASE = 2;

    // Preventing unsupported bases from being used
    if (base < MIN_BASE)
        base = MIN_BASE;
    if (base > MAX_BASE)
        base = MAX_BASE;

    // value=0 is a special case
    if (value == 0)
    {
        destination[0] = '0';
        destination[1] = '\0';
        return destination;
    }

    // for negative values add '-' sign and write the number as a positive after '-' sign
    if (value < 0)
    {
        destination[0] = '-';
        return ltoa(-value, destination+1, base);
    }

    // main conversion
    int characters_stored = 0;
    while(value > 0)
    {
        destination[characters_stored++] = symbols[value % base];
        value /= base;
    }

    // Now the number is stored backwards, we need to reverse it
    // It could be prevented by calculating the amount of characters the number would take
    // and writing it backwards starting from there, but i doubt it would be faster
    // reverse number destinationing
    for(int i = 0; i < characters_stored/2; i++)
    {
        int temp = destination[i];
        destination[i] = destination[characters_stored-i-1];
        destination[characters_stored-i-1] = temp;
    }

    // ending the destinationing properly
    destination[characters_stored] = '\0';

    return destination;
}