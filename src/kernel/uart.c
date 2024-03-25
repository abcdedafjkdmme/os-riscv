#include <stdint.h>
#include <stddef.h>
#include "uart.h"
#include <assert.h>
#include "riscv.h"

void uart_init()
{
    *(volatile reg_t *)UART_TXCTRL = (*(volatile reg_t *)UART_TXCTRL & ~UART_TXCTRL_TXEN_MASK) | (0x1 & UART_TXCTRL_TXEN_MASK);
    *(volatile reg_t *)UART_RXCTRL = (*(volatile reg_t *)UART_RXCTRL & ~UART_RXCTRL_RXEN_MASK) | (0x1 & UART_RXCTRL_RXEN_MASK);
}

void uart_put_byte(uint8_t data)
{
    int is_uart_txfifo_full = (*(reg_t *)UART_TXDATA) & UART_TXDATA_FIFO_FULL_MASK;

    while (is_uart_txfifo_full)
        ;

    *(volatile reg_t *)UART_TXDATA = data;
}
uint8_t uart_get_byte()
{
    int is_uart_rxfifo_empty = (*(volatile reg_t *)UART_RXDATA) & UART_RXDATA_FIFO_EMPTY_MASK;
    while (is_uart_rxfifo_empty)
        ;
    return *(volatile reg_t *)UART_RXDATA;
}
