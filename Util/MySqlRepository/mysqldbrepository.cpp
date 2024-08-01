#include "mysqldbrepository.h"
#include "mysqldbmanager.h"

#include <QDebug>

MySqlDBRepository::MySqlDBRepository()
    : m_database(MySqlDBManager::instance().getDatabase())
{
    if(!m_database.isOpen()){
            qDebug() << "数据库连接未打开或无效。";
            return; // 提前返回或处理连接错误
    }
}

MySqlDBRepository::~MySqlDBRepository()
{

}

QSqlQuery MySqlDBRepository::executeQuery(const QString &queryStr, const QVariantList &bindValues)
{

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
