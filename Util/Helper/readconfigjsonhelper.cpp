#include "readconfigjsonhelper.h"
#include <QDebug>

ReadConfigJsonHelper::ReadConfigJsonHelper()
{

}

QJsonObject ReadConfigJsonHelper::readConfig(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot open config file:" << filePath;
        return QJsonObject();
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc(QJsonDocument::fromJson(data));
    return doc.object();
}
