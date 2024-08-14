#include "dbstateinfo.h"

DBStateInfo::DBStateInfo()
{
    m_InfoName="DBStateInfo";
}

QString DBStateInfo::getDataBaseType()
{
    return m_DataBaseType;
}

bool DBStateInfo::getDataBaseConnectState()
{
    return m_DataBaseConnectState;
}
