#ifndef MAINWINDOWMEDIATOR_H
#define MAINWINDOWMEDIATOR_H

#include "Mediator.h"

class MainWindowMediator : public Mediator
{
public:
    MainWindowMediator();

    QList<QString> getListNotificationInterests();

    void handleNotification(INotification *notification);

    // View中的直接调用的指令
    void startGetNtpTime();

private:
    QList<QString> m_notificationInterests;
};

#endif // MAINWINDOWMEDIATOR_H
