#include "Block.h"
#include <cstdint>
#include <iostream>
#include <cmath>

/*--------------Public--------------*/
Block::Block(uint32_t* numbers, int elements) {
    this->numbers = new uint32_t[elements];
    for (int i = 0; i < elements; i++) {
        this->numbers[i] = numbers[i];
    }

    this->elements = elements;
    this->ref = 0;
    this->bits = 0;
}

void Block::print() {
    std::cout << " Ref " << this->ref << " Bits " << unsigned(this->bits) << '\n';
}

void Block::compress() {
    this->ref = this->find_min();
    this->subtract_reference();

    uint32_t max = this->find_max();
    this->bits = this->get_bits(max);
}

/*--------------Private-------------*/
uint32_t Block::find_min() {
    uint32_t curr_min = this->numbers[0];
    for (int i = 1; i < this->elements; i++) {
        if (curr_min > this->numbers[i]) {
            curr_min = this->numbers[i];
        }
    }
    return curr_min;
}

uint32_t Block::find_max() {
    uint32_t curr_max = this->numbers[0];
    for (int i = 1; i < this->elements; i++) {
        if (curr_max < this->numbers[i]) {
            curr_max = this->numbers[i];
        }
    }
    return curr_max;
}

void Block::subtract_reference() {
    for (int i = 0; i < this->elements; i++) {
        this->numbers[i] = this->numbers[i] - this->ref;
    }
}

uint8_t Block::get_bits(uint32_t number) {
    return (uint8_t)log2(number) + 1;
}
