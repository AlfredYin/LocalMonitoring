#ifndef CONTROLDEVICECOMMANDSENDRESULT_H
#define CONTROLDEVICECOMMANDSENDRESULT_H

#include "devicestateinfo.h"
#include "baseresult.h"

class ControlDeviceCommandSendResult : public BaseResult
{
public:
    ControlDeviceCommandSendResult();

    QString publishTopic;

    QList<ControlDeviceState> resultControlDeviceStateList;     // 还要使用List,没有处理区分控制设备的来源
//    ControlDeviceState resultControlDeviceState;
};

#endif // CONTROLDEVICECOMMANDSENDRESULT_H
