#include "client_Client.h"
#include "client_ServerProxy.h"
#include "client_Instruction.h"
#include <string>
#include <iostream>

Client::Client(const std::string host, const std::string port):
    port(port),
    host(host)
{}

void Client::connect() {
    this->server.connect(this->port, this->host);
}

void Client::send(Instruction inst) {
    inst.send(&this->server);
}

Client::~Client() {}
