#ifndef NTPSERVICE_H
#define NTPSERVICE_H

#include <QObject>
#include <QUdpSocket>
#include <QDateTime>

class QUdpSocket;
#if 0   // NTP协议帧（未使用）
typedef struct
{
    char  LI_VN_Mode;
    char  Stratum;
    char  Poll;
    char  Precision;
    int  RootDelay;
    int  RootDispersion;
    int  ReferenceIdentifier;
    quint64  ReferenceTimeStamp;    // 系统时钟最后一次被设定或更新的时间
    quint64   OriginateTimeStamp;    // NTP请求报文离开发送端时发送端的本地时间
    quint64   ReceiveTimeStamp;      // NTP请求报文到达Server端时接收端的本地时间。
    quint64   TransmitTimeStamp;     // 发送时间戳，客户端发送时填写，server接收到后会将TransmitTimeStamp值写入OriginateTimeStamp，然后NTP应答报文离开Server时在OriginateTimeStamp的本地时间。
}NtpPacket;
#endif

class NtpService : public QObject
{
    Q_OBJECT

public:
    NtpService(QObject *parent = nullptr);

    ~NtpService();

    QDateTime getNtpTime();

signals:
    void updateNtpTime(QDateTime);
    void updateData(QString);

private:
    void on_connected();

    void on_readData();

    void sendData();

private:
    QUdpSocket* m_socket = nullptr;
};

#endif // NTPSERVICE_H
