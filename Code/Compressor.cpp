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
    this->init_queues(max_q_len);
    this->init_threads(block_len);
    this->wtr_thread = new WriterThread(this->queues, this->writer);
}

void Compressor::set_input_file(const char* i_filename) {
    this->reader.set_file(i_filename);
}

void Compressor::set_output_file(const char* o_filename) {
    this->writer.set_file(o_filename);
}

void Compressor::compress() {
    for (int i = 0; i < cmp_threads.size(); i++) {
        this->cmp_threads[i]->run();
    }
    this->wtr_thread->run();
    for (int i = 0; i < cmp_threads.size(); i++) {
        this->cmp_threads[i]->join();
    }
    this->wtr_thread->join();
    std::cerr << "Threads Closed" << '\n';
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
    this->cmp_threads.clear();
    //Destroy queues
    //Destroy threads
}
