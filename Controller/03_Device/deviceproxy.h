#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include "Proxy.h"
#include "deviceparam.h"
#include "devicestateresult.h"
#include "mysqldbrepository.h"

class DeviceProxy : public Proxy , MySqlDBRepository
{
public:
    DeviceProxy();

    void getDeviceState(DeviceParam *deviceParam);

    void getDeviceStatesList(DeviceParam *deviceParam);

private:
    DeviceParam m_DeviceParam;

    QList<QPair<QString, QVariant>> RegisterListFilter(DeviceParam *deviceParam);
    QString RegisterStrFilter(DeviceParam *deviceParam);
};

#endif // DEVICEPROXY_H
