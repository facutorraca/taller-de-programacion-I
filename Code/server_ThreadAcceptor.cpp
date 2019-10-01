#include "server_ThreadAcceptor.h"
#include "server_SocketAcceptor.h"
#include "server_ThreadClient.h"
#include "server_ProtectedSet.h"
#include "server_SocketAcceptorError.h"
#include "common_Socket.h"
#include <cstdbool>
#include <thread>
#include <string>
#include <vector>
#include <map>

#include <iostream>
ThreadAcceptor::ThreadAcceptor(const std::string port,
                               std::map<std::string, std::string>& config,
                               ProtectedSet& directories,
                               std::vector<ThreadClient*>& clients):
    directories(directories),
    clients(clients),
    config(config)
{
    this->acceptor.bind(port);
    this->acceptor.listen();
    this->server_running = true;
    //Socket ready to accept
}

void ThreadAcceptor::verify_clients() {
    for (size_t i = 0; i < this->clients.size(); i++) {
        if (this->clients[i]->is_dead()) {
            this->clients[i]->join();
            delete this->clients[i];
            this->clients.erase(this->clients.begin() + i);
        }
    }
}

void ThreadAcceptor::stop() {
    this->acceptor.close();
}

void ThreadAcceptor::run() {
    while (this->server_running) {
        try {
            Socket socket = this->acceptor.accept();

            ThreadClient* new_client = new ThreadClient(std::move(socket),
                                                        this->config,
                                                        this->directories);
            new_client->start();
            this->clients.push_back(new_client);

            this->verify_clients();
        } catch(const SocketAcceptorError &exception) {
            this->server_running = false;
        }
    }
}

ThreadAcceptor::~ThreadAcceptor() {}
