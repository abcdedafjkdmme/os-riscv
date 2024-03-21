#include "ustar_filesystem.h"
#include "common.h"
#include "string.h"

static size_t generate_ustar_file_checksum(ustar_file_t* file){
    size_t checksum = 0;
    for(int i = 0; i < 512; i++){
        checksum += ((uint8_t*)file)[i];
    }
    checksum += ustar_file_checksum_value_as_spaces;
}

void create_ustar_file_t(ustar_file_t* file){
    strcpy(file->ustar_indicator, "ustar");
    strcpy(file->ustar_indicator, "00");

    size_t checksum = 0;
    for(int i = 0; i < 512; i++){
        checksum += ((uint8_t*)file)[i];
    }
    checksum += ustar_file_checksum_value_as_spaces;
}

void* lookup_ustar_file_data(char* filename){
    
}
