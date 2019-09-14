#ifndef _WRITER_THREAD_H_
#define _WRITER_THREAD_H_

#include "ProtectedQueue.h"
#include <fstream>
#include <thread>

class WriterThread {

    std::ofstream* o_file;
    std::thread thread;
    std::vector<ProtectedQueue*>& queues;

    private:

        void write_file();

    public:

        WriterThread(std::vector<ProtectedQueue*>& queues);

        void set_file(std::ofstream* o_file);

        void run();

        void join();

        ~WriterThread();

};

#endif
