#ifndef SECURITYHELPER_H
#define SECURITYHELPER_H

#include <QByteArray>

class SecurityHelper
{
public:

    static QByteArray md5(const QString &input);

    static QString md5ToHex(const QString &input, int bit = 32);
};

#endif // SECURITYHELPER_H
