#include "mainwindowmediator.h"

#include "INotification.h"
#include "Patterns/Mediator.h"

#include <QDebug>

MainWindowMediator::MainWindowMediator()
{
    MEDIATOR_NAME = "MainWindowMediator";
    m_notificationInterests.append("get_ntptime_finished");
}

QList<QString> MainWindowMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void MainWindowMediator::handleNotification(INotification *notification)
{
    if(notification->getNotificationName() == "get_ntptime_finished"){
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }else if(notification->getNotificationName() == "mysql_connection_error"){

    }
}

void MainWindowMediator::startGetNtpTime()
{
    sendNotification("start_getntptime", nullptr);
}
