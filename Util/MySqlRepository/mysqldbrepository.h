#ifndef MYSQLDBREPOSITORY_H
#define MYSQLDBREPOSITORY_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

#include "mysqldbmanager.h"

class MySqlDBRepository
{

protected:
    QSqlDatabase m_database;

public:
    MySqlDBRepository();

    ~MySqlDBRepository();

    QSqlQuery executeQuery(const QString &queryStr, const QVariantList &bindValues = QVariantList());

};

#endif // MYSQLDBREPOSITORY_H
