#include "homemediator.h"
#include "INotification.h"

#include <QDebug>

HomeMediator::HomeMediator()
{
    MEDIATOR_NAME = "HomeMediator";

    m_notificationInterests.append("login_finished");
    m_notificationInterests.append("change_passwd_finished");
    m_notificationInterests.append("get_devicestatelist_finished");
    //    m_notificationInterests.append("mysql_connection_error");    
}

QList<QString> HomeMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void HomeMediator::handleNotification(INotification *notification)
{
    if (notification->getNotificationName() == "login_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "get_devicestatelist_finished"){
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "change_passwd_finished"){
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else{
        int a=0;
    }
}

void HomeMediator::getDeviceStateList(DeviceParam *deviceParam)
{
    sendNotification("get_devicestatelist", deviceParam);
}
