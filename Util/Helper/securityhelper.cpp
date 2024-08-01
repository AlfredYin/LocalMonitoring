#include "securityhelper.h"

#include <QCryptographicHash>
#include <QString>


QByteArray SecurityHelper::md5(const QString &input)
{
    QByteArray hash;
    hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5);
    return hash;
}

QString SecurityHelper::md5ToHex(const QString &input, int bit)
{
    QByteArray byteArr = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Md5);
    QString result = byteArr.toHex().data();

    if (bit == 16)
    {
        // Take the middle 16 bits (8 characters) of the hash
        return result.mid(8, 8).toUpper();
    }
    else
    {
        return result.toUpper();
    }
}
