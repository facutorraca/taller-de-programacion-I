#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include <stdbool.h>

#define ERROR 1
#define SUCCESS 0

int uint_to_array(char* array, uint32_t uint);

int char_to_int(char char_value);

uint32_t array_to_uint(char* array);

bool is_a_number(char a);

#endif
