#ifndef SENSORPARAM_H
#define SENSORPARAM_H

#include <QString>

class SensorParam
{
public:
    SensorParam();

    QString devicename;     // 网关设备ClientId名称

    QString sensorname;
};

#endif // SENSORPARAM_H
