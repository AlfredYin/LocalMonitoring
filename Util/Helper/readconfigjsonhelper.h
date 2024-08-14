#ifndef READCONFIGJSONHELPER_H
#define READCONFIGJSONHELPER_H

#include <QJsonObject>
#include <QFile>
#include <QJsonDocument>

class ReadConfigJsonHelper
{
public:
    ReadConfigJsonHelper();

    static QJsonObject readConfig(const QString& filePath);
};

#endif // READCONFIGJSONHELPER_H
