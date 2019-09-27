#ifndef _COMMAND_UNKNOW_H_
#define _COMMAND_UNKNOW_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include <string>

class CommandUnknown : public Command {
    public:
        void execute(User& user, Socket& socket);

        ~CommandUnknown();
};

#endif
