#include "client_Client.h"
#include "client_ServerProxy.h"
#include "client_Instruction.h"
#include <string>
#include <iostream>

Client::Client(const std::string host, const std::string port):
    server(host, port) {}

void Client::run() {
    while (true) {
        Instruction instruction = this->input.get_instruction();
        instruction.execute(&this->server);
    }
}

Client::~Client() {}
