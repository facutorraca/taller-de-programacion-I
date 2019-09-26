#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "client_ServerProxy.h"
#include <string>

class Client {
    ServerProxy server;

    private:
        void read_input(std::string& buf);

    public:
        explicit Client(const std::string host, const std::string port);

        void run();

        ~Client();
};

#endif
