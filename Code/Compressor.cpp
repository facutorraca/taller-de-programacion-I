#include "Compressor.h"
#include "ProtectedQueue.h"
#include "ThreadCompressor.h"
#include <iostream>

/*--------------Public--------------*/

Compressor::Compressor(int num_thrds, size_t max_q_len, int block_len) {
    this->num_thrds = num_thrds;
    this->max_q_len = max_q_len;
    this->block_len = block_len;
    this->init_queues();
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
        this->cmp_threads[i]->run();
    }
    //Aca va un join:
}

/*--------------Private-------------*/

void Compressor::init_threads() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads.push_back(new ThreadCompressor(this->block_len, i, this->mtx));
        this->cmp_threads[i]->set_queue(this->queues[i]);
    }
}

void Compressor::init_queues() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->queues.push_back(new ProtectedQueue(this->max_q_len));
    }
}

void Compressor::set_file_to_threads() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->set_file(&this->i_file);
    }
}

Compressor::~Compressor() {
    this->cmp_threads.clear();

    if (this->i_file.is_open()) {
        this->i_file.close();
    }
    if (this->o_file.is_open()) {
        this->o_file.close();
    }
}
