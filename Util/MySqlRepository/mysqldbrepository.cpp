#include "mysqldbrepository.h"
#include "mysqldbmanager.h"

#include <QDebug>

MySqlDBRepository::MySqlDBRepository()
{
}

MySqlDBRepository::~MySqlDBRepository()
{

}

QSqlQuery MySqlDBRepository::executeQuery(const QString &queryStr, const QVariantList &bindValues)
{

    if(!MySqlDBManager::instance().getDatabase().isOpen()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

    QSqlQuery query(MySqlDBManager::instance().getDatabase());

    if (!query.prepare(queryStr)) {
        qDebug() << "Query prepare error:" << query.lastError().text();
        return query;
    }

    for (int i = 0; i < bindValues.size(); ++i) {
        query.bindValue(i, bindValues.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Query execution error:" << query.lastError().text();
    }

    return query;
}
