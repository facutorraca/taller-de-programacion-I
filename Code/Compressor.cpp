#include "Compressor.h"
#include "Reader.h"
#include "Writer.h"
#include "ProtectedQueue.h"
#include "CompressorThread.h"
#include <iostream>

/*--------------Public--------------*/
Compressor::Compressor(int num_thrds, size_t max_q_len, int block_len) : reader(block_len) {
    this->wtr_thread = new WriterThread(this->queues, this->writer); //By Reference
    this->num_thrds = num_thrds;
    this->init_queues(max_q_len);
    this->init_threads(block_len);
}

void Compressor::set_input_file(const char* i_filename) {
    this->reader.set_file(i_filename);
}

void Compressor::set_output_file(const char* o_filename) {
    this->writer.set_file(o_filename);
}

void Compressor::compress() {
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->run();
    }
    this->wtr_thread->run();
    for (int i = 0; i < this->num_thrds; i++) {
        this->cmp_threads[i]->join();
    }
    this->wtr_thread->join();
    std::cerr << "Threads Closed" << '\n';
}

/*--------------Private-------------*/
void Compressor::init_threads(int block_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        CompressorThread* cmp_thread = new CompressorThread(block_len, i, this->num_thrds, this->reader);
        this->cmp_threads.push_back(cmp_thread); //By pointer
        this->cmp_threads[i]->set_queue(this->queues[i]); //By reference
    }
}

void Compressor::init_queues(size_t max_q_len) {
    for (int i = 0; i < this->num_thrds; i++) {
        ProtectedQueue* queue = new ProtectedQueue(max_q_len);
        this->queues.push_back(queue); //By pointer
    }
}

Compressor::~Compressor() {
    this->cmp_threads.clear();
    //Destroy queues
    //Destroy threads
}
