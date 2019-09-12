#include "Compressor.h"
#include "Collector.h"
#include <cmath>


/*--------------Public--------------*/

void Compressor::compress() {
    uint32_t min;
    while (this->collectors[0].collect()) {
        min = this->collectors[0].find_min();
        this->process_block(min);
        this->collectors[0].clear();
    }
}

/*--------------Private-------------*/

void Compressor::init_collectors(int threads, int blk_len) {
    for (int i = 0; i < threads; i++) {
        Collector collector(&this->i_file, blk_len);
        this->collectors.push_back(collector);
    }
}

uint32_t Compressor::find_minimal_bits(uint32_t number) {
      return (uint32_t)log2(number) + 1;
}


void Compressor::process_block(uint32_t min) {
    this->collectors[0].substract_from_element(min);
    uint32_t max = this->collectors[0].find_max();
    uint32_t num_bits = this->find_minimal_bits(max);
}
