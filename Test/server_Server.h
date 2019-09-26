#ifndef _SERVER_H_
#define _SERVER_H_

#include "server_ThreadAcceptor.h"
#include <cstdbool>
#include <string>
#include <vector>

class Server {
    ThreadAcceptor* acceptor;

    public:
        explicit Server(const std::string port);

        void run();

        ~Server();
};

#endif
