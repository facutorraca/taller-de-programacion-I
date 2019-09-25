#ifndef _SOCKET_H_
#define _SOCKET_H_

class Socket {
    int fd;

    private:
        socket_getaddrinfo(struct addrinfo** result, int ai_flags)

    public:

        Socket();

        Socket(int fd);

        int send(const char* msg, size_t len);

        int receive(char* buf, size_t len);

        int connect();

        ~Socket();
}

#endif
