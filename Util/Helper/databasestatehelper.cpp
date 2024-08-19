#include "databasestatehelper.h"
#include "mysqldbmanager.h"
#include "sqlserverdbmanager.h"

QString DataBaseStateHelper::m_DataBaseType = "default_value";

DataBaseStateHelper::DataBaseStateHelper()
{
}

QString DataBaseStateHelper::getConnectingDBType()
{
    QJsonObject config = ReadConfigJsonHelper::readConfig("config.json");
    if (config.isEmpty()) {
        qDebug() << "config.json Invalid configuration.";
        return "Invalid configuration.";
    }
    QJsonObject dbConfig = config["database"].toObject();

    DataBaseStateHelper::m_DataBaseType=dbConfig["type"].toString();

    return DataBaseStateHelper::m_DataBaseType;
}

bool DataBaseStateHelper::isConnectedDb()
{
    if(DataBaseStateHelper::m_DataBaseType=="MySQL"){
        return MySqlDBManager::instance().getDatabase().isOpen();
    }else if(DataBaseStateHelper::m_DataBaseType=="SQLServer") {
        return SqlServerDBManager::instance().getDatabase().isOpen();
    }
    return false;
}
