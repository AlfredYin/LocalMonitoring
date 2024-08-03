#include "mainwindowmediator.h"
#include "INotification.h"

#include <QDebug>

MainWindowMediator::MainWindowMediator()
{
    MEDIATOR_NAME = "MainWindowMediator";

    m_notificationInterests.append("login_finished");
    m_notificationInterests.append("change_passwd_finished");
    //    m_notificationInterests.append("mysql_connection_error");
}

QList<QString> MainWindowMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void MainWindowMediator::handleNotification(INotification *notification)
{
    if (notification->getNotificationName() == "login_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "change_passwd_finished"){
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "mysql_connection_error"){

    }else{
        int a=0;
    }
}
