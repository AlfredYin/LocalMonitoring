#ifndef HOMENTPTIMECOMMAND_H
#define HOMENTPTIMECOMMAND_H

#include "Command.h"
#include "ntpservice.h"
#include "../Interface/IMediator.h"
#include "../Interface/IObserver.h"
#include "../Interface/IViewComponent.h"
#include "Notifier.h"

#include <QThread>

class WorkerNtpTimeThread;

class HomeNtpTimeCommand : public Command, public Notifier
{
public:
    HomeNtpTimeCommand();

    void excute(INotification *notification);

private:
    WorkerNtpTimeThread *m_workerNtpTimeThread;
};

class WorkerNtpTimeThread : public QThread {
    Q_OBJECT
public:
    WorkerNtpTimeThread(QObject *parent = nullptr);

    ~WorkerNtpTimeThread();

protected:
    void run() override ;

signals:
    void updateNtpTime(QDateTime);

private slots:
    void on_TimeoutGetNtpTime();

private:
//    NtpService *ntpService;
};

#endif // HOMENTPTIMECOMMAND_H
