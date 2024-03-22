#include "string.h"
#include "stdio.h"
#include <stdint.h>

size_t strlen( const char* str ){
    const char *s;
    for (s = str; *s; ++s);
    return (s - str);
}

char* strcpy( char* dest, const char* src ){
    if(dest == NULL){
        puts(" strcpy dest is null !!");
        return NULL;
    }
    if(src == NULL){
        puts(" strcpy src is null !!");
        return NULL;
    }
    char *temp = dest;
    while(*dest++ = *src++); // or while((*strDest++=*strSrc++) != '\0');
    return temp;
}

int memcmp( const void* lhs, const void* rhs, size_t len ){

    if(lhs == NULL){
        puts(" memcmp lhs is null");
        return -1;
    }
    if(rhs == NULL){
        puts(" memcmp rhs is null");
        return -1;
    }

    if(lhs == rhs){ return 0;}

    unsigned char *p = lhs;
    unsigned char *q = rhs;

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

//TODO: probaly wrong ret value prev was val
void* memset(void *dest, int val, size_t len) {
     if(dest == NULL){
        puts(" memset dest is null !!");
        return NULL;
    }
    
    unsigned char *dst = dest;
    while (len > 0) {
        *dst = (unsigned char) val;
        dst++;
        len--;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t len){
     if(dest == NULL){
        puts(" memcpy dest is null !!");
        return NULL;
    }
    if(src == NULL){
        puts(" memcpy src is null !!");
        return NULL;
    }

    uint8_t *pdest = (uint8_t*) dest;
    uint8_t *psrc = (uint8_t*) src;

    int loops = (len / sizeof(uint32_t));
    for(int index = 0; index < loops; ++index)
    {
        *((uint32_t*)pdest) = *((uint32_t*)psrc);
        pdest += sizeof(uint32_t);
        psrc += sizeof(uint32_t);
    }

    loops = (len % sizeof(uint32_t));
    for (int index = 0; index < loops; ++index)
    {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
    }
}