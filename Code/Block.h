#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <cstdint>
#include <bitset>
#include <fstream>
#include "Bitset.h"

class Block {

    Bitset bitset;
    uint8_t bits;
    uint32_t ref;

    int elements;
    uint32_t* numbers;

    private:

        uint32_t find_max();

        uint32_t find_min();

        void add_padding();

        void numbers_to_bits();

        void subtract_reference();

        uint8_t get_bits(uint32_t number);

    public:

        Block(const uint32_t* numbers, int elements);

        void print_in_file(std::ofstream* o_file);

        void compress();

        ~Block();
};

#endif
