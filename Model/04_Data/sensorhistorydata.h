#ifndef SENSORHISTORYDATA_H
#define SENSORHISTORYDATA_H

#include <QString>

// GwClientId, GwPubTopic, Humidity, Temperature, HeatIndex, CO2conc, VOCconc, Illum, GwMessDate
class SensorHistoryData
{
public:
    SensorHistoryData();
    int id;
    QString devicename;
    QString gwpubtopic;
    QString humidity;
    QString temperature;
    QString heatIndex;
    QString co2conc;
    QString vocconc;
    QString illum;
    QString gwdatadate;
};

#endif // SENSORHISTORYDATA_H
