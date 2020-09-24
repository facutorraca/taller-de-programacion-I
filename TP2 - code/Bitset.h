#ifndef _BITSET_H_
#define _BITSET_H_

#include "Writer.h"
#include <vector>
#include <cstdint>
#include <fstream>
#include <cstdbool>

class Bitset {
    int size;
    int curr_pos;
    std::vector<bool> bits;

    private:
        void complete_number();

        void calculate_padding();

        uint8_t get_byte_to_print(char* number_by_bit);

    public:
        Bitset();

        void push_bit(bool bit);

        void set_size(int size);

        void print_in_file(Writer& writer);
};

#endif
