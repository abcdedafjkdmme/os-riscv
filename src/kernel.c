#include <stdint.h>
#include "serial.h"
#include <stdio.h>
#include "syscon.h"

void kmain(){
    puts("hello");
    for(;;){
        asm volatile("wfi");
    };
}
