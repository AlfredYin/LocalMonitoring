#ifndef MAINWINDOWMEDIATOR_H
#define MAINWINDOWMEDIATOR_H

#include "Patterns/Mediator.h"

class MainWindowMediator : public Mediator
{
public:
    MainWindowMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

private:
    QList<QString> m_notificationInterests;
};

#endif // MAINWINDOWMEDIATOR_H
