#ifndef _SOCKET_H_
#define _SOCKET_H_

class Socket {
    int fd;

    public:

        explicit Socket(int fd);

        int send();

        int receive();

        ~Socket();

}

#endif
