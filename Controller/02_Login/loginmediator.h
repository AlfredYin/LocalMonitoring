#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include "Patterns/Mediator.h"
#include "loginparam.h"
#include "loginresult.h"

class LoginInfo;

// Login Mediator
// Mediator 是视图组件（如窗口、对话框、按钮等）的中介。
// 它负责处理视图组件的事件，并将这些事件传递给 Facade 或其他组件。它也可以接收来自 Facade 或 Proxy 的通知，并更新视图。
// 管理和协调不同组件之间的通信。注册各个组件并管理它们之间的消息传递。

// Mediator：Mediator 监听这些操作，并将事件传递给 Facade。

class LoginMediator : public Mediator
{
public:
    LoginMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    // special
    void doLogin(LoginParam *loginInfo);

    void changePwd(LoginParam *loginInfo);

private:
    QList<QString> m_notificationInterests;
};

#endif // LOGINMEDIATOR_H
