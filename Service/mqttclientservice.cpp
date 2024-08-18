#include "mqttclientservice.h"
#include <QIODevice>

MqttClientService::MqttClientService(QObject *parent) : QObject{parent}
{
    m_QmqttClient = MqttClientSingleton::instance(); // 获取单例实例

    connect(m_QmqttClient,&QMQTT::Client::connected,[this](){
        qDebug()<<"m_QmqttClient connected";
        foreach(const QString& topic, subTopicList){
            m_QmqttClient->subscribe(topic);
            qDebug()<<"m_QmqttClient subscribe : "<<topic;
        }
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

void MqttClientService::setSendCommandFlag(bool flag)
{
    m_SendCommandFlag=flag;
}

void MqttClientService::setSubTopicList(QList<QString> topicList)
{
    subTopicList=topicList;

    // 开始重新开始订阅
    if(m_QmqttClient->connectionState()!=QMQTT::STATE_CONNECTED){
        foreach(const QString& topic, subTopicList){
            m_QmqttClient->subscribe(topic);
        }
    }
}

void MqttClientService::onMessageReceived(const QMQTT::Message &message)
{
    // emit messageReceived(message.payload(), message.topic());
    // 检测是不是注册过的主题,这个应该肯定是
    QString pubTopic=message.topic();
    QString messStr=QString::fromUtf8(message.payload());
    // 解析json,看看是不是response的相应
    // "{\"response\":[{\"device\":\"led\",\"state\":\"off\"},{\"device\":\"trigger1\",\"state\":\"off\"},{\"device\":\"trigger2\",\"state\":\"off\"},{\"device\":\"trigger3\",\"state\":\"off\"},{\"device\":\"rgb\",\"state\":\"Green \"},{\"device\":\"servo\",\"state\":\"off\"},{}]}"
    if(JsonHelper::containsArray(messStr,"response")){
        ControlDeviceCommandSendResult *result=new ControlDeviceCommandSendResult();
//        qDebug()<< pubTopic<<" "<<messStr;
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(messStr.toUtf8(), &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            return;
        }

        // 解析出controldevice的状态
        QJsonObject jsonObj = doc.object();
        if (jsonObj.contains("response") && jsonObj["response"].isArray()) {
            QJsonArray responseArray = jsonObj["response"].toArray();
            for (const QJsonValue &value : responseArray) {
                if (value.isObject()) {
                    QJsonObject itemObj = value.toObject();
                    if (itemObj.contains("device") && itemObj.contains("state")) {

                        ControlDeviceState controlDeviceState;
                        controlDeviceState.device=itemObj["device"].toString();
                        controlDeviceState.devicestate=itemObj["state"].toString();

                        result->resultControlDeviceStateList.append(controlDeviceState);
                    }
                }
            }
        }
        // 填充result作为参数,发出指令
        result->publishTopic=pubTopic;
        if(m_SendCommandFlag){
           sendNotification("devicecontrolsendcommand_finished", static_cast<void *>(result));
           m_SendCommandFlag=false;
        }
    }
}
