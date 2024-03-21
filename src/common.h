#pragma once

#include <stdint.h>

static int oct_str_to_int(unsigned char *str, int size)
{
    int n = 0;
    unsigned char *c = str;
    while (size-- > 0)
    {
        n *= 8;
        n += *c - '0';
        c++;
    }
    return n;
}

static int uint16_to_oct_str(uint16_t num, char* str, size_t str_size)
{
    if(str_size < 7){
        return -1;
    }

    int index = 0;
    int octal_digit = 0;

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
    return 0;

}