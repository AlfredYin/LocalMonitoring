#include "logincommand.h"
#include "Facade.h"
#include "userproxy.h"
#include "loginparam.h"
#include "userparam.h"
#include "userinfo.h"
#include "INotification.h"
#include "userhelper.h"
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
    userProxy->checkLogin(loginParam);      // 已经发送通知，前端已经改变

    // 回过头来获取登录信息,这个地方同步的
//    UserParam *userParam =new UserParam();
//    userParam->username=loginParam->name;
//    UserInfo userInfo=userProxy->getUserInfo(userParam);

//    UserHelper::instance()->setUserInfo(userInfo);

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
