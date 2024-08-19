#ifndef DATABASESTATEHELPER_H
#define DATABASESTATEHELPER_H

#include "mysqldbmanager.h"
#include "sqlserverdbmanager.h"
#include "readconfigjsonhelper.h"


class DataBaseStateHelper
{
public:
    DataBaseStateHelper();

    static QString getConnectingDBType();

    static bool isConnectedDb();

    static QString m_DataBaseType;
};

#endif // DATABASESTATEHELPER_H
