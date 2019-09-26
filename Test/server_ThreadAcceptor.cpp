#include "server_ThreadAcceptor.h"
#include "server_SocketAcceptor.h"
#include "server_ThreadClient.h"
#include "common_Socket.h"
#include <cstdbool>
#include <thread>
#include <string>
#include <vector>

#include <iostream>

ThreadAcceptor::ThreadAcceptor(std::string port) {
    this->acceptor.bind(port);
    this->acceptor.listen();
    this->server_running = true;
    //Socket ready to accept
}

void ThreadAcceptor::verify_clients() {
    return; //Verifica que los clientes sigan vivos
}

void ThreadAcceptor::run() {
    this->thread = std::thread(&ThreadAcceptor::accept_clients, this);
}

void ThreadAcceptor::accept_clients() {
    while (this->server_running) {
        Socket socket = this->acceptor.accept();

        ThreadClient* new_client = new ThreadClient(std::move(socket));
        this->clients.push_back(new_client);
        new_client->run();

        this->verify_clients();
    }
}

ThreadAcceptor::~ThreadAcceptor() {}
