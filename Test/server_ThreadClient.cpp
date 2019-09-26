#include "server_ThreadClient.h"
#include "common_Socket.h"
#include <cstdbool>
#include <iostream>
#include <string>
#include <thread>


ThreadClient::ThreadClient(Socket socket):
    socket(std::move(socket))
{
    this->alive = true;
}

void ThreadClient::run() {
    this->thread = std::thread(&ThreadClient::communicate, this);
}

void ThreadClient::communicate() {
    std::string buf;
    while (this->alive) {
        this->socket.receive(buf);
        std::cout << buf;
    }
}

ThreadClient::~ThreadClient() {}
