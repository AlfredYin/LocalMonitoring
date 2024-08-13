#ifndef DEVICESTATEINFO_H
#define DEVICESTATEINFO_H

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QDomElement>
#include <QDomDocument>

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

    // Convert to QDomElement
    QDomElement toXml(QDomDocument &doc) const {
        QDomElement sensorStateElement = doc.createElement("SensorState");
        sensorStateElement.appendChild(createElement(doc, "sensorname", sensorname));
        sensorStateElement.appendChild(createElement(doc, "sensorstate", sensorstate));
        return sensorStateElement;
    }

    // Populate from QDomElement
    void fromXml(const QDomElement &element) {
        sensorname = getElementText(element, "sensorname");
        sensorstate = getElementText(element, "sensorstate");
    }

    QString sensorname;
    QString sensorstate;
    // QString sensorrealtimevalue;

private:
    QDomElement createElement(QDomDocument &doc, const QString &name, const QString &value) const {
        QDomElement element = doc.createElement(name);
        QDomText textNode = doc.createTextNode(value);
        element.appendChild(textNode);
        return element;
    }

    QString getElementText(const QDomElement &element, const QString &name) const {
        QDomNodeList nodes = element.elementsByTagName(name);
        if (!nodes.isEmpty()) {
            return nodes.at(0).toElement().text();
        }
        return QString();
    }
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

    void toXml(QDomDocument &doc, QDomElement &parentElement) const {
            QDomElement deviceElement = doc.createElement("DeviceStateInfo");
            deviceElement.appendChild(createElement(doc, "devicename", devicename));
            deviceElement.appendChild(createElement(doc, "connectingflag", QString::number(connectingflag)));

            QDomElement sensorListElement = doc.createElement("sensorstatelist");
            for (const SensorState &sensor : sensorstatelist) {
                sensorListElement.appendChild(sensor.toXml(doc));
            }
            deviceElement.appendChild(sensorListElement);

            parentElement.appendChild(deviceElement);
        }

    void fromXml(const QDomElement &element) {
            devicename = getElementText(element, "devicename");
            connectingflag = getElementText(element, "connectingflag").toInt();

            QDomNodeList sensorNodes = element.elementsByTagName("SensorState");
            sensorstatelist.clear();
            for (int i = 0; i < sensorNodes.size(); ++i) {
                SensorState sensor;
                sensor.fromXml(sensorNodes.at(i).toElement());
                sensorstatelist.append(sensor);
            }
        }

public:
    QString devicename;
    int connectingflag;  // 0: offline / 1: online
    QList<SensorState> sensorstatelist;

private:
    QDomElement createElement(QDomDocument &doc, const QString &name, const QString &value) const {
        QDomElement element = doc.createElement(name);
        QDomText textNode = doc.createTextNode(value);
        element.appendChild(textNode);
        return element;
    }

    QString getElementText(const QDomElement &element, const QString &name) const {
        QDomNodeList nodes = element.elementsByTagName(name);
        if (!nodes.isEmpty()) {
            return nodes.at(0).toElement().text();
        }
        return QString();
    }
};

#endif // DEVICESTATEINFO_H
