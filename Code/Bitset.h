#ifndef _BITSET_H_
#define _BITSET_H_

#include <fstream>
#include <cstdint>

class Bitset {

    int size;
    char* bits;
    int curr_pos;

    private:

        void calculate_padding();

        uint8_t get_byte_to_print(char* number_by_bit);

    public:

        Bitset();

        void push_bit(bool bit);

        void set_size(int size);

        void print_in_file(std::ofstream* o_file);

};

#endif
