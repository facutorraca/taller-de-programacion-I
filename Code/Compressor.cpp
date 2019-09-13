#include "Compressor.h"
#include "ThreadCompressor.h"
#include <iostream>

/*--------------Public--------------*/

Compressor::Compressor(int num_thrds, size_t max_q_len, int block_len) {
    this->num_thrds = num_thrds;
    this->max_q_len = max_q_len;
    this->block_len = block_len;
    this->init_threads();
}

void Compressor::set_input_file(const char* i_filename) {
    this->i_file.open(i_filename, std::ios::binary);
    this->set_file_to_threads();
}

void Compressor::set_output_file(const char* o_filename) {
    this->o_file.open(o_filename, std::ios::binary);
}

void Compressor::compress() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->threads[i].compress();
    }
}

/*--------------Private-------------*/

void Compressor::init_threads() {
    for (int i = 0; i < this->num_thrds; i++) {
        ThreadCompressor thread(this->block_len, i, this->max_q_len);
        this->threads.push_back(thread);
    }
}

void Compressor::set_file_to_threads() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->threads[i].set_file(&this->i_file);
    }
}

Compressor::~Compressor() {
    threads.clear();

    if (i_file.is_open()) {
        i_file.close();
    }
    if (o_file.is_open()) {
        o_file.close();
    }
}
