#ifndef LOGINCOMMAND_H
#define LOGINCOMMAND_H

#include "Command.h"

#include <QtConcurrent/QtConcurrent>

class LoginCommand : public Command
{
public:
    LoginCommand();

    void excute(INotification *notification);
};

#endif // LOGINCOMMAND_H
