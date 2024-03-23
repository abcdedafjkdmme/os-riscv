
#pragma once

#include <stdint.h>

//#define reg_t uint32_t // RISCV32: register is 32bits
#define reg_t uint64_t // RISCV64: register is 64bits

// Saved registers for kernel context switches.
struct context {
  reg_t ra;
  reg_t sp;

  // callee-saved
  reg_t s0;
  reg_t s1;
  reg_t s2;
  reg_t s3;
  reg_t s4;
  reg_t s5;
  reg_t s6;
  reg_t s7;
  reg_t s8;
  reg_t s9;
  reg_t s10;
  reg_t s11;
};

typedef struct{
  reg_t zero;
  reg_t ra;
  reg_t sp;
  reg_t gp;
  reg_t tp;
  reg_t t0;
  reg_t t1;
  reg_t t2;
  reg_t s0_fp;
  reg_t s1;
  reg_t a0;
  reg_t a1;
  reg_t a2;
  reg_t a3;
  reg_t a4;
  reg_t a5;
  reg_t a6;
  reg_t a7;
  reg_t s2;
  reg_t s3;
  reg_t s4;
  reg_t s5;
  reg_t s6;
  reg_t s7;
  reg_t s8;
  reg_t s9;
  reg_t s10;
  reg_t s11;
  reg_t t3;
  reg_t t4;
  reg_t t5;
  reg_t t6;
} all_registers_t;

// ref: https://github.com/mit-pdos/xv6-riscv/blob/riscv/kernel/riscv.h
// 
// local interrupt controller, which contains the timer.
// ================== Timer Interrput ====================

#define NCPU 8             // maximum number of CPUs
#define CLINT 0x2000000
#define CLINT_MTIMECMP(hartid) (CLINT + 0x4000 + 4*(hartid))
#define CLINT_MTIME (CLINT + 0xBFF8) // cycles since boot.

// which hart (core) is this?
static inline reg_t r_mhartid()
{
  reg_t x;
  asm volatile("csrr %0, mhartid" : "=r" (x) );
  return x;
}

// Machine Status Register, mstatus
#define MSTATUS_MPP_MASK (3 << 11) // previous mode.
#define MSTATUS_MPP_M (3 << 11)
#define MSTATUS_MPP_S (1 << 11)
#define MSTATUS_MPP_U (0 << 11)
#define MSTATUS_MIE (1 << 3)    // machine-mode interrupt enable.

static inline reg_t r_mstatus()
{
  reg_t x;
  asm volatile("csrr %0, mstatus" : "=r" (x) );
  return x;
}

static inline void w_mstatus(reg_t x)
{
  asm volatile("csrw mstatus, %0" : : "r" (x));
}

// machine exception program counter, holds the
// instruction address to which a return from
// exception will go.
static inline void w_mepc(reg_t x)
{
  asm volatile("csrw mepc, %0" : : "r" (x));
}

static inline reg_t r_mepc()
{
  reg_t x;
  asm volatile("csrr %0, mepc" : "=r" (x));
  return x;
}


#define MCAUSE_INTERRUPT_MASK (1 << 63)
#define MCAUSE_INTERRUPT 1
#define MCAUSE_TRAP 0

#define MCAUSE_EC_MASK 0b111111111 //excecption code mask
/*m -> machine
  s -> supervisor
  s -> software
  t -> timer
  e -> external
  i -> interrupt
*/
#define MCAUSE_SSI_EC 1
#define MCAUSE_MSI_EC 3
#define MCAUSE_STI_EC 5
#define MCAUSE_MTI_EC 7
#define MCAUSE_SEI_EC 9
#define MCAUSE_MEI_EC 11

#define MCAUSE_INSTR_ADDR_MISALIGN 0
#define MCAUSE_INSTR_ACCESS_FAULT 1
#define MCAUSE_ILLEGAL_INSTR 2
#define MCAUSE_BREAKPOINT 3
#define MCAUSE_LOAD_ADDR_MISALIGN 4
#define MCAUSE_LOAD_ACCESS_FAULT 5
#define MCAUSE_STORE_AMO_ADDR_MISALIGN 6
#define MCAUSE_STORE_AMO_ACCESS_FAULT 7
#define MCAUSE_ENV_CALL_U_MODE 8
#define MCAUSE_ENV_CALL_S_MODE 9
#define MCAUSE_ENV_CALL_M_MODE 11
#define MCAUSE_INSTR_PAGE_FAULT 12
#define MCAUSE_LOAD_PAGE_FAULT 13
#define MCAUSE_LOAD_AMO_PAGE_FAULT 15


static inline reg_t r_mcause()
{
  reg_t x;
  asm volatile("csrr %0, mcause" : "=r" (x));
  return x;
}
static inline void w_mcause(reg_t x)
{
  asm volatile("csrw mcause, %0" : : "r" (x));
}

// Machine Scratch register, for early trap handler
static inline void w_mscratch(reg_t x)
{
  asm volatile("csrw mscratch, %0" : : "r" (x));
}

#define MTVEC_MODE_MASK 0b11
#define MTVEC_MODE_DIRECT 0x0
#define MTVEC_MODE_VECTORED 0x1
static inline reg_t r_mtvec()
{
  reg_t x;
  asm volatile("csrr %0, mtvec" : "=r" (x));
  return x;
}
// Machine-mode interrupt vector
static inline void w_mtvec(reg_t x)
{
  asm volatile("csrw mtvec, %0" : : "r" (x));
}

// Machine-mode Interrupt Enable
#define MIE_MEIE (1 << 11) // external interrupt enable
#define MIE_MTIE (1 << 7)  // timer interrupt enable
#define MIE_MSIE (1 << 3)  // software interrupt enable

static inline reg_t r_mie()
{
  reg_t x;
  asm volatile("csrr %0, mie" : "=r" (x) );
  return x;
}

static inline void w_mie(reg_t x)
{
  asm volatile("csrw mie, %0" : : "r" (x));
}