#include "devicecontrolmediator.h"
#include "INotification.h"

DeviceControlMediator::DeviceControlMediator()
{
    MEDIATOR_NAME = "DeviceControlMediator";

    m_notificationInterests.append("devicecontrolsendcommand_finished");
}

QList<QString> DeviceControlMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void DeviceControlMediator::handleNotification(INotification *notification)
{
    if (notification->getNotificationName() == "devicecontrolsendcommand_finished")
    {
        m_viewComponent->update((IUpdateData *)notification->getBody());
    }
}
