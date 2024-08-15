#ifndef DEVICEMEDIATOR_H
#define DEVICEMEDIATOR_H

#include "Patterns/Mediator.h"
#include "Command.h"
#include <QtConcurrent/QtConcurrent>

#include "deviceparam.h"
#include "devicestateresult.h"
#include "sensorstateresult.h"
#include "controldevicestateresult.h"

class DeviceMediator : public Mediator , public Command
{
public:
    DeviceMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    // 获取单个设备状态
    void getDeviceState(DeviceParam *deviceStateInfo);

    // 获取设备连接列表
    void getDeviceStateList(DeviceParam *deviceStateInfoParam);

    SensorStateResult getSensorStateList(DeviceParam *deviceParam);

    ControlDeviceStateResult getControlDeviceStateList(DeviceParam *deviceParam);

private:
    QList<QString> m_notificationInterests;
};

#endif // DEVICEMEDIATOR_H
