#pragma once
#include <stdint.h>
#include <stddef.h>

#define ustar_file_block_size 512
#define ustar_filetype_normal '0'
#define ustar_filetype_hardlink '1'
#define ustar_filetype_symlink '2' 
#define ustar_filetype_chardev '3'
#define ustar_filetype_block_dev '4'
#define ustar_filetype_dir '5'
#define ustar_filetype_named_pipe '6' 
#define ustar_file_checksum_value_as_spaces 32
#define ustar_file_lookup_max_tries 50

struct ustar_file_header {
    char name[100]; 
    char mode[8];
    char owner_id[8];
    char group_id[8];
    uint8_t file_size_octal[12];
    uint8_t last_modification_time_octal[12];
    uint8_t checksum_octal[8];
    uint8_t type_flag;
    char linked_filename[100];
    char ustar_indicator[6];
    char ustar_version[2];
    char owner_user_name[32];
    char owner_group_name[32];
    char device_major_num[8];
    char device_minor_num[8];
    char name_prefix[155];
}  __attribute__ ((aligned (512)));

typedef struct ustar_file_header ustar_file_header_t;
typedef int ustar_file_mode_t;

void* ustar_file_header_lookup(const char* filename,size_t filename_len, const char* filename_prefix, size_t filename_prefix_len, void* archive, size_t archive_len);
void ustar_file_header_init(ustar_file_header_t* file_header);

