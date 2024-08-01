#ifndef APPLICATIONMEDIATOR_H
#define APPLICATIONMEDIATOR_H

#include "Patterns/Mediator.h"

class ApplicationMediator : public Mediator
{
public:
    ApplicationMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

private:
    QList<QString> m_notificationInterests;

};

#endif // APPLICATIONMEDIATOR_H
