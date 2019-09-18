#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Writer.h"
#include <cstdint>
#include <bitset>
#include <vector>
#include <fstream>
#include "Bitset.h"

class Block {

    Bitset bitset;
    uint8_t bits;
    uint32_t ref;

    std::vector<uint32_t> numbers;

    private:

        uint32_t find_max();

        uint32_t find_min();

        void add_padding();

        void numbers_to_bits();
 
        void subtract_reference();

        uint8_t get_bits(uint32_t number);

    public:

        Block(const std::vector<uint32_t> numbers);

        void print_in_file(Writer& writer);

        void compress();

        ~Block();
};

#endif
