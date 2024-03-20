#include "serial.h"
#include "stdio.h"


#pragma GCC push_options
// Force the alignment for mtvec.BASE.
#pragma GCC optimize ("align-functions=4")
__attribute__ ((interrupt ("machine")))
void interrupt_handler(void){
    puts("interrupt!!!");
    asm volatile("wfi");
};
#pragma GCC pop_options