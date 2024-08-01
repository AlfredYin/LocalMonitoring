#include "ApplicationMediator.h"
#include "Interface/INotification.h"

#include <QDebug>

ApplicationMediator::ApplicationMediator()
{
    MEDIATOR_NAME = "ApplicationMediator";

    m_notificationInterests.append("login_finished");
    m_notificationInterests.append("change_passwd_finished");
    m_notificationInterests.append("mysql_connection_error");
}

QList<QString> ApplicationMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void ApplicationMediator::handleNotification(INotification *notification)
{
    if (notification->getNotificationName() == "login_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "change_passwd_finished"){
        int a=0;
    }else if(notification->getNotificationName() == "mysql_connection_error"){

    }else{
        int a=0;
    }
}
