#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "common_Socket.h"
#include "server_LogState.h"
#include "server_CommandFactory.h"
#include <thread>
#include <cstdbool>

class ThreadClient {
    User user;
    bool alive;
    Socket socket;
    std::thread thread;
    CommandFactory cmd_factory;

    private:
        void communicate();

        void interpret_command(std::string cmd);

    public:
        ThreadClient(Socket socket);

        void run();

        ~ThreadClient();
};

#endif
