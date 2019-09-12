#ifndef _BLOCK_BUFFER_H_
#define _BLOCK_BUFFER_H_

#include <cstdint>
#include <iostream>

#define DW_BYTES 4

class BlockBuffer {

    uint32_t* buffer;
    int buff_len;
    int curr_pos;


    public:

        BlockBuffer(int num_dble_words) {
            this->buff_len = num_dble_words;
            this->clear(); //Clear the buffer
            this->buffer = new uint32_t[this->buff_len];
        }

        void push_back(char* number_as_str);

        uint32_t pop_back();

        uint32_t find_min();

        uint32_t find_max();

        void substract_from_element(uint32_t min);

        void print();

        void clear();

        ~BlockBuffer() {
            delete [] buffer;
        }
};


#endif
