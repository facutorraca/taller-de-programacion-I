#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "common_Socket.h"
#include "client_ServerProxy.h"
#include <string>

class Client {
    ServerProxy server;
    std::string port;
    std::string host;

    public:
        explicit Client(const std::string host, const std::string port);

        void connect();

        void send(std::string msg);

        ~Client();
};

#endif
