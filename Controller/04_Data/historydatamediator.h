#ifndef HISTORYDATAMEDIATOR_H
#define HISTORYDATAMEDIATOR_H

#include "Mediator.h"

#include "sensorparam.h"

class HistoryDataMediator : public Mediator
{
public:
    HistoryDataMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    void getSensorHistoryData(SensorParam *sensorParam);

private:
    QList<QString> m_notificationInterests;
};

#endif // HISTORYDATAMEDIATOR_H
