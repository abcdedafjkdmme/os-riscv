#include "string.h"
#include "stdio.h"
#include <stdint.h>
#include <assert.h>

size_t strlen( const char* str ){
    assert(str != NULL);

    const char *s;
    for (s = str; *s; ++s);

    assert(s >= str);

    return (size_t)(s - str);
}

char* strcpy( char* dest, const char* src ){
    assert(dest != NULL);
    assert(src != NULL);

    char *temp = dest;
    while((*dest++ = *src++) != '\0'); // or while((*strDest++=*strSrc++) != '\0');
    return temp;
}

int memcmp( const void* lhs, const void* rhs, size_t len ){

    assert(lhs != NULL);
    assert(rhs != NULL);

    if(lhs == rhs){ return 0;}

    const unsigned char *p = lhs;
    const unsigned char *q = rhs;

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
    assert(dest != NULL);
    
    unsigned char *dst = dest;
    while (len > 0) {
        *dst = (unsigned char) val;
        dst++;
        len--;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t len){
    assert(dest != NULL);
    assert(src != NULL);

    uint8_t *pdest = (uint8_t*) dest;
    uint8_t *psrc = (uint8_t*) src;

    size_t loops = (len / sizeof(uint32_t));
    for(size_t index = 0; index < loops; ++index)
    {
        *((uint32_t*)pdest) = *((uint32_t*)psrc);
        pdest += sizeof(uint32_t);
        psrc += sizeof(uint32_t);
    }

    loops = (len % sizeof(uint32_t));
    for (size_t index = 0; index < loops; ++index)
    {
        *pdest = *psrc;
        ++pdest;
        ++psrc;
    }
    return dest;
}

int strncmp(const char* lhs, const char* rhs, size_t len){
    assert(lhs != NULL);
    assert(rhs != NULL);
    
    while ( len && *lhs && ( *lhs == *rhs ) )
    {
        ++lhs;
        ++rhs;
        --len;
    }
    if ( len == 0 )
    {
        return 0;
    }
    else
    {
        return ( *(unsigned char *)lhs - *(unsigned char *)rhs );
    }
}
