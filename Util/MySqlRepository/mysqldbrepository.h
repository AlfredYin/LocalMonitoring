#ifndef MYSQLDBREPOSITORY_H
#define MYSQLDBREPOSITORY_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>

#include "mysqldbmanager.h"

class MySqlDBRepository
{

public:
    MySqlDBRepository();

    ~MySqlDBRepository();

    QSqlQuery executeQuery(const QString &queryStr, const QVariantList &bindValues = QVariantList());

    QSqlQuery executeQuery(const QString &queryStr, const QVariantMap &namedBindValues);

    QSqlQuery executeQuery(const QString &queryStr, const std::initializer_list<QPair<QString, QVariant>> &namedBindValues);

};

#endif // MYSQLDBREPOSITORY_H
