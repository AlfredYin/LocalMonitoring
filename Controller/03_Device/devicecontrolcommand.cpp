#include "devicecontrolcommand.h"

DeviceControlCommand::DeviceControlCommand()
{
    // serivce 初始化
    m_MqttClientService=new MqttClientService();

    // 订阅主题
    // 订阅数据库中获取
    QList<QString> topicList;
    topicList.append("Esp32_1_Pub");
    topicList.append("Esp32_2_Pub");

    // 传入订阅列表 MqttClientService 自动订阅并且注册监听
    m_MqttClientService->setSubTopicList(topicList);
}

void DeviceControlCommand::excute(INotification *notification)
{
    ControlDeviceState *controlDeviceParam=static_cast<ControlDeviceState *>(notification->getBody());

    QString publicTopic=controlDeviceParam->gwclientid+"_Sub";
    // {"action":"control","device":"beep","state":"off"}
    QString payloadMess="{\"action\":\"control\",\"device\":\""+controlDeviceParam->device+
            "\",\"state\":\""+controlDeviceParam->devicecommands+"\"}";

    m_MqttClientService->setSendCommandFlag(true);
    m_MqttClientService->publishMessage(publicTopic,payloadMess);
}
