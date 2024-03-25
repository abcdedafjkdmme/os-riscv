#include "uart.h"
#include "stdio.h"
#include <string.h>


int putchar(char ch){
     uart_put_byte((uint8_t)ch);
     return 0;
}

int puts(const char* str){
    for(size_t i = 0; i < strlen(str); i++){
        int res = putchar(str[i]);
        if(res != 0)
        {
            return res;
        }
    }
    return 0;
}

int getchar(){
    return uart_get_byte();
}
