#ifndef MQTTCLIENTSERVICE_H
#define MQTTCLIENTSERVICE_H

#include <QMainWindow>
//#include <qmqttclient.h>
#include "qmqtt_client.h"   // 使用Qt非官方的库
#include <qmqtt.h>
#include <qdebug.h>
#include <QtNetwork>
#include <QNetworkAccessManager>

class MqttClientService : public QObject
{
    Q_OBJECT
public:
    explicit MqttClientService(QObject *parent = nullptr);

    void connectMqttServerSsl(QSslConfiguration config);

private:
    void connectInit();

private:
    QMQTT::Client *client;

    QSslConfiguration config;   // Since QT 5.14, SSL transport config
};

#endif // MQTTCLIENTSERVICE_H
