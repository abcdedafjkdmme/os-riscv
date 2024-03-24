#pragma once
#include "stdio.h"
#include <stdint.h>

#define SYSCON_PTR (volatile uint32_t*)0x100000
#define SYSCON_REBOOT_VAL 0x7777
#define SYSCON_POWEROFF_VAL 0x5555


static void syscon_reboot(){
    puts("reboot requested !!!");
    *SYSCON_PTR = SYSCON_REBOOT_VAL;
}


static void syscon_poweroff(){
    puts("poweroff requested !!!");
    *SYSCON_PTR = SYSCON_POWEROFF_VAL;
}