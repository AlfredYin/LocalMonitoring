#include "LoginCommand.h"
#include "Facade.h"
#include "LoginProxy.h"
#include "loginparam.h"
#include "INotification.h"

#include <QDebug>

LoginCommand::LoginCommand()
{
}

//  Command（命令）表示一个执行操作或命令的对象。通常封装了一个操作或一系列操作，并且可以调用 Proxy 完成业务逻辑。
void LoginCommand::excute(INotification *notification)
{
    LoginProxy *loginProxy = (LoginProxy *)Facade::getInstance()->retrieveProxy("LoginProxy");
    loginProxy->checkLogin((LoginParam *)notification->getBody());
}
