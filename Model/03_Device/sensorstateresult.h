#ifndef SENSORSTATERESULT_H
#define SENSORSTATERESULT_H

#include "baseresult.h"
#include "devicestateinfo.h"

class SensorState;

//class SensorStateResult : public BaseResult
class SensorStateResult
{
public:
    SensorStateResult();

    QList<SensorState> resultSensorStateList;
};

#endif // SENSORSTATERESULT_H
