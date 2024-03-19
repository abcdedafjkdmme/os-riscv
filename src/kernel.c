#include <stdint.h>

#define SERIAL_BASE_ADDR 0x10000000

void kmain(){

    for(uintptr_t ptr = SERIAL_BASE_ADDR; ptr < 100; ptr++){
        *(uint32_t*)ptr = 'H';
    }

    *(uint8_t*)SERIAL_BASE_ADDR = 'H';  

    for(;;){
        asm volatile("wfi");
    };
}
