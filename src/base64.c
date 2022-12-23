#include <stdint.h>
#include <stdlib.h>
#include <string.h>

unsigned char bin_to_ascii[65] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','9','+','/','='
};

int8_t ascii_to_bin[80] = {
    /* + */   62,
    -1,-1,-1,
    /* / */   63,
    /* 0-9 */ 52,53,54,55,56,57,58,59,60,61,
    -1,-1,-1,
    /* = */ 0,
    -1,-1,-1,
    /* A-Z */ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
    -1,-1,-1,-1,-1,-1,
    /* a-z */ 26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
};

const unsigned char base_char = '+';

void PrintBits(void* bytes, uint64_t num_bytes) {
    printf("Bytes: ");
    for(uint64_t i = 0; i < num_bytes; ++i) {
        for(uint64_t j = 0; j < 8; ++j) {
            uint8_t on = ((uint8_t*)bytes)[i] & (1 << (7 - j));
            if(on) {
                printf("1");
            }
            else {
                printf("0");
            }

            if(j == 3) {
                printf(".");
            }
        }
        printf(" ");
    }
    printf("\n");
}

char* Base64Encode(void* data, uint64_t num_bytes) {
    if(!data || num_bytes == 0) {
        return NULL;
    }

    uint64_t result_size = 4*((num_bytes / 3) + (num_bytes % 3 > 0));
    char* result_string = malloc(result_size + 1);
    if(!result_string) {
        printf("Could not malloc %zd bytes for result size...\n", result_size);
        return NULL;
    }

    uint64_t num_bytes_left = num_bytes;
    uint8_t* byte_to_read = (uint8_t*)data;
    uint64_t write_i = 0;
    while(3 <= num_bytes_left) {
        uint8_t byte_to_write_0 = 0;
        uint8_t byte_to_write_1 = 0;
        uint8_t byte_to_write_2 = 0;
        uint8_t byte_to_write_3 = 0;

        byte_to_write_0  = *byte_to_read >> 2;
        byte_to_write_1 = (*byte_to_read & 3) << 4;
        byte_to_read++;

        byte_to_write_1 = byte_to_write_1 | (*byte_to_read >> 4);
        byte_to_write_2  = (*byte_to_read & 15) << 2;
        byte_to_read++;

        byte_to_write_2  = byte_to_write_2  | ((*byte_to_read & 192) >> 6);
        byte_to_write_3 = *byte_to_read & 63;
        byte_to_read++;

        result_string[write_i++] = bin_to_ascii[byte_to_write_0];
        result_string[write_i++] = bin_to_ascii[byte_to_write_1];
        result_string[write_i++] = bin_to_ascii[byte_to_write_2];
        result_string[write_i++] = bin_to_ascii[byte_to_write_3];

        num_bytes_left -= 3;
    }

    // Take care of 1 or 2 bytes left
    uint8_t byte_to_write_0 = 0;
    uint8_t byte_to_write_1 = 0;
    uint8_t byte_to_write_2 = 64;
    uint8_t byte_to_write_3 = 64;
    if(num_bytes_left == 2) {
        byte_to_write_0  = *byte_to_read >> 2;
        byte_to_write_1 = (*byte_to_read & 3) << 4;
        byte_to_read++;

        byte_to_write_1 = byte_to_write_1 | (*byte_to_read >> 4);
        byte_to_write_2  = (*byte_to_read & 15) << 2;

        result_string[write_i++] = bin_to_ascii[byte_to_write_0];
        result_string[write_i++] = bin_to_ascii[byte_to_write_1];
        result_string[write_i++] = bin_to_ascii[byte_to_write_2];
        result_string[write_i++] = bin_to_ascii[byte_to_write_3];
    }
    else if (num_bytes_left == 1) {
        byte_to_write_0  = *byte_to_read >> 2;
        byte_to_write_1 = (*byte_to_read & 3) << 4;

        result_string[write_i++] = bin_to_ascii[byte_to_write_0];
        result_string[write_i++] = bin_to_ascii[byte_to_write_1];
        result_string[write_i++] = bin_to_ascii[byte_to_write_2];
        result_string[write_i++] = bin_to_ascii[byte_to_write_3];
    }

    result_string[write_i]   = '\0';

    return result_string;
}

