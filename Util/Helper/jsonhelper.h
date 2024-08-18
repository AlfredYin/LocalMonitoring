#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include <QDebug>

class JsonHelper
{   
public:
    // 静态方法，用于判断 JSON 字符串中是否包含指定数组
    static bool containsArray(const QString &jsonString, const QString &arrayKey) {
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "JSON parse error:" << parseError.errorString();
            return false;
        }

        // 获取顶层对象
        QJsonObject jsonObj = doc.object();

        // 检查是否包含指定的键
        if (jsonObj.contains(arrayKey) && jsonObj[arrayKey].isArray()) {
            QJsonArray jsonArray = jsonObj[arrayKey].toArray();
            // 检查数组是否为空
            if (!jsonArray.isEmpty()) {
                return true;
            }
        }

        return false;
    }
};

#endif // JSONHELPER_H
