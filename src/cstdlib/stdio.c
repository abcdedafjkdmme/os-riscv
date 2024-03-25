#include "uart.h"
#include "stdio.h"
#include <string.h>


int putchar(char ch){
     uart_put_byte((uint8_t)ch);
     return 0;
}

int puts(const char* str){
    size_t str_len = strlen(str);
    for(size_t i = 0; i < str_len; i++){
        int res = putchar(str[i]);
        if(res != 0)
        {
            return res;
        }
    }
    return 0;
}

int getchar(){
    char ret = 0;
    int is_uart_fifo_empty = uart_get_byte(&ret);
    while(is_uart_fifo_empty){
        is_uart_fifo_empty = uart_get_byte(&ret);
    }
    return ret;
}
