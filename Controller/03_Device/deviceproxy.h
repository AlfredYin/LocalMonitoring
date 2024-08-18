#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include "Proxy.h"
#include "deviceparam.h"
#include "devicestateresult.h"
#include "databaserepository.h"
#include "sensorstateresult.h"
#include "controldevicestateresult.h"
#include "controldevicelistresult.h"

class DeviceProxy : public Proxy , DataBaseRepository
{
public:
    DeviceProxy();

    void getDeviceState(DeviceParam *deviceParam);

    void getDeviceStatesList(DeviceParam *deviceParam);

    SensorStateResult getSensorStateList(DeviceParam *deviceParam);

    ControlDeviceListResult getControlDeviceStateList(DeviceParam *deviceParam);

private:
    DeviceParam m_DeviceParam;

    QList<QPair<QString, QVariant>> RegisterListFilter(DeviceParam *deviceParam);
    QString RegisterStrFilter(DeviceParam *deviceParam);
};

#endif // DEVICEPROXY_H
