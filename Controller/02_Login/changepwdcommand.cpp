#include "changepwdcommand.h"
#include "Patterns/Facade.h"
#include "LoginProxy.h"
#include "loginresult.h"
#include "Interface/INotification.h"

#include <QDebug>

ChangePwdCommand::ChangePwdCommand()
{
    int a=0;
}

void ChangePwdCommand::excute(INotification *notification)
{
    LoginProxy *loginProxy = (LoginProxy *)Facade::getInstance()->retrieveProxy("LoginProxy");
    loginProxy->changePwd((LoginParam *)notification->getBody());
}
