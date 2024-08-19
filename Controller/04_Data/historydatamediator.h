#ifndef HISTORYDATAMEDIATOR_H
#define HISTORYDATAMEDIATOR_H

#include "Mediator.h"
#include "Command.h"
#include "sensorhistorydata.h"
#include "sensorparam.h"
#include "dataproxy.h"

class HistoryDataMediator : public Mediator , public Command
{
public:
    HistoryDataMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    void getSensorHistoryData(SensorParam *sensorParam);

    QList<SensorHistoryData> get_HistoryDataSync(SensorParam *sensorParam);


private:
    QList<QString> m_notificationInterests;
};

#endif // HISTORYDATAMEDIATOR_H
