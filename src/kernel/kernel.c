#include <stdint.h>
#include "uart.h"
#include <stdio.h>
#include "syscon.h"
#include "ustar_filesystem.h"
#include <string.h>
#include "common.h"
#include "interrupt.h"
#include <assert.h>
#include "riscv.h"

static ustar_file_header_t test_ustar_archive[10];

void init_test_ustar_archive()
{
    for (size_t i = 0; i < ARRAY_SIZE(test_ustar_archive); i++)
    {
        ustar_file_header_init(&test_ustar_archive[i]);
    }
}

void kmain()
{

    uart_init(11520,11520);
  //  interrupt_init();
    init_test_ustar_archive();

    puts("hello\r\nworld");

    // asm volatile("ebreak");
   for(;;){
     putchar(getchar());
   }
     
    

    // ustar_file_header_t *file_header = (ustar_file_header_t *)test_ustar_archive;

    // strcpy(file_header->name, "my_filet");
    // ustar_file_header_init(file_header);
    // void *res = ustar_file_header_lookup("my_file", ARRAY_SIZE("my_file"), "", ARRAY_SIZE(""), &test_ustar_archive, ARRAY_SIZE(test_ustar_archive));
    // assert(res == NULL);

    // void *res_2 = ustar_file_header_lookup("my_filet", ARRAY_SIZE("my_filet"), "", ARRAY_SIZE(""), &test_ustar_archive, ARRAY_SIZE(test_ustar_archive));
    // assert(res_2 != NULL);

    // for(;;){
    //     putchar(getchar());
    // }

    asm volatile("wfi");
}

/*
#pragma GCC push_options
// Force the alignment for mtvec.BASE.
#pragma GCC optimize("align-functions=4")
__attribute__((interrupt("machine"))) void c_intr(void)
{
    puts("interrupt");
}
#pragma GCC pop_options
*/