#include "interrupt.h"
#include "riscv.h"
#include <stdio.h>
#include "common.h"

#define timer_interval 10000000 * 5 // cycles; about 1 second in qemu.

extern void interrupt_and_exception_handler_asm();

void exception_handler(void)
{
  puts(" exception!! ");
  char ec[20];
  itoa(r_mcause() & MCAUSE_EC_MASK, ec, 10);
  puts("exception code: ");
  puts(ec);
  puts(" ");
}
void machine_timer_interrupt_handler(void){
  //to periodically trigger interrupt
  *((uint64_t*)CLINT_MTIME) = 0;
  puts("timer");
}

void interrupt_handler(void)
{
  if(r_mcause() & MCAUSE_MTI_EC){
    machine_timer_interrupt_handler();
  }
}
void interrupt_and_exception_handler(void)
{
  if ((r_mcause() & MCAUSE_INTERRUPT_MASK) == MCAUSE_EXCEPTION)
  {
    exception_handler();
  }
  else
  {
    interrupt_handler();
  }
  w_mepc(r_mepc() + 4);
}

void interrupt_init()
{
  // each CPU has a separate source of timer interrupts.
  int id = r_mhartid();

  // ask the CLINT for a timer interrupt.
  *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + timer_interval;

  // set the machine-mode trap handler.
  w_mtvec(&interrupt_and_exception_handler_asm);

  // enable machine-mode interrupts.
  w_mstatus(r_mstatus() | MSTATUS_MIE);

  // enable machine-mode timer interrupts.
  w_mie(MIE_MSIE | MIE_MTIE);
}
