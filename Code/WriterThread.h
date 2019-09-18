#ifndef _WRITER_THREAD_H_
#define _WRITER_THREAD_H_

#include "ProtectedQueue.h"
#include "Writer.h"
#include <fstream>
#include <thread>
#include <cstdbool>

class WriterThread {

    Writer& writer;
    std::thread thread;
    std::vector<ProtectedQueue>& queues;

    private:

        void write_file();

        void show_results();

        bool queues_are_open();

        bool queues_are_empty();

    public:

        WriterThread(std::vector<ProtectedQueue>& queues, Writer& writer);

        void run();

        void join();
 
        ~WriterThread();

};

#endif
