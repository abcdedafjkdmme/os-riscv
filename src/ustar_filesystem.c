#include "ustar_filesystem.h"
#include "common.h"
#include "string.h"
#include <stddef.h>

int generate_ustar_file_checksum(ustar_file_header_t *file_header)
{
    /*
    if(file_header == NULL) return -1;

    int checksum = 0;
    for (int i = 0; i < 512; i++)
    {
        checksum += ((uint8_t *)file_header)[i];
    }
    checksum += ustar_file_checksum_value_as_spaces;
    return checksum;
    */
    
   
    const uint8_t *header = (const uint8_t *) file_header;
    unsigned int chksum;
    size_t i;

    chksum = 0;
    for (i = 0; i < 512; i++)
    {
        //The ustar checksum is calculated as if the chksum field were all spaces. 
        const size_t chksum_start = offsetof(ustar_file_header_t, checksum_octal);
        const size_t chksum_end = chksum_start + sizeof file_header->checksum_octal;
        int in_chksum_field = i >= chksum_start && i < chksum_end;
        chksum += in_chksum_field ? ' ' : header[i];
    }
    return chksum;
    
}

int is_block_valid_ustar_file_header(ustar_file_header_t *file_header)
{
    if (file_header == NULL)
        return -1;

    int file_header_checksum_val =  oct_str_to_int(file_header->checksum_octal, sizeof file_header->checksum_octal);

    puts(file_header->checksum_octal);

    int correct_checksum = generate_ustar_file_checksum(file_header);

    int does_file_header_have_correct_ustar_indicator = memcmp(file_header->ustar_indicator, "ustar", sizeof file_header->ustar_indicator);
    int does_file_header_have_correct_ustar_version = memcmp(file_header->ustar_version, "00", sizeof file_header->ustar_version);

    if (file_header_checksum_val == correct_checksum
        && (does_file_header_have_correct_ustar_indicator == 0)
        && (does_file_header_have_correct_ustar_version == 0))
    {
        return 1;
    }
    return 0;
}

int ustar_file_header_create(ustar_file_header_t *file_header)
{
    if (file_header == NULL)
        return -1;

    memcpy(file_header->ustar_indicator, "ustar", 6);
    memcpy(file_header->ustar_version, "00", 2);

    int checksum = generate_ustar_file_checksum(file_header);

    if (checksum < 0)
        return -1;

    int res = uint16_to_oct_str(checksum, file_header->checksum_octal, sizeof file_header->checksum_octal);
    return res;
}

void *ustar_file_header_lookup(char *filename, void *archive)
{
    if (filename == NULL)
        return NULL;
    if (archive == NULL)
        return NULL;

    for (size_t i = 0; i < ustar_file_lookup_max_tries; i++)
    {
        ustar_file_header_t *file_header = &((ustar_file_header_t *)archive)[i];
        if (is_block_valid_ustar_file_header(file_header))
        {
            return file_header;
        }
    }
    return NULL;
}
