#ifndef DEVICEMEDIATOR_H
#define DEVICEMEDIATOR_H

#include "Patterns/Mediator.h"

#include "deviceparam.h"
#include "devicestateresult.h"

class DeviceMediator : public Mediator
{
public:
    DeviceMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    // special
    void getDeviceState(DeviceParam *deviceStateInfo);

private:
    QList<QString> m_notificationInterests;
};

#endif // DEVICEMEDIATOR_H
