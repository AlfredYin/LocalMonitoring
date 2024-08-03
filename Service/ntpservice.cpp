#include "ntpservice.h"
#include "ntphelper.h"

#include <QDateTime>
#include <QUdpSocket>
#include <QDebug>
#include <QtEndian>
#include <QElapsedTimer>
#include <QMetaEnum>

NtpService::NtpService(QObject *parent) : QObject(parent)
{
    m_socket = new QUdpSocket();

    connect(m_socket, &QUdpSocket::connected, this, &NtpService::on_connected);
//    connect(m_socket, &QUdpSocket::readyRead, this, &NtpService::on_readData);

    m_socket->connectToHost("47.98.243.38", 123);
}

NtpService::~NtpService()
{
    m_socket->close();
}

QDateTime NtpService::getNtpTime()
{
    // 发送Ntp组成报文
    sendData();
    if (m_socket->waitForReadyRead(5000)) { // 超时时间为5秒
        QElapsedTimer timer;       // 统计数据解析消耗的时间
        timer.start();

        QByteArray buf = m_socket->readAll();
        qint64 currentLocalTimestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();        // 客户端接收到响应报文时的时间戳 T4
        if(buf.count() < 48)          // Ntp协议帧长度为48字节
        {
            return QDateTime();
        }

        QDateTime epoch(QDate(1900, 1, 1), QTime(0, 0, 0));           // ntp时间计时从1900年开始
        QDateTime unixStart(QDate(1970, 1, 1), QTime(0, 0, 0));       // UNIX操作系统考虑到计算机产生的年代和应用的时限综合取了1970年1月1日作为UNIX TIME的纪元时间(开始时间)
        qint64 unixDiff = epoch.msecsTo(unixStart);

        // 解析ntp协议中的时间
        qint64 referenceTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(16, 8)) - unixDiff;           // 参考时间戳
        qint64 originTimestamp;                                                                 // 原始时间戳    T1
        memcpy(&originTimestamp, buf.mid(24, 8), 8);
        qint64 receiveTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(32, 8)) - unixDiff;             // 接收时间戳   T2
        qint64 translateTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(40, 8)) - unixDiff;           // 传送时间戳   T3

        QDateTime dateTime;

    #if 0
        qDebug() << "-----------NTP协议中包含的所有时间-----------";
        dateTime.setMSecsSinceEpoch(referenceTimestamp);
        qDebug() << "参考时间戳：  " << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
        dateTime.setMSecsSinceEpoch(originTimestamp);
        qDebug() << "原始时间戳T1：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
        dateTime.setMSecsSinceEpoch(receiveTimestamp);
        qDebug() << "接收时间戳T2：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
        dateTime.setMSecsSinceEpoch(translateTimestamp);
        qDebug() << "传送时间戳T3：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
        dateTime.setMSecsSinceEpoch(currentLocalTimestamp);
        qDebug() << "本地时间戳T4：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
        qDebug() << "------------------------------------------";
    #endif

        QString strTime;
        // 计算方式1：时间差offset=（（T2-T1）+（T3-T4））/2      实际时间=程序处理时间（timer.elapsed()） + 接收数据时间T4 + 客户端与服务端的时间差（offset）
        qint64 currentLocalTimestamp1 = timer.elapsed()
                + currentLocalTimestamp
                + qint64((receiveTimestamp - originTimestamp
                + translateTimestamp - currentLocalTimestamp) / 2);

        dateTime.setMSecsSinceEpoch(currentLocalTimestamp1);
    } else {
        qDebug() << "Failed to receive NTP response.";
        return QDateTime();
    }
}

void NtpService::on_connected()
{
    // QMetaEnum m = QMetaEnum::fromType<QAbstractSocket::SocketState>();      // 获取QUdpSocket连接状态字符串
    // emit updateData(QString("连接成功：%1  %2").arg(m_socket->peerName()).arg(m.key(m_socket->state())));

}

void NtpService::on_readData()
{
    QElapsedTimer timer;       // 统计数据解析消耗的时间
    timer.start();

    QByteArray buf = m_socket->readAll();
    qint64 currentLocalTimestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();        // 客户端接收到响应报文时的时间戳 T4
    if(buf.count() < 48)          // Ntp协议帧长度为48字节
    {
        return;
    }

    QDateTime epoch(QDate(1900, 1, 1), QTime(0, 0, 0));           // ntp时间计时从1900年开始
    QDateTime unixStart(QDate(1970, 1, 1), QTime(0, 0, 0));       // UNIX操作系统考虑到计算机产生的年代和应用的时限综合取了1970年1月1日作为UNIX TIME的纪元时间(开始时间)
    qint64 unixDiff = epoch.msecsTo(unixStart);

    // 解析ntp协议中的时间
    qint64 referenceTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(16, 8)) - unixDiff;           // 参考时间戳
    qint64 originTimestamp;                                                                 // 原始时间戳    T1
    memcpy(&originTimestamp, buf.mid(24, 8), 8);
    qint64 receiveTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(32, 8)) - unixDiff;             // 接收时间戳   T2
    qint64 translateTimestamp = NtpHelper::byte64ToMillionSecond(buf.mid(40, 8)) - unixDiff;           // 传送时间戳   T3

    QDateTime dateTime;

#if 0
    qDebug() << "-----------NTP协议中包含的所有时间-----------";
    dateTime.setMSecsSinceEpoch(referenceTimestamp);
    qDebug() << "参考时间戳：  " << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
    dateTime.setMSecsSinceEpoch(originTimestamp);
    qDebug() << "原始时间戳T1：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
    dateTime.setMSecsSinceEpoch(receiveTimestamp);
    qDebug() << "接收时间戳T2：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
    dateTime.setMSecsSinceEpoch(translateTimestamp);
    qDebug() << "传送时间戳T3：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
    dateTime.setMSecsSinceEpoch(currentLocalTimestamp);
    qDebug() << "本地时间戳T4：" << dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
    qDebug() << "------------------------------------------";
#endif

    QString strTime;
#if 1         // 计算方式1：时间差offset=（（T2-T1）+（T3-T4））/2      实际时间=程序处理时间（timer.elapsed()） + 接收数据时间T4 + 客户端与服务端的时间差（offset）
    qint64 currentLocalTimestamp1 = timer.elapsed() + currentLocalTimestamp + qint64((receiveTimestamp - originTimestamp + translateTimestamp - currentLocalTimestamp) / 2);

    dateTime.setMSecsSinceEpoch(currentLocalTimestamp1);
    strTime = dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
//    emit updateData(strTime);
#else        // 计算方式2：往返时延Delay=（T4-T1）-（T3-T2）            实际时间=程序处理时间（timer.elapsed()） + 服务器数据发出时间（T3）+ 通信时延（Delay）
    qint64 currentLocalTimestamp2 = timer.elapsed() + translateTimestamp + (((currentLocalTimestamp - originTimestamp) - (translateTimestamp - receiveTimestamp)) / 2);
    dateTime.setMSecsSinceEpoch(currentLocalTimestamp2);
    strTime = dateTime.toString("yyyy-MM-dd HH:mm:ss zzz");
#endif
    qDebug() << strTime;
//    setDateTime(dateTime);
}

// 发送NTP请求帧
void NtpService::sendData()
{
    QByteArray arr = NtpHelper::toNtpPacket();
    qint64 len = m_socket->write(arr);
    if(len != arr.count())
    {
        qWarning() << "发送NTP请求帧失败：" << arr.toHex(' ');
    }
}
