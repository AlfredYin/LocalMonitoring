#ifndef MQTTCLIENTSERVICE_H
#define MQTTCLIENTSERVICE_H

//#include <qmqttclient.h>
#include "qmqtt_client.h"   // 使用Qt非官方的库
#include <qmqtt.h>
#include <qdebug.h>
#include <QtNetwork>
#include <QNetworkAccessManager>

#include "Proxy.h"
#include "mqttclientsingleton.h"
#include "jsonhelper.h"
#include "controldevicecommandsendresult.h"

class MqttClientService : public QObject , public Proxy
{
    Q_OBJECT
public:
    explicit MqttClientService(QObject *parent = nullptr);

    void subscribeToTopic(const QString& topic);

    bool  publishMessage(const QString& topic, const QString& message);

    QMQTT::Client* getQmqttClient();

    void setSendCommandFlag(bool flag);

    void setSubTopicList(QList<QString> topicList);

//signals:
//    void messageReceived(const QByteArray& message, const QString& topic);

private slots:
    void onMessageReceived(const QMQTT::Message& message);

private:

private:
    QMQTT::Client *m_QmqttClient;

    QList<QString> subTopicList;

    QSslConfiguration config;   // Since QT 5.14, SSL transport config

    bool m_SendCommandFlag=false;
};

#endif // MQTTCLIENTSERVICE_H
