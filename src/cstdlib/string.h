#pragma once
#include <stddef.h>

size_t strlen( const char* str );
char* strcpy( char* dest, const char* src );
int strncmp(const char* lhs, const char* rhs, size_t len);
int memcmp( const void* lhs, const void* rhs, size_t len );
void* memset(void *dest, int val, size_t len);
void* memcpy(void* dest, const void* src, size_t len);
