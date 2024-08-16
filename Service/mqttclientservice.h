#ifndef MQTTCLIENTSERVICE_H
#define MQTTCLIENTSERVICE_H

//#include <qmqttclient.h>
#include "qmqtt_client.h"   // 使用Qt非官方的库
#include <qmqtt.h>
#include <qdebug.h>
#include <QtNetwork>
#include <QNetworkAccessManager>

#include "mqttclientsingleton.h"

class MqttClientService : public QObject
{
    Q_OBJECT
public:
    explicit MqttClientService(QObject *parent = nullptr);

    void subscribeToTopic(const QString& topic);

    bool  publishMessage(const QString& topic, const QString& message);

    QMQTT::Client* getQmqttClient();

signals:
    void messageReceived(const QByteArray& message, const QString& topic);

private slots:
    void onMessageReceived(const QMQTT::Message& message);

private:

private:
    QMQTT::Client *m_QmqttClient;

    QSslConfiguration config;   // Since QT 5.14, SSL transport config
};

#endif // MQTTCLIENTSERVICE_H
