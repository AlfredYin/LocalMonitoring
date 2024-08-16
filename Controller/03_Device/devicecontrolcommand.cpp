#include "devicecontrolcommand.h"

DeviceControlCommand::DeviceControlCommand()
{
    // serivce 初始化
    m_MqttClientService=new MqttClientService();

    // 订阅主题
    // 订阅数据库中获取
    m_MqttClientService->subscribeToTopic("Esp32_1_Pub");

    // 设置连接函数
    connect(m_MqttClientService,&MqttClientService::messageReceived,[this](const QByteArray& message, const QString& topic){
        if()
    });
}

void DeviceControlCommand::excute(INotification *notification)
{
    qDebug()<<"void DeviceControlCommand::excute(INotification *notification)";
    ControlDeviceState *controlDeviceParam=static_cast<ControlDeviceState *>(notification->getBody());

    QString publicTopic=controlDeviceParam->gwclientid+"_Sub";
    // {"action":"control","device":"beep","state":"off"}
    QString payloadMess="{\"action\":\"control\",\"device\":\""+controlDeviceParam->device+
            "\",\"state\":\""+controlDeviceParam->devicecommands+"\"}";

    m_MqttClientService->publishMessage(publicTopic,payloadMess);
}
