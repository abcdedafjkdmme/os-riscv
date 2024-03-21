#include "string.h"
#include "stdio.h"

size_t strlen( const char* str ){
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}

char* strcpy( char* dest, const char* src ){
    if(dest == NULL){
        puts("strcpy dest is null !!");
        return NULL;
    }
    if(src == NULL){
        puts("strcpy src is null !!");
        return NULL;
    }
    char *temp = dest;
    while(*dest++ = *src++); // or while((*strDest++=*strSrc++) != '\0');
    return temp;
}

int memcmp( const void* lhs, const void* rhs, size_t count ){
     unsigned char *p = b;
    unsigned char *q = c;

    while (len > 0)
    {
        if (*p != *q)
            return (*p - *q);
        len--;
        p++;
        q++;
    }
    return 0;
}