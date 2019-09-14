#include "Compressor.h"
#include "ProtectedQueue.h"
#include "CompressorThread.h"
#include <iostream>

/*--------------Public--------------*/
Compressor::Compressor(int num_thrds, size_t max_q_len, int block_len) {
    this->wrt_thread = new WriterThread(this->queues);
    this->num_thrds = num_thrds;
    this->init_queues(max_q_len);
    this->init_threads(block_len);
}

void Compressor::set_input_file(const char* i_filename) {
    this->i_file.open(i_filename, std::ios::binary);
    this->set_file_to_cmp_threads();
}

void Compressor::set_output_file(const char* o_filename) {
    this->o_file.open(o_filename, std::ios::binary);
    this->wrt_thread->set_file(&this->o_file);
}

void Compressor::compress() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->run();
    }
    this->wrt_thread->run();
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->join();
    }
    this->wrt_thread->join();
}

/*--------------Private-------------*/
void Compressor::init_threads(int block_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads.push_back(new CompressorThread(block_len, i, this->file_mtx));
        this->cmp_threads[i]->set_queue(this->queues[i]);
    }
}

void Compressor::init_queues(size_t max_q_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        this->queues.push_back(new ProtectedQueue(max_q_len));
    }
}

void Compressor::set_file_to_cmp_threads() {
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
