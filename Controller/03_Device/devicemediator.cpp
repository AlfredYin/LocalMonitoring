#include "devicemediator.h"
#include "deviceproxy.h"

DeviceMediator::DeviceMediator()
{
    // 初始化名称，LoginMediator
    // 初始化了中介器的名称 MEDIATOR_NAME 为 "LoginMediator"
    MEDIATOR_NAME = "DeviceMediator";

    // 将感兴趣的加入列表
    // m_notificationInterests 是一个保存该中介器感兴趣的通知类型的列表。在这里，它关注 "login_success" 和 "login_error" 两种通知。
//    m_notificationInterests.append("get_devicestatelist_finished");
}

QList<QString> DeviceMediator::getListNotificationInterests()
{
    return m_notificationInterests;
}

void DeviceMediator::handleNotification(INotification *notification)
{
//    if (notification->getNotificationName() == "get_devicestatelist_finished")
//    {
//        m_viewComponent->update((IUpdateData *)notification->getBody());
//    }
}

void DeviceMediator::getDeviceState(DeviceParam *deviceParam)
{
    // 发送指令
    sendNotification("get_devicestate", deviceParam);
}

void DeviceMediator::getDeviceStateList(DeviceParam *deviceParam)
{
    sendNotification("get_devicestatelist", deviceParam);
}

SensorStateResult DeviceMediator::getSensorStateList(DeviceParam *deviceParam)
{
    DeviceProxy deviceProxy;
    return deviceProxy.getSensorStateList(deviceParam);
}

ControlDeviceListResult DeviceMediator::getControlDeviceStateList(DeviceParam *deviceParam)
{
    DeviceProxy deviceProxy;
    return deviceProxy.getControlDeviceStateList(deviceParam);
}

void DeviceMediator::sendMqttControlDeviceCommand(ControlDeviceState *controlDeviceParam)
{
    sendNotification("send_mqttcontroldevicecommand",controlDeviceParam);
}
