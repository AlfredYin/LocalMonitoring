#ifndef LOGINCOMMAND_H
#define LOGINCOMMAND_H

#include "Command.h"

class LoginCommand : public Command
{
public:
    LoginCommand();

    void excute(INotification *notification);
};

#endif // LOGINCOMMAND_H
