#include "server_Server.h"
#include <string>
#include <cstdbool>
#include <iostream>

Server::Server(const std::string port) {
    this->acceptor = new ThreadAcceptor(port);
}

void Server::run() {
    this->acceptor->run();

    bool quit = false;
    while (!quit) {
        char cmd = std::cin.get();
        if (cmd == 'q') {
            quit = true;
        }
    }
    std::cout << "Chau!" <<'\n';

}

Server::~Server() {}
