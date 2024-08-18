#include "historydatamediator.h"
#include "INotification.h"

HistoryDataMediator::HistoryDataMediator()
{
    MEDIATOR_NAME = "HistoryDataMediator";
    m_notificationInterests.append("get_historydata_finished");
    //    m_notificationInterests.append("change_passwd_finished");
}

QList<QString> HistoryDataMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void HistoryDataMediator::handleNotification(INotification *notification)
{
    if (notification->getNotificationName() == "get_historydata_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }/*else if (notification->getNotificationName() == "change_passwd_finished") {

        qDebug()<<"notification->getNotificationName() == change_passwd_finished";
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }*/
}

void HistoryDataMediator::getSensorHistoryData(SensorParam *sensorParam)
{
    sendNotification("get_historydata",sensorParam);
}


