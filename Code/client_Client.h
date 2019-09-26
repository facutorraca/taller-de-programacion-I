#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "common_Socket.h"
#include "client_ServerProxy.h"
#include "client_Instruction.h"
#include <string>

class Client {
    ServerProxy server;
    Input input;

    public:
        explicit Client(const std::string host, const std::string port);

        void send(Instruction instruction);

        void run();

        ~Client();
};

#endif
