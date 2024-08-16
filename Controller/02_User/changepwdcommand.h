#ifndef CHANGEPWDCOMMAND_H
#define CHANGEPWDCOMMAND_H

#include "loginparam.h"
#include "Command.h"

class ChangePwdCommand : public Command
{
public:
    ChangePwdCommand();

    void excute(INotification *notification);
};

#endif // CHANGEPWDCOMMAND_H
