#ifndef DEVICEPROXY_H
#define DEVICEPROXY_H

#include "Proxy.h"
#include "deviceparam.h"
#include "devicestateresult.h"

class DeviceProxy : public Proxy
{
public:
    DeviceProxy();

    void getDevicestate(DeviceParam *deviceParam);
};

#endif // DEVICEPROXY_H
