#ifndef _COMMAND_PWD_H_
#define _COMMAND_PWD_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandPwd : public Command {
    std::string answer;

    public:
        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        void send_answer(Socket& socket);
};

#endif
