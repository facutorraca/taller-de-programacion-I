#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include <string.h>

int char_to_int(char char_value) {
    return (char_value - '0');
}

bool is_a_number(char a) {
    return a == '0' || a == '1' || a == '2' || a == '3' || a == '4' ||
           a == '5' || a == '6' || a == '7' || a == '8' || a == '9';
}
