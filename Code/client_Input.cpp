#include "client_Input.h"
#include "client_Command.h"
#include "client_CommandFactory.h"
#include <string>
#include <iostream>

Input::Input() {}

void Input::parse_input() {
    if (this->input.length() > 4) {
        this->cmd_factory.set_command(this->input.substr(0, 4));
        this->cmd_factory.set_argument(this->input.substr(5, std::string::npos));
    } else if (this->input.length() == 4) {
        this->cmd_factory.set_command(this->input.substr(0, 4));
    } else {
        this->cmd_factory.set_command(this->input.substr(0, 3));
    }
}

Command Input::get_command() {
    std::getline(std::cin, this->input);
    this->parse_input();
    return this->cmd_factory.create_command();
}

Input::~Input() {}
