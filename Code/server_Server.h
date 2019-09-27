#ifndef _SERVER_H_
#define _SERVER_H_

#include "server_ThreadAcceptor.h"
#include <cstdbool>
#include <string>
#include <vector>

class Server {
    ThreadAcceptor* acceptor;

    private:
        void control_quit();

    public:
        Server(const std::string port);

        void start();

        ~Server();
};

#endif
