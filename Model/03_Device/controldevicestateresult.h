#ifndef CONTROLDEVICESTATERESULT_H
#define CONTROLDEVICESTATERESULT_H

#include "devicestateinfo.h"

class ControlDeviceStateResult
{
public:
    ControlDeviceStateResult();

     QList<ControlDeviceState> resultControlDeviceStateList;
};

#endif // CONTROLDEVICESTATERESULT_H
