.section .init, "ax"
.global _start
_start:
    .cfi_startproc
    .cfi_undefined ra
    .option push
    .option norelax
    la gp, __global_pointer$
    .option pop
    la sp, __stack_top
    add s0, sp, zero

    csrw mie, 1

    la a0, interrupt_handler
    csrw mtvec , a0


    jal zero, kmain
    .cfi_endproc
    .end
