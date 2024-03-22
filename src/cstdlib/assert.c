#include "stdio.h"
#include "common.h"

void assert_failed(char *file, int line, char* expr){
    puts(" ");
    puts(file);
    
    char line_str[32];
    char* res = itoa(line, line_str, 10);

    puts(":");
    puts(res);
    puts(": ");

    puts("Assertion '");
    puts(expr);
    puts("' failed. ");

    asm volatile("ebreak");
}