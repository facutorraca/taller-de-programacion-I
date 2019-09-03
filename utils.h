#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>

#define ERROR 1
#define SUCCESS 0

int uint_to_array(char* array, uint32_t uint);

uint32_t array_to_uint(char* array);

#endif
