#pragma once 
#include <stddef.h>
#include <stdint.h>

#define SERIAL_BASE_ADDR 0x10000000
#define SERIAL_LENGTH 0x100

int serial_put_byte( uint8_t data);