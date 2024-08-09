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

    // 获取单个设备状态
    void getDeviceState(DeviceParam *deviceStateInfo);

    // 获取设备连接列表
    void getDeviceStateList(DeviceParam *deviceStateInfo);

private:
    QList<QString> m_notificationInterests;
};

#endif // DEVICEMEDIATOR_H
