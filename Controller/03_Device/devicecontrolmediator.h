#ifndef DEVICECONTROLMEDIATOR_H
#define DEVICECONTROLMEDIATOR_H

#include "Mediator.h"

class DeviceControlMediator : public Mediator
{
public:
    DeviceControlMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

private:
    QList<QString> m_notificationInterests;
};

#endif // DEVICECONTROLMEDIATOR_H
