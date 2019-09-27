#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "client_ServerProxy.h"
#include <string>

class Client {
    ServerProxy server;

    public:
        Client(const std::string host, const std::string port);

        void start();

        ~Client();
};

#endif
