#ifndef MYSQLDBREPOSITORY_H
#define MYSQLDBREPOSITORY_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QFuture>
#include <QFutureWatcher>
#include <QThreadPool>
#include <QPair>

#include "mysqldbmanager.h"

class MySqlDBRepository
{

public:
    MySqlDBRepository();

    ~MySqlDBRepository();

    QSqlQuery executeQuery(const QString &queryStr, const QVariantList &bindValues = QVariantList());
    QSqlQuery executeQuery(const QString &queryStr, const QVariantMap &namedBindValues);
    QSqlQuery executeQuery(const QString &queryStr, const std::initializer_list<QPair<QString, QVariant>> &namedBindValues);

    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QVariantList &bindValues = QVariantList());
    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QVariantMap &namedBindValues);
    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues);

    signals:
        void queryFinished(QSqlQuery query);
};

#endif // MYSQLDBREPOSITORY_H
