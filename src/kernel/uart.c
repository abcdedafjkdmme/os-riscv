#include <stdint.h>
#include <stddef.h>
#include "uart.h"

void uart_init(){
    //enable rxctrl rxenable
    //*(volatile uint32_t*)UART_TXCTRL = (*(volatile uint32_t*)UART_TXCTRL & ~UART_TXCTRL_TXEN_MASK) | ( 0x1 & UART_TXCTRL_TXEN_MASK);
    //*(volatile uint32_t*)(UART_BASE_PTR+ 0xc) = 0b1111111111;
}

void uart_put_byte(uint8_t data){
    *(volatile uint8_t*)UART_THR = data;
}
uint8_t uart_get_byte(){
    while ((*(volatile uint8_t*)UART_LSR & UART_LSR_RX_READY) == 0);
    return *(volatile uint8_t*)UART_RHR;
}


