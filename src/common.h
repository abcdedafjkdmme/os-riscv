#pragma once

#include <stdint.h>
#include <stddef.h>

#define FIELD_SIZEOF(t, f) (sizeof(((t*)0)->f))
#define ARRAY_SIZE(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

char* itoa(int value, char* result, int base);
int oct_str_to_int(const unsigned char *str, int size);
void uint16_to_oct_str(uint16_t num, char *str, size_t size);