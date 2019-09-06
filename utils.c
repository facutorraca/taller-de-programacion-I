#include "utils.h"
#include <stdint.h>

int uint_to_array(char* array, uint32_t uint) {
    array[0] = uint >> 24;
    array[1] = uint >> 16;
    array[2] = uint >> 8;
    array[3] = uint;
    return SUCCESS;
}

uint32_t array_to_uint(char* array) {
    uint32_t uint_a = array[0] << 24;
    uint32_t uint_b = array[1] << 16;
    uint32_t uint_c = array[2] << 8;
    uint32_t uint_d = array[3];
    return uint_a | uint_b | uint_c | uint_d;
}
