#include "client_Input.h"
#include "client_Instruction.h"
#include "client_InstructionFactory.h"
#include <string>
#include <iostream>

Input::Input() {}

void Input::parse_input() {
    if (this->input.length() > 4) {
        this->inst_factory.set_instruction(this->input.substr(0, 4));
        this->inst_factory.set_args(this->input.substr(5, std::string::npos));
    } else {
        this->inst_factory.set_instruction(this->input.substr(0, 3));
    }
}

Instruction Input::get_instruction() {
    std::getline(std::cin, this->input);
    this->parse_input();
    return this->inst_factory.create_instruction();
}

Input::~Input() {}
