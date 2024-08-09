#ifndef HOMEMEDIATOR_H
#define HOMEMEDIATOR_H

#include "deviceparam.h"
#include "Patterns/Mediator.h"

class HomeMediator : public Mediator
{
public:
    HomeMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    void getDeviceStateList(DeviceParam *deviceParam);

private:
    QList<QString> m_notificationInterests;
};

#endif // HOMEMEDIATOR_H
