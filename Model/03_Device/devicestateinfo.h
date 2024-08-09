#ifndef DEVICESTATEINFO_H
#define DEVICESTATEINFO_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>  // 确保包含 QList 的定义

#include "baseinfo.h"

class SensorState {
public:
    QJsonObject toJson() const {
        QJsonObject jsonObject;
        jsonObject["sensorname"] = sensorname;
        jsonObject["sensorstate"] = sensorstate;
        return jsonObject;
    }

    void fromJson(const QJsonObject &jsonObject) {
        sensorname = jsonObject["sensorname"].toString();
        sensorstate = jsonObject["sensorstate"].toString();
    }

    QString sensorname;
    QString sensorstate;
    // QString sensorrealtimevalue;
};

class DeviceStateInfo : public BaseInfo {
public:
    DeviceStateInfo();

    QJsonObject toJson() const {
        QJsonObject jsonObject;
        jsonObject["devicename"] = devicename;
        jsonObject["connectingflag"] = connectingflag;

        QJsonArray sensorArray;
        for (const SensorState& sensor : sensorstatelist) {
            sensorArray.append(sensor.toJson());
        }
        jsonObject["sensorstatelist"] = sensorArray;
        return jsonObject;
    }

    void fromJson(const QJsonObject &jsonObject) {
        devicename = jsonObject["devicename"].toString();
        connectingflag = jsonObject["connectingflag"].toInt();

        sensorstatelist.clear();
        QJsonArray sensorArray = jsonObject["sensorstatelist"].toArray();
        for (const QJsonValue &value : sensorArray) {
            SensorState sensor;
            sensor.fromJson(value.toObject());
            sensorstatelist.append(sensor);
        }
    }

public:
    QString devicename;
    int connectingflag;  // 0: offline / 1: online
    QList<SensorState> sensorstatelist;
};

#endif // DEVICESTATEINFO_H
