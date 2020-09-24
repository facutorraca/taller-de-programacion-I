 #include "Bitset.h"
#include "Writer.h"
#include <cstring>
#include <cstdint>
#include <iostream>
#include <cstdbool>

#define BINARY +2


/*--------------Public--------------*/
Bitset::Bitset() {
    this->size = 0;
    this->curr_pos = 0;
}

void Bitset::set_size(int size) {
    this->size = size;
    this->calculate_padding();
}

void Bitset::push_bit(bool bit) {
    this->bits.push_back(bit);
    this->curr_pos++;
}

void Bitset::print_in_file(Writer& writer) {
    this->complete_number();
    char number_by_bit[8];

    int offset = 0;
    for (int i = 0; i < this->size; i++) {
        number_by_bit[i - offset] = this->bits[i]?'1':'0';
        if ((i+1) % 8 == 0) {
            writer.write_number(number_by_bit);
            offset = offset + 8;
        }
    }
}

/*--------------Private-------------*/
void Bitset::calculate_padding() {
    while (this->size % 8 != 0) {
        this->size++;
    }
}

void Bitset::complete_number() {
    for (int i = this->curr_pos; i < this->size; i++) {
        this->bits[i] = false;
    }
}
