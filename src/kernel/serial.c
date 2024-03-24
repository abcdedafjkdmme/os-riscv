#include <stdint.h>
#include <stddef.h>
#include "serial.h"

int serial_put_byte(uint8_t data){
    *SERIAL_BASE_ADDR = data;
    return 0;
}
