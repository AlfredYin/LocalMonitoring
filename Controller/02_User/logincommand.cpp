#include "logincommand.h"
#include "Facade.h"
#include "userproxy.h"
#include "loginparam.h"
#include "userparam.h"
#include "userinfo.h"
#include "INotification.h"

#include "homeproxy.h"

#include <QDebug>

LoginCommand::LoginCommand()
{
}

//  Command（命令）表示一个执行操作或命令的对象。通常封装了一个操作或一系列操作，并且可以调用 Proxy 完成业务逻辑。
void LoginCommand::excute(INotification *notification)
{
    UserProxy *userProxy = (UserProxy *)Facade::getInstance()->retrieveProxy("UserProxy");
    LoginParam *loginParam = (LoginParam *)notification->getBody();
    userProxy->checkLogin(loginParam);

    // 因为checkLogin改为异步方法，不能使用同步方法获取是否登录状态
//    if(userProxy->checkLogin(loginParam)){
//        UserParam *userParam = new UserParam();
//        userParam->username=loginParam->name;

//        HomeProxy *homeProxy = (HomeProxy *)Facade::getInstance()->retrieveProxy("HomeProxy");
//        UserInfo userInfo=userProxy->getUserInfo(userParam);
//        homeProxy->saveUser(&userInfo);

//    }else{
//        return ;
//    }
}
