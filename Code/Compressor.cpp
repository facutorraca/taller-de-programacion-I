#include "Compressor.h"
#include "Reader.h"
#include "Writer.h"
#include "ProtectedQueue.h"
#include "CompressorThread.h"
#include <iostream>

/*--------------Public--------------*/
Compressor::Compressor(int num_thrds, size_t max_q_len, size_t block_len):
    reader(block_len)
{
    this->init_queues(max_q_len, num_thrds);
    this->init_threads(block_len, num_thrds);
    this->wtr_thread = new WriterThread(this->queues, this->writer);
}

int Compressor::set_input_file(const char* i_filename) {
    return this->reader.set_file(i_filename);
}

int Compressor::set_output_file(const char* o_filename) {
    return this->writer.set_file(o_filename);
}

void Compressor::compress() {
    for (size_t i = 0; i < cmp_threads.size(); i++) {
        this->cmp_threads[i]->run();
    }
    this->wtr_thread->run();
    for (size_t i = 0; i < cmp_threads.size(); i++) {
        this->cmp_threads[i]->join();
    }
    this->wtr_thread->join();
}

/*--------------Private-------------*/
void Compressor::init_threads(size_t block_len, int num_thrds) {
    for (int i = 0; i < num_thrds; i++) {
        CompressorThread* cmp_thread = new CompressorThread(block_len,
                                                            i,
                                                            num_thrds,
                                                            this->reader,
                                                            this->queues[i]);
        this->cmp_threads.push_back(cmp_thread);
    }
}

void Compressor::init_queues(size_t max_q_len, int num_thrds) {
    for (int i = 0; i < num_thrds; i++) {
        this->queues.emplace_back(ProtectedQueue(max_q_len));
    }
}

Compressor::~Compressor() {
    delete this->wtr_thread;
    for (size_t i = 0; i < this->cmp_threads.size(); i++) {
        delete this->cmp_threads[i];
    }
}
