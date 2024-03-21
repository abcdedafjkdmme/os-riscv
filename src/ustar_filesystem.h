#pragma once
#include <stdint.h>

#define ustar_filetype_normal '0'
#define ustar_filetype_hardlink '1'
#define ustar_filetype_symlink '2' 
#define ustar_filetype_chardev '3'
#define ustar_filetype_block_dev '4'
#define ustar_filetype_dir '5'
#define ustar_filetype_named_pipe '6' 
#define ustar_file_checksum_value_as_spaces 32

struct ustar_file {
    char name[100]; 
    char mode[8];
    char owner_id[8];
    char group_id[8];
    uint8_t file_size_octal[12];
    uint8_t last_modification_time_octal[12];
    uint8_t checksum[8];
    uint8_t type_flag;
    char linked_filename[100];
    char ustar_indicator[6];
    char ustar_version[2];
    char owner_user_name[32];
    char owner_group_name[32];
    char device_major_num[8];
    char device_minor_num[8];
    char filename_prefix[155];
}  __attribute__ ((aligned (512)));

typedef struct ustar_file ustar_file_t;

void create_ustar_file_t(ustar_file_t* file);

void* lookup_ustar_file_data(char* filename);