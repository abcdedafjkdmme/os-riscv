#include "interrupt.h"
#include "riscv.h"
#include <stdio.h>
#include "common.h"
#include <assert.h>
#include "timer.h"

#define timer_interval 10000000 // cycles; about 1/100th of a second in qemu.

extern void interrupt_and_exception_handler_asm();

void exception_handler(void)
{
  puts(" exception!! ");
  char ec[20];
  itoa(r_mcause(), ec, 10);
  puts("exception code: ");
  puts(ec);
  puts(" ");
}


void interrupt_handler(void)
{

  switch (r_mcause() & MCAUSE_EC_MASK)
  {
  case MCAUSE_MTI_EC:
    mti_handler();
    break;
  case MCAUSE_STI_EC:
    sti_handler();
    break;
  case MCAUSE_ENV_CALL_M_MODE:
    break;
  default:
  {
    char ec_str[10];
    itoa(r_mcause() & MCAUSE_EC_MASK, ec_str, 10);
    puts(" couldnt parse interrupt ec. ec is ");
    puts(ec_str);
    puts(" ");
    break;
  }
  }
}
void interrupt_and_exception_handler(void)
{
  int is_mcause_interrupt_or_trap = r_mcause() & MCAUSE_INTERRUPT_MASK;
   if (is_mcause_interrupt_or_trap == MCAUSE_EXCEPTION)
   {
      exception_handler();
  }
  if(is_mcause_interrupt_or_trap == MCAUSE_INTERRUPT)
  {
    interrupt_handler();
  }
  //advance mepc to next instr
  w_mepc(r_mepc() + 4);
}

void interrupt_init()
{
  // each CPU has a separate source of timer interrupts.
  int id = r_mhartid();

  // ask the CLINT for a timer interrupt.
  *(reg_t *)CLINT_MTIMECMP(id) = *(reg_t *)CLINT_MTIME + timer_interval;

  // set the machine-mode trap handler.
  w_mtvec((reg_t)interrupt_and_exception_handler_asm);

  // enable machine-mode interrupts.
  w_mstatus( MSTATUS_MIE);

  // enable machine-mode timer interrupts.
  w_mie(MIE_MSIE | MIE_MTIE);
}
