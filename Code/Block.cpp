#include "Block.h"
#include <cstdint>
#include <iostream>

//Default Constructor
Block::Block(uint32_t ref, uint8_t bits) {
    this->ref = ref;
    this->bits = bits;
}

void Block::print() {
    std::cout << " Ref " << this->ref << " Bits " << unsigned(this->bits) << '\n';
}
