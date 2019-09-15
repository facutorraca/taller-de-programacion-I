#ifndef _WRITER_THREAD_H_
#define _WRITER_THREAD_H_

#include "ProtectedQueue.h"
#include <fstream>
#include <thread>
#include <cstdbool>

class WriterThread {

    std::ofstream* o_file;
    std::thread thread;
    std::vector<ProtectedQueue*>& queues;

    private:

        void write_file();

        bool queues_are_open();

        bool queues_are_empty();

    public:

        WriterThread(std::vector<ProtectedQueue*>& queues);

        void set_file(std::ofstream* o_file);

        void run();

        void join();

        ~WriterThread();

};

#endif
