#ifndef MQTTCLIENTSINGLETON_H
#define MQTTCLIENTSINGLETON_H

//#include <qmqttclient.h>
#include "qmqtt_client.h"   // 使用Qt非官方的库
#include <qmqtt.h>
#include <qdebug.h>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QScopedPointer>


class MqttClientSingleton
{
public:
    static QMQTT::Client* instance();

private:
    MqttClientSingleton() {}
    ~MqttClientSingleton() {}

    Q_DISABLE_COPY(MqttClientSingleton)
    static QScopedPointer<QMQTT::Client> _instance;
    static QMutex mutex;
};

// 定义静态成员变量
//QScopedPointer<QMQTT::Client> MqttClientSingleton::_instance = nullptr;

#endif // MQTTCLIENTSINGLETON_H
