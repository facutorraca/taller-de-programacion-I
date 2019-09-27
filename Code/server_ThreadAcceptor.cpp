#include "server_ThreadAcceptor.h"
#include "server_SocketAcceptor.h"
#include "server_ThreadClient.h"
#include "server_ProtectedSet.h"
#include "common_Socket.h"
#include <cstdbool>
#include <thread>
#include <string>
#include <vector>
#include <map>

ThreadAcceptor::ThreadAcceptor(const std::string port,
                               std::map<std::string, std::string>& config,
                               ProtectedSet& directories):
    directories(directories),
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
        }
    }
}

void ThreadAcceptor::run() {
    this->thread = std::thread(&ThreadAcceptor::accept_clients, this);
}

void ThreadAcceptor::accept_clients() {
    while (this->server_running) {
        Socket socket = this->acceptor.accept();

        ThreadClient* new_client = new ThreadClient(std::move(socket),
                                                    this->config,
                                                    this->directories);
        this->clients.push_back(new_client);
        new_client->run();

        this->verify_clients();
    }
}

ThreadAcceptor::~ThreadAcceptor() { }
