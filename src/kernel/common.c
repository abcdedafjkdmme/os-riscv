#include "common.h"
#include <assert.h>

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.
 */
char* itoa(int value, char* result, int base) {
    assert(result != NULL);
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
  
    // Reverse the string
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

int oct_str_to_int(const unsigned char *str, int size)
{
    assert(str != NULL);

    int n = 0;
    const unsigned char *c = str;
    while (size-- > 0 && (*c != '\0'))
    {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

void uint16_to_oct_str(uint16_t num, char *str, size_t size)
{

    assert(str != NULL);
    assert(size > 7);

    int index = 0;

    // Convert to octal
    do
    {
        str[index++] = '0' + (num & 7);
        num >>= 3;
    } while (num);

    str[index] = '\0';

    // Reverse the string
    int i, j;
    char temp;
    for (i = 0, j = index - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    

   /*
    size_t ofs;

    int value = 0;
    for (ofs = 0; ofs < size; ofs++)
    {
        char c = str[ofs];
        if (c >= '0' && c <= '7')
        {
            if (value > (-1) / 8)
            {
                puts("u16 to oct overflow");
            }
            value = c - '0' + value * 8;
        }
        else if (c == ' ' || c == '\0')
        {
            // End of field, but disallow completely empty fields. 
            puts("u16 to oct end of field");
            return value;
        }

        else
        {
            //Bad character
            puts("u16 to oct bad char");
        }
    }

    // Field did not end in space or null byte.
    return value;

    */

}
