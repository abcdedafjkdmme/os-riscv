#include <stdint.h>

#define SERIAL_BASE_ADDR 0x10000000

#pragma GCC push_options
// Force the alignment for mtvec.BASE.
#pragma GCC optimize ("align-functions=4")
__attribute__ ((interrupt ("machine")))
void interrupt_handler(void){
    *(uint8_t*) SERIAL_BASE_ADDR = 'H';
     for(;;){
        asm volatile("wfi");
    };
};
#pragma GCC pop_options


void kmain(){
    *(uint8_t*) SERIAL_BASE_ADDR = 'V';
    int i = 5/0;
    for(;;){
        asm volatile("wfi");
    };
}
