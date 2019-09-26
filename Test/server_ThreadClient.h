#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "common_Socket.h"
#include <cstdbool>
#include <thread>

class ThreadClient {
    bool alive;
    Socket socket;
    std::thread thread;

    private:
        void communicate();

    public:
        ThreadClient(Socket socket);

        void run();

        ~ThreadClient();
};

#endif
