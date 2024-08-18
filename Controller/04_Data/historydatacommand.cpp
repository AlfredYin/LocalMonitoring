#include "historydatacommand.h"

#include "Facade.h"
#include "INotification.h"

HistoryDataCommand::HistoryDataCommand()
{
    // get_historydata
}

void HistoryDataCommand::excute(INotification *notification)
{
    DataProxy *dataProxy=(DataProxy *)Facade::getInstance()->retrieveProxy("DataProxy");
    SensorParam *sensorParam = (SensorParam *)notification->getBody();
    dataProxy->get_HistoryData(sensorParam);      // 已经发送通知，前端已经改变
}
