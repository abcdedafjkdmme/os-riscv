#pragma once
#include <stddef.h>
#include <stdint.h>

// #define UART        0x10010000
// #define UART_THR    (UART+0x00) // THR:transmitter holding register
// #define UART_RHR    (UART+0x00) // THR:transmitter holding register
// #define UART_LSR    (UART+0x05) // LSR:line status register
// #define UART_LSR_RX_READY 0x01            // input is waiting to be read from RHR
// #define UART_LSR_EMPTY_MASK 0x40

#define UART_BASE_PTR 0x10010000
#define UART_TXDATA (UART_BASE_PTR + 0x0)
#define UART_RXDATA (UART_BASE_PTR + 0x4)
#define UART_TXCTRL (UART_BASE_PTR + 0x8)
#define UART_RXCTRL (UART_BASE_PTR + 0xc)
#define UART_IE (UART_BASE_PTR + 0x10)
#define UART_IP (UART_BASE_PTR + 0x14)
#define UART_DIV (UART_BASE_PTR + 0x18)

#define UART_TXDATA_FIFO_FULL_MASK (1 << 31)
#define UART_RXDATA_FIFO_EMPTY_MASK (1 << 31)

#define UART_TXCTRL_TXEN_MASK 0x1
#define UART_TXCTRL_NSTOP_MASK (1 << 1)
#define UART_RXCTRL_RXEN_MASK 0x1

#define UART_RX_EMPTY_VALUE 2147483648

void uart_init(int in_freq, int baud_rate);
void uart_put_byte(uint8_t data);
int uart_get_byte(uint8_t* res);