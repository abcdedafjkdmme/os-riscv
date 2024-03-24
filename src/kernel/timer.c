#include "riscv.h"
#include <stdio.h>

void mti_handler()
{
  // to periodically trigger interrupt
  *((reg_t *)CLINT_MTIME) = 0;
  puts(" machine timer ");
}

void sti_handler(){
  // to periodically trigger interrupt
  //*((reg_t *)CLINT_MTIME) = 0;
  puts(" supervisor timer ");
}