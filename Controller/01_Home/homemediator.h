#ifndef HOMEMEDIATOR_H
#define HOMEMEDIATOR_H

#include "Patterns/Mediator.h"

class HomeMediator : public Mediator
{
public:
    HomeMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

private:
    QList<QString> m_notificationInterests;
};

#endif // HOMEMEDIATOR_H
