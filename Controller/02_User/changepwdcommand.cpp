#include "changepwdcommand.h"
#include "Patterns/Facade.h"
#include "userproxy.h"
#include "loginresult.h"
#include "Interface/INotification.h"

#include <QDebug>

ChangePwdCommand::ChangePwdCommand()
{
    int a=0;
}

void ChangePwdCommand::excute(INotification *notification)
{
    UserProxy *userProxy = (UserProxy *)Facade::getInstance()->retrieveProxy("UserProxy");
    userProxy->changePwd((LoginParam *)notification->getBody());
}
