#ifndef CONTROLDEVICESTATERESULT_H
#define CONTROLDEVICESTATERESULT_H

#include "devicestateinfo.h"
#include "baseresult.h"

class ControlDeviceStateResult : public BaseResult
{
public:
    ControlDeviceStateResult();

//     QList<ControlDeviceState> resultControlDeviceStateList;
    ControlDeviceState resultControlDeviceState;
};

#endif // CONTROLDEVICESTATERESULT_H
