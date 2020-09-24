#include "Block.h"
#include "Writer.h"
#include "Bitset.h"
#include <cstdint>
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>


/*--------------Public--------------*/
Block::Block(const std::vector<uint32_t> numbers) {
    this->numbers.assign(numbers.begin(), numbers.end());
    this->ref = this->bits = 0;
}

void Block::print_in_file(Writer& writer) {
    writer.write_reference(this->ref);
    writer.write_bits(this->bits);
    this->bitset.print_in_file(writer);
}

void Block::compress() {
    this->ref = this->find_min();
    this->subtract_reference();

    uint32_t max = this->find_max();
    this->bits = this->get_bits(max);

    this->bitset.set_size(this->bits * this->numbers.size());

    this->numbers_to_bits();
}

/*--------------Private-------------*/
uint32_t Block::find_min() {
    uint32_t curr_min = this->numbers[0];
    for (size_t i = 1; i < this->numbers.size(); i++) {
        if (curr_min > this->numbers[i]) {
            curr_min = this->numbers[i];
        }
    }
    return curr_min;
}

uint32_t Block::find_max() {
    uint32_t curr_max = this->numbers[0];
    for (size_t i = 1; i < this->numbers.size(); i++) {
        if (curr_max < this->numbers[i]) {
            curr_max = this->numbers[i];
        }
    }
    return curr_max;
}

void Block::subtract_reference() {
    for (size_t i = 0; i < this->numbers.size(); i++) {
        this->numbers[i] = this->numbers[i] - this->ref;
    }
}

uint8_t Block::get_bits(uint32_t number) {
    if (number == 0) {
        return 0;
    }
    return (uint8_t)log2(number) + 1;
}

void Block::numbers_to_bits() {
    std::bitset<32> bitset;

    for (size_t i = 0; i < this->numbers.size(); i++) {
        bitset = this->numbers[i];
        for (int j = 0; j < this->bits; j++) {
            this->bitset.push_bit(bitset[this->bits - 1 - j]);
        }
    }
}

Block::~Block() {}
