#ifndef DEVICESTATERESULT_H
#define DEVICESTATERESULT_H

#include <QJsonObject>
#include "baseresult.h"
#include "devicestateinfo.h"

class SensorState;
class DeivceState;

class DeviceStateListResult : public BaseResult
{
public:
    DeviceStateListResult();

    QList<DeviceStateInfo> resultList;
};


#endif // DEVICESTATERESULT_H
