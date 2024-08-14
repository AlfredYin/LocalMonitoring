#ifndef DBREPOSITORY_H
#define DBREPOSITORY_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QFuture>
#include <QFutureWatcher>
#include <QThreadPool>
#include <QPair>
#include <QtConcurrent>

#include "mysqldbmanager.h"
#include "sqlserverdbmanager.h"
#include "readconfigjsonhelper.h"

class DataBaseRepository
{
public:
    DataBaseRepository();

    ~DataBaseRepository();

    QSqlQuery executeQuery(const QString &queryStr, const QVariantList &bindValues = QVariantList());
    QSqlQuery executeQuery(const QString &queryStr, const QVariantMap &namedBindValues);
    QSqlQuery executeQuery(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues);

    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QVariantList &bindValues = QVariantList());
    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QVariantMap &namedBindValues);
    QFuture<QSqlQuery> executeQueryAsync(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues);

    signals:
        void queryFinished(QSqlQuery query);

private:

    QString m_DataBaseType; // MySQL,SQLServer

    QSqlDatabase getDataBase();
    bool isDataBaseConnection();
};

#endif // DBREPOSITORY_H
