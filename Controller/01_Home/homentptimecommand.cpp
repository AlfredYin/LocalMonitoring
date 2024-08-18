#include "homentptimecommand.h"
#include "ntpservice.h"
#include "ntptimeresult.h"

#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QObject>

HomeNtpTimeCommand::HomeNtpTimeCommand()
{

}

void HomeNtpTimeCommand::excute(INotification *notification)
{
    // 每分钟定时同步一下Ntp时间
    qDebug()<<"开启每分钟定时同步一下Ntp时间";
//    WorkerNtpTimeThread worker;
//    worker.start();
    m_workerNtpTimeThread=new WorkerNtpTimeThread;

//    QObject::connect(m_workerNtpTimeThread,SIGNAL(QThread::started),this,)
    QObject::connect(m_workerNtpTimeThread,&WorkerNtpTimeThread::updateNtpTime, [this](QDateTime ntpTime){

                         NtpTimeResult *result=new NtpTimeResult();
                         if(ntpTime.isNull() || !ntpTime.isValid()){
                             result->result=false;
                             result->message="Ntp时间获失败";
                         }else{
                            result->result=true;
                            result->ntpTime=ntpTime;
                         }

                         sendNotification("get_ntptime_finished", result);
                     });

    m_workerNtpTimeThread->start();
}

WorkerNtpTimeThread::WorkerNtpTimeThread(QObject *parent)
{

}

WorkerNtpTimeThread::~WorkerNtpTimeThread()
{
    if (isRunning()) {
        quit();
        wait();
    }
}

void WorkerNtpTimeThread::run()
{
    QTimer::singleShot(0, this, &WorkerNtpTimeThread::on_TimeoutGetNtpTime);

    QTimer *timer = new QTimer();;
    connect(timer, &QTimer::timeout, this, &WorkerNtpTimeThread::on_TimeoutGetNtpTime);

    timer->start(5000); // 每5秒触发一次
    exec(); // 进入事件循环
}

void WorkerNtpTimeThread::on_TimeoutGetNtpTime()
{
    NtpService *ntpService=new NtpService();
//    QDateTime ntpTime = ntpService->getNtpTime();

    connect(ntpService, &NtpService::updateData, [this](QString mess) {
//        qDebug() << "NtpService 日志记录:" << mess;
    });

    connect(ntpService, &NtpService::updateNtpTime, [this](QDateTime ntpTime) {

        if(ntpTime.isNull() || !ntpTime.isValid()){
            qDebug() << "Ntp时间获取失败";
            updateNtpTime(QDateTime());
        }
        else{
            QString ntpTimeStr = ntpTime.toString("yyyy-MM-dd hh:mm:ss zzz");
//            qDebug() << "Ntp时间获取成功:" << ntpTimeStr;
            updateNtpTime(ntpTime);
        }

    });

}
