#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include <string>
#include <sys/socket.h>
#include <sys/types.h>

class AcceptorSocket {
    const std::string service;
    int fd;

    private:
        socket_getaddrinfo(struct addrinfo** result, int ai_flags)

    public:
        AcceptorSocket();

        int bind();

        int listen();

        Socket accept(); //Return a new socket;

        ~AcceptorSocket();
};

#endif
