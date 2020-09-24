#ifndef _SOCKET_ACCEPTOR_ERROR_H_
#define _SOCKET_ACCEPTOR_ERROR_H_

#include <stdexcept>

class SocketAcceptorError : public std::runtime_error {
    public:
        explicit SocketAcceptorError(const char* error): runtime_error(error) {}
};

#endif
