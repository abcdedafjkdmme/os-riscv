#include <stdint.h>
#include "serial.h"
#include <stdio.h>
#include "syscon.h"
#include "ustar_filesystem.h"
#include <string.h>
#include "common.h"
#include <assert.h>

static uint8_t test_filesystem_block[512*10];


void kmain(){
   

    puts("hello");

    ustar_file_header_t* file_header =  (ustar_file_header_t*)test_filesystem_block;

    strcpy(file_header->name , "my_file");
    ustar_file_header_create(file_header);
    void* res = ustar_file_header_lookup("my_file", test_filesystem_block);

    if(res == NULL){
        puts(" cant find file");
    }
    else{
        puts(" found file");
    }

    asm volatile("wfi");

}

#pragma GCC push_options
// Force the alignment for mtvec.BASE.
#pragma GCC optimize ("align-functions=4")
__attribute__((interrupt ("machine")))
void c_intr(void){
    puts("interrupt");
}
#pragma GCC pop_options