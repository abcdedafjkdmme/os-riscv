#include <stdint.h>
#include "serial.h"
#include <stdio.h>

void kmain(){
    puts("hello");
    for(;;){
        asm volatile("wfi");
    };
}
