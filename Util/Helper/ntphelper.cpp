#include "ntphelper.h"

#include <QDateTime>
#include <QUdpSocket>
#include <QDebug>
#include <QtEndian>
#include <QElapsedTimer>
#include <QMetaEnum>

NtpHelper::NtpHelper()
{

}

QByteArray NtpHelper::toNtpPacket()
{
    QByteArray result(40, 0);

    quint8 li = 0;                   // LI闰秒标识器，占用2个bit，0 即可；
    quint8 vn = 3;                   // VN 版本号，占用3个bits，表示NTP的版本号，现在为3；
    quint8 mode = 3;                 // Mode 模式，占用3个bits，表示模式。 3 表示 client， 2 表示 server
    quint8 stratum = 0;              // 系统时钟的层数，取值范围为1～16，它定义了时钟的准确度。层数为1的时钟准确度最高，准确度从1到16依次递减，层数为16的时钟处于未同步状态，不能作为参考时钟。
    quint8 poll = 4;                 // 轮询时间，即两个连续NTP报文之间的时间间隔(4-14)
    qint8 precision = -6;            // 系统时钟的精度,精确到秒的平方级（-6 到 -20）

    result[0] = char((li << 6) | (vn <<3) | (mode));
    result[1] = char(stratum & 0xff);

    result[2] = char(poll & 0xff);
    result[3] = char(precision & 0xff);

    qint64 currentLocalTimestamp = QDateTime::currentMSecsSinceEpoch();
    result.append((const char *)&currentLocalTimestamp, sizeof(qint64));

    return result;
}

// 将QByteArray类型时间戳数据转换为整形并且进行大小端转换
quint32 NtpHelper::byteToUInt32(QByteArray bt)
{
    if(bt.count() != 4) return 0;

    quint32 value;
    memcpy(&value, bt.data(), 4);

    return qToBigEndian(value);       // 大端转小端
}

// 将Ntp时间戳转换成QDateTime可用的时间戳
qint64 NtpHelper::byte64ToMillionSecond(QByteArray bt)
{
    qint64 second = byteToUInt32(bt.left(4));
    qint64 millionSecond = byteToUInt32(bt.mid(4, 4));
    return (second * 1000L) + ((millionSecond * 1000L) >> 32);
}
