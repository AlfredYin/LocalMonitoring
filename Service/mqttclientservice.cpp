#include "mqttclientservice.h"
#include <QIODevice>

MqttClientService::MqttClientService(QObject *parent) : QObject{parent}
{
    m_QmqttClient = MqttClientSingleton::instance(); // 获取单例实例

    connect(m_QmqttClient,&QMQTT::Client::connected,[this](){
        qDebug()<<"m_QmqttClient connected";
    });

    connect(m_QmqttClient, &QMQTT::Client::received, this, &MqttClientService::onMessageReceived);

    m_QmqttClient->connectToHost();
}

void MqttClientService::subscribeToTopic(const QString &topic)
{
    m_QmqttClient->subscribe(topic);
}

bool MqttClientService::publishMessage(const QString &topic, const QString &message)
{
    QMQTT::Message mqttMessage(0, topic, message.toUtf8());
    m_QmqttClient->publish(mqttMessage);
}

QMQTT::Client* MqttClientService::getQmqttClient()
{
    return m_QmqttClient;
}

void MqttClientService::onMessageReceived(const QMQTT::Message &message)
{
    emit messageReceived(message.payload(), message.topic());
}
