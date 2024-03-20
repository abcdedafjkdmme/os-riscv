#include "serial.h"
#include "stdio.h"
#include <string.h>


int putchar(char ch){
    int res = serial_put_byte((uint8_t)ch);
    if(res != 0){
        return res;
    }
    return 0;
}

int puts(const char* str){
    for(int i = 0; i < strlen(str); i++){
        int res = putchar(str[i]);
        if(res != 0)
        {
            return res;
        }
    }
}
