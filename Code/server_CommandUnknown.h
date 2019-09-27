#ifndef _COMMAND_UNKNOW_H_
#define _COMMAND_UNKNOW_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

class CommandUnknown : public Command {
    std::string answer;

    public:
        void execute(User& user);

        void send_answer(Socket& socket);

        ~CommandUnknown();
};

#endif
