#ifndef DEVICECONTROLCOMMAND_H
#define DEVICECONTROLCOMMAND_H

#include "Proxy.h"
#include "Command.h"
#include <QObject>
#include "mqttclientservice.h"
#include "devicestateinfo.h"
#include "INotification.h"
#include "controldevicestateresult.h"

#include <QDebug>

class DeviceControlCommand : public QObject,public Command
{
    Q_OBJECT
public:
    DeviceControlCommand();

    void excute(INotification *notification);

private:
    MqttClientService *m_MqttClientService;
};

#endif // DEVICECONTROLCOMMAND_H
