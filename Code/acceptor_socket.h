#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include <string>

class AcceptorSocket {
    const std::string service;
    int fd;

    public:

        AcceptorSocket();

        int bind();

        int listen();

        Socket accept(); //Return a new socket;

        ~AcceptorSocket();
};

#endif
