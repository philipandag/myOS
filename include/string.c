#include <string.h>

int memcmp(const void* str1, const void* str2, size_t n)
{
    const char* s1 = (const char*)str1;
    const char* s2 = (const char*)str2;
    for(size_t i = 0; i < n; i++)
    {
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return 1;
    }
    return 0;
}

void* memcpy(void* dest, const void* src, size_t n)
{
    char* d = (char*) dest;
    const char* s = (char*) src;
    
    for(size_t i = 0; i < n; i++)
        d[i] = s[i];

    return dest;
}

void* memmove(void* destination, const void* source, size_t length)
{
    unsigned char* dst = (unsigned char*) destination;
	const unsigned char* src = (const unsigned char*) source;
	if (dst < src) 
    {
		for (size_t i = 0; i < length; i++)
			dst[i] = src[i];
	} 
    else 
    {
		for (size_t i = length; i != 0; i--)
			dst[i-1] = src[i-1];
	}
	return destination;
}

size_t strlen(const char* string)
{
    size_t len = 0;
	while (string[len])
		len++;
	return len;
}

void* memset(void* destination, int value, size_t length) {
	unsigned char* buf = (unsigned char*) destination;
	for (size_t i = 0; i < length; i++)
		buf[i] = (unsigned char) value;
	return destination;
}


