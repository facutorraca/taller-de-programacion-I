#ifndef _SOCKET_ERROR_H_
#define _SOCKET_ERROR_H_

#include <stdexcept>

class SocketError : public std::runtime_error {
    public:
        explicit SocketError(const char* error) : runtime_error(error) {}
};

#endif
