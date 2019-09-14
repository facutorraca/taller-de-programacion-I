#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <cstdint>
#include <bitset>
#include <vector>

class Block {
    //d
    int elements;
    uint8_t bits;
    uint32_t ref;
    uint32_t* numbers;
    std::vector<bool> dyn_bitset;

    private:

        uint32_t find_max();

        uint32_t find_min();

        void numbers_to_bits();

        void subtract_reference();

        uint8_t get_bits(uint32_t number);

    public:

        Block(uint32_t* numbers, int elements);

        void compress();

        void print();

        ~Block();
};

#endif
