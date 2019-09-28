#ifndef _COMMAND_UNKNOW_H_
#define _COMMAND_UNKNOW_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>

class CommandUnknown : public Command {
    std::string answer;

    public:
        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        int send_answer(Socket& socket);

        ~CommandUnknown();
};

#endif
