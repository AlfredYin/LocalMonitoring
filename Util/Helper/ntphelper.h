#ifndef NTPHELPER_H
#define NTPHELPER_H

#include <QByteArray>

class NtpHelper
{
public:
    NtpHelper();

    static QByteArray toNtpPacket();

    static quint32 byteToUInt32(QByteArray bt);

    static qint64 byte64ToMillionSecond(QByteArray bt);
};

#endif // NTPHELPER_H
