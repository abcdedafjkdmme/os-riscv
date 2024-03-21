#include "ustar_filesystem.h"
#include "common.h"
#include "string.h"
#include "stddef.h"

static size_t generate_ustar_file_checksum(ustar_file_header_t* file_header){
    size_t checksum = 0;
    for(int i = 0; i < 512; i++){
        checksum += ((uint8_t*)file_header)[i];
    }
    checksum += ustar_file_checksum_value_as_spaces;
}

static int is_block_valid_ustar_file_header(ustar_file_header_t* file_header){
    if(file_header->checksum == )
}

void create_ustar_file_header_t(ustar_file_header_t* file_header){
    strcpy(file_header->ustar_indicator, "ustar");
    strcpy(file_header->ustar_indicator, "00");

    size_t checksum = generate_ustar_file_checksum(file_header);
    uint16_to_oct_char(checksum, file_header->checksum_octal, strlen(file_header->checksum_octal));
}

void* lookup_ustar_file_data(char* filename, void* archive){
    for(size_t i = 0; i < ustar_file_lookup_max_tries; i++){
        ustar_file_header_t file_header = ((ustar_file_header_t*)archive)[i];
        
    }
}
