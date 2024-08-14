#ifndef DBSTATERESULT_H
#define DBSTATERESULT_H

#include "baseinfo.h"

class DBStateInfo : BaseInfo
{
public:
    DBStateInfo();

    QString getDataBaseType();

    bool getDataBaseConnectState();

private:

    QString m_DataBaseType;

    bool m_DataBaseConnectState;
};

#endif // DBSTATERESULT_H
