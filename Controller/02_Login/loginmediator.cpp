#include "LoginMediator.h"

// 通知接口 INotification
#include "INotification.h"

#include "loginparam.h"
#include "loginresult.h"

#include <QDebug>

LoginMediator::LoginMediator()
{
    // 初始化名称，LoginMediator
    // 初始化了中介器的名称 MEDIATOR_NAME 为 "LoginMediator"
    MEDIATOR_NAME = "LoginMediator";

    // 将感兴趣的加入列表
    // m_notificationInterests 是一个保存该中介器感兴趣的通知类型的列表。在这里，它关注 "login_success" 和 "login_error" 两种通知。
    m_notificationInterests.append("login_finished");
    m_notificationInterests.append("change_passwd_finished");

//    m_notificationInterests.append("login_error");
}

// 返回 m_notificationInterests，即该中介器感兴趣的通知类型列表。
// 获取已注册感兴趣的通知列表
QList<QString> LoginMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

// 返回处理好的更新操作
// 处理接受到的信息
void LoginMediator::handleNotification(INotification *notification)
{
    // 用户输入数据到View Components后，由Mediator
    // 通知观察者Command数据更新（观察者模式中的发布）
    // 当通知的名称为 "login_success" 时，调用视图组件 m_viewComponent 的 update 方法，
    // 并传递通知的主体数据。notification->getBody() 返回一个指向更新数据的指针，该指针被强制转换为 IUpdateData 类型。
    if (notification->getNotificationName() == "login_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if (notification->getNotificationName() == "change_passwd_finished") {

        qDebug()<<"notification->getNotificationName() == change_passwd_finished";
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }
}

// doLogin 方法处理登录活动。
// 它发送一个名为 "login_check" 的通知，并将登录信息 loginInfo 作为通知的主体数据传递出去。
// sendNotification 方法用于将通知发送到系统中的其他部分（如 Command 或其他 Mediator）。
// 登录活动
void LoginMediator::doLogin(LoginParam *loginInfo)
{
    // 发送指令
    sendNotification("login_check", loginInfo);
}

void LoginMediator::changePwd(LoginParam *loginInfo)
{
    // 发送指令
    sendNotification("change_passwd", loginInfo);
}
