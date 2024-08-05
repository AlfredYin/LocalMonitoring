#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include "Proxy.h"
#include "deviceparam.h"
#include "devicestateresult.h"

class DeviceProxy : public Proxy
{
public:
    DeviceProxy();

    void getDeviceState(DeviceParam *deviceParam);

    void getDeviceStatesList(DeviceParam *deviceParam);

    private
};

#endif // DEVICEPROXY_H
