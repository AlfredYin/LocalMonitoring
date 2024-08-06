#ifndef DEVICESTATERESULT_H
#define DEVICESTATERESULT_H

#include "baseresult.h"

class SensorState;
class DeivceState;

class DeviceStateResult : public BaseResult
{
public:
    DeviceStateResult();

public:
    QList<DeivceState> devicestatelist;
};

class DeivceState{
    QString devicename;
    QString devicestate;
    QList<SensorState> sensorstatelist;
};

class SensorState{
    QString sensorname;
    QString sensorstate;
//    QString sensorrealtimevalue;
};

#endif // DEVICESTATERESULT_H
