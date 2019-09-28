#ifndef _COMMAND_LIST_H_
#define _COMMAND_LIST_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <vector>
#include <map>

class CommandList : public Command {
    std::vector<std::string> answers;

    public:
        CommandList();

        int send_answer(Socket& socket);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        ~CommandList();
};

#endif
