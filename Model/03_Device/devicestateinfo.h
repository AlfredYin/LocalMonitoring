#ifndef DEVICESTATEINFO_H
#define DEVICESTATEINFO_H

#include "devicestateresult.h"
#include "baseinfo.h"

class SensorState;
class DeivceState;

class DeviceStateInfo : public BaseInfo
{
public:
    DeviceStateInfo();

public:
    QString devicename;

//    QString connectstate;   // online / offline

    int connectingflag;   // 0:offline / 1:online

    QList<DeivceState> subdevicestatelist;

};

#endif // DEVICESTATEINFO_H
