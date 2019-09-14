#include "WriterThread.h"
#include "ProtectedQueue.h"
#include "Block.h"
#include <condition_variable>
#include <fstream>

/*--------------Public--------------*/
WriterThread::WriterThread(std::vector<ProtectedQueue*>& queues): queues(queues) {
    this->o_file = NULL;
}

void WriterThread::set_file(std::ofstream* o_file) {
    this->o_file = o_file;
}

void WriterThread::run() {
    this->thread = std::thread(&WriterThread::write_file, this);
}

void WriterThread::join() {
    this->thread.join();
}

/*--------------Private-------------*/
void WriterThread::write_file() {
    while (true) {
        for (size_t i = 0; i < queues.size(); i++){
            this->queues[i]->wait();
            Block block = this->queues[i]->pop();
            block.print();
        }
    }
}

WriterThread::~WriterThread() {}
