#include "WriterThread.h"
#include "ProtectedQueue.h"
#include "Block.h"
#include <condition_variable>
#include <fstream>
#include <cstdbool>
#include <iostream>

/*--------------Public--------------*/
WriterThread::WriterThread(std::vector<ProtectedQueue*>& queues): queues(queues) {
    this->o_file = NULL;
}

void WriterThread::set_file(std::ofstream* o_file) {
    this->o_file = o_file;
}

void WriterThread::run() {
    //this->thread = std::thread(&WriterThread::write_file, this);
    this->write_file();
}

void WriterThread::join() {
    this->thread.join();
}

/*--------------Private-------------*/
void WriterThread::write_file() {
    while (!this->queues_are_empty() || this->queues_are_open()) {
        for (size_t i = 0; i < queues.size(); i++){
            //this->queues[i]->wait();
            Block* block = this->queues[i]->pop();
            block->print_in_file(this->o_file);
        }
    }
    int pop = this->queues[0]->get_pop();
    int push = this->queues[0]->get_push();

    std::cout << "Number of Push: " << push << " Numbers of Pop's " << pop << '\n';

    std::cout << "WriterThread finalized!" <<'\n';
}


bool WriterThread::queues_are_open() {
    bool open = false;
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (!this->queues[i]->closed()) {
            open = true;
        }
    }
    return open;
}

bool WriterThread::queues_are_empty() {
    bool empty = true;
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (!this->queues[i]->empty()) {
            empty = false;
        }
    }
    return empty;
}


WriterThread::~WriterThread() {}
