#ifndef _SERVER_PROXY_H_
#define _SERVER_PROXY_H_

#include "common_Socket.h"
#include <string>

class ServerProxy {
    Socket c_socket;

    public:
        ServerProxy();

        void connect(const std::string host, const std::string port);

        void send(std::string msg);

        ~ServerProxy();
};

#endif