void* Base64Decode(char* data, uint64_t* num_bytes_returned) {
    *num_bytes_returned = 0;

    if(!data || *data == '\0') {
        printf("No data to decode...\n");
        return NULL;
    }

    uint64_t buffer_size = 512;
    uint64_t growth_factor = 2;
    uint8_t* write_buffer = malloc(buffer_size);
    if(!write_buffer) {
        printf("Could not malloc %lld bytes for output buffer...\n", buffer_size);
        return NULL;
    }
    uint64_t write_i = 0;
    uint64_t read_i = 0;
    while(data[read_i] != '\0') {
        // Incorrect length
        if(data[read_i + 1] == '\0' ||
           data[read_i + 2] == '\0' ||
           data[read_i + 3] == '\0') {
            free(write_buffer);
            printf("Base64 string must be multiple of 4, but instead is %lld...\n", strlen(data));
            return NULL;
        }

        // Incorrect padding
        if(data[read_i]     == '=' ||
           data[read_i + 1] == '=') {
            free(write_buffer);
            printf("Incorrect padding near char index %lld [%c%c%c%c]...\n", read_i, data[read_i], data[read_i + 1], data[read_i + 2], data[read_i + 3]);
            return NULL;
        }

        // Check padding to see if we write 1, 2, or 3 bytes
        uint8_t num_bytes_to_write = 3;
        if(data[read_i + 3] == '=') {
            num_bytes_to_write = 2;
        }
        if(data[read_i + 2] == '=') {
            num_bytes_to_write = 1;
        }

        // After padding should be null term
        if(num_bytes_to_write < 3 && 
           data[read_i + 4] != '\0') {
            free(write_buffer);
            printf("String doesn't terminate after padding [%c%c%c%c%c]...\n", data[read_i], data[read_i + 1], data[read_i + 2], data[read_i + 3], data[read_i + 4]);
            return NULL;
        }

        // Need to reallocate output buffer
        if(buffer_size <= (write_i + num_bytes_to_write - 1)) {
            buffer_size = buffer_size * growth_factor;
            uint8_t* new_write_buffer = realloc(write_buffer, buffer_size);
            if(!new_write_buffer) {
                free(write_buffer);
                printf("Could not realloc %zd bytes for output buffer...\n", buffer_size);
                return NULL;
            }
            else {
                write_buffer = new_write_buffer;
            }
        }

        // Check for bad characters
        char char_0 = data[read_i++];
        char char_1 = data[read_i++];
        char char_2 = data[read_i++];
        char char_3 = data[read_i++];
        uint8_t index_0 = char_0 - base_char;
        uint8_t index_1 = char_1 - base_char;
        uint8_t index_2 = char_2 - base_char;
        uint8_t index_3 = char_3 - base_char;
        if(79 < index_0 ||
           79 < index_1 ||
           79 < index_2 ||
           79 < index_3) {
            free(write_buffer);
            printf("Bad ascii character found near index %lld [%c%c%c%c]...\n", read_i - 4, char_0, char_1, char_2, char_3);
            return NULL;
        }
        int8_t byte_to_read_0 = ascii_to_bin[index_0];
        int8_t byte_to_read_1 = ascii_to_bin[index_1];
        int8_t byte_to_read_2 = ascii_to_bin[index_2];
        int8_t byte_to_read_3 = ascii_to_bin[index_3];

        if(byte_to_read_0 == -1 ||
           byte_to_read_1 == -1 ||
           byte_to_read_2 == -1 ||
           byte_to_read_3 == -1) {
            free(write_buffer);
            printf("Bad ascii character found near index %lld [%c%c%c%c]...\n", read_i - 4, char_0, char_1, char_2, char_3);
            return NULL;
        }

        uint8_t byte_to_write_0 = (byte_to_read_0 << 2) | (byte_to_read_1 >> 4);
        uint8_t byte_to_write_1 = (byte_to_read_1 << 4) | (byte_to_read_2 >> 2);
        uint8_t byte_to_write_2 = (byte_to_read_2 << 6) | (byte_to_read_3);

        write_buffer[write_i++] = byte_to_write_0;
        if(1 < num_bytes_to_write) {
            write_buffer[write_i++] = byte_to_write_1;
        }
        if(2 < num_bytes_to_write ) {
            write_buffer[write_i++] = byte_to_write_2;
        }
    }

    // If buffer is larger than output bytes, realloc to save space
    if(write_i < buffer_size) {
        uint8_t* new_write_buffer = realloc(write_buffer, write_i);
        if(new_write_buffer) {
            write_buffer = new_write_buffer;
        }
    }

    *num_bytes_returned = write_i;
    return write_buffer;
}
