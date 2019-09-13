#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <cstdint>

class Block {

    uint8_t bits;
    uint32_t ref;

    public:
        
        Block(uint32_t ref, uint8_t bits);

        void print();

};

#endif
