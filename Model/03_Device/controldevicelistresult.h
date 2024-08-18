#ifndef CONTROLDEVICELISTRESULT_H
#define CONTROLDEVICELISTRESULT_H

#include "devicestateinfo.h"
#include "baseresult.h"

//class ControlDeviceListResult : public BaseResult
class ControlDeviceListResult
{
public:
    ControlDeviceListResult();

    QList<ControlDeviceState> resultControlDeviceStateList;
};

#endif // CONTROLDEVICELISTRESULT_H
