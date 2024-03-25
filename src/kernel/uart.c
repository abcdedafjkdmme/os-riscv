#include <stdint.h>
#include <stddef.h>
#include "uart.h"
#include <assert.h>
#include "riscv.h"
#include <stdio.h>

/**
 * Find minimum divisor divides in_freq to max_target_hz;
 * Based on uart driver n SiFive FSBL.
 *
 * f_baud = f_in / (div + 1) => div = (f_in / f_baud) - 1
 * The nearest integer solution requires rounding up as to not exceed max_target_hz.
 * div  = ceil(f_in / f_baud) - 1
 *	= floor((f_in - 1 + f_baud) / f_baud) - 1
 * This should not overflow as long as (f_in - 1 + f_baud) does not exceed
 * 2^32 - 1, which is unlikely since we represent frequencies in kHz.
 */
static inline unsigned int uart_min_clk_divisor(int in_freq,
                                                int max_target_hz)
{
    uint64_t quotient = (in_freq + max_target_hz - 1) / (max_target_hz);

    /* Avoid underflow */
    if (quotient == 0)
        return 0;
    else
        return quotient - 1;
}

void uart_init(int in_freq, int baud_rate)
{
    *(volatile uint32_t *)UART_TXCTRL = 0x1;
    *(volatile uint32_t *)UART_RXCTRL = 0x1;
    *(volatile uint32_t *)UART_DIV = uart_min_clk_divisor(in_freq, baud_rate);
}

void uart_put_byte(uint8_t data)
{
    int is_uart_txfifo_full = (*(uint32_t *)UART_TXDATA) & UART_TXDATA_FIFO_FULL_MASK;
    while (is_uart_txfifo_full)
        ;

    *(volatile reg_t *)UART_TXDATA = data;
}
int uart_get_byte(uint8_t* res)
{
    uint32_t rx = *(volatile uint32_t *)UART_RXDATA;
    uint_fast8_t is_uart_rxfifo_empty = (rx == UART_RX_EMPTY_VALUE); 
    *res = (uint8_t)rx;
    return is_uart_rxfifo_empty;
}
