#pragma once 
#include <stddef.h>
#include <stdint.h>

#define UART        0x10000000
#define UART_THR    (UART+0x00) // THR:transmitter holding register 
#define UART_RHR    (UART+0x00) // THR:transmitter holding register 
#define UART_LSR    (UART+0x05) // LSR:line status register 
#define UART_LSR_RX_READY 0x01            // input is waiting to be read from RHR
#define UART_LSR_EMPTY_MASK 0x40 

void uart_init();
void uart_put_byte(uint8_t data);
uint8_t uart_get_byte();