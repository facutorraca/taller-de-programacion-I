#include "Bitset.h"
#include <cstring>
#include <cstdint>
#include <iostream>
#include <stack>

#define BINARY 2

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

void Bitset::print_in_file(std::ofstream* o_file) {
    char number_by_bit[8];
    int offset = 0;
    for (int i = 0; i < this->size; i++) {
        number_by_bit[i - offset] = this->bits[i];
        if ((i+1) % 8 == 0) {
            uint8_t number = this->get_byte_to_print(number_by_bit);
            o_file->write((char*)&number, sizeof(uint8_t));
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

uint8_t Bitset::get_byte_to_print(char* number_by_bit) {
    uint8_t number = strtoul(number_by_bit, 0, BINARY);
    return number;
}
