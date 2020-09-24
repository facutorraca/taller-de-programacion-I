#ifndef _WRITER_THREAD_H_
#define _WRITER_THREAD_H_

#include "ProtectedQueue.h"
#include "Writer.h"
#include <thread>
#include <vector>
#include <cstdbool>

class WriterThread {
    Writer& writer;
    std::thread thread;
    std::vector<ProtectedQueue>& queues;

    private:
        void write_file();

        bool queues_are_open();

        bool queues_are_empty();

    public:
        explicit WriterThread(std::vector<ProtectedQueue>& queues,
                              Writer& writer);

        void start();

        void join();

        ~WriterThread();
};

#endif
