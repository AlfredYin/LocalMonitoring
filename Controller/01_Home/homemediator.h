#ifndef HOMEMEDIATOR_H
#define HOMEMEDIATOR_H

#include "deviceparam.h"
#include "Mediator.h"
#include "databasestatehelper.h"

class HomeMediator : public Mediator
{
public:
    HomeMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    void getDeviceStateList(DeviceParam *deviceParam);

    QString getConnectingDBType();

    bool isConnectedDb();

private:
    QList<QString> m_notificationInterests;
};

#endif // HOMEMEDIATOR_H
