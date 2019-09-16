#include "Bitset.h"
#include "Writer.h"
#include <cstring>
#include <cstdint>
#include <iostream>
#include <stack>

#define BINARY +2

/*--------------Public--------------*/
Bitset::Bitset() {
    this->bits = nullptr;
    this->size = 0;
    this->curr_pos = 0;
}

void Bitset::set_size(int size) {
    this->size = size;
    this->calculate_padding();
    this->bits = new char[this->size];
    memset(this->bits, 0, this->size * sizeof(char));
}

void Bitset::push_bit(bool bit) {
    if (bit) {
        this->bits[this->curr_pos] = '1';
    } else
        this->bits[this->curr_pos] = '0';
    this->curr_pos++;
}

void Bitset::print_in_file(Writer& writer) {
    char number_by_bit[8];
    int offset = 0;
    for (int i = 0; i < this->size; i++) {
        number_by_bit[i - offset] = this->bits[i];
        if ((i+1) % 8 == 0) {
            writer.write_number(number_by_bit);
            offset = offset + 8;
        }
    }
}

/*--------------Private-------------*/
void Bitset::calculate_padding() {
    while(this->size % 8 != 0) {
        this->size++;
    }
}
