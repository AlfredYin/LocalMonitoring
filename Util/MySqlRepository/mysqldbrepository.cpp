#include "mysqldbrepository.h"
#include "mysqldbmanager.h"

#include <QtConcurrent/QtConcurrent>
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

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!bindValues.isEmpty()){
        qDebug() << "Bound Values:";
        for (int i = 0; i < bindValues.size(); ++i)
        {
            qDebug() << "Position" << i << ":" << bindValues[i].toString();
        }
    }

#endif

    QSqlQuery query(MySqlDBManager::instance().getDatabase());
    query.prepare(queryStr);

    for (int i = 0; i < bindValues.size(); ++i) {
        query.bindValue(i, bindValues.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    return query;
}

QSqlQuery MySqlDBRepository::executeQuery(const QString &queryStr, const QVariantMap &namedBindValues)
{
    if(!MySqlDBManager::instance().getDatabase().isOpen()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

#if defined(QT_DEBUG) || defined(DEBUG)
    qDebug() << "Executing SQL Query:" << queryStr;
    qDebug() << "Bound Values:";

    for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
    {
        qDebug() << "Name" << it.key() << ":" << it.value().toString();
    }
#endif

    QSqlQuery query(MySqlDBManager::instance().getDatabase());
    query.prepare(queryStr);
    for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
    {
        query.bindValue(it.key(), it.value());
    }
    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return query;
}

QSqlQuery MySqlDBRepository::executeQuery(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues)
{
    if(!MySqlDBManager::instance().getDatabase().isOpen()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

#if defined(QT_DEBUG) || defined(DEBUG)
    qDebug() << "Executing SQL Query:" << queryStr;
    qDebug() << "Bound Values:";

    for (const auto &pair : namedBindValues)
    {
        qDebug() << "Name" << pair.first << ":" << pair.second.toString();
    }
#endif

    QSqlQuery query(MySqlDBManager::instance().getDatabase());

    query.prepare(queryStr);

    // 检查 prepare 语句是否成功
    if (query.lastError().type() != QSqlError::NoError)
    {
        qDebug() << "Error preparing SQL query:" << query.lastError().text();
        return query;
    }

    for (const auto &pair : namedBindValues)
    {
        query.bindValue(pair.first, pair.second);
    }
    if (!query.exec())
    {
        // 处理错误
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return query;
}

QFuture<QSqlQuery> MySqlDBRepository::executeQueryAsync(const QString &queryStr, const QVariantList &bindValues)
{
    return QtConcurrent::run([this, queryStr, bindValues]() {

        if(!MySqlDBManager::instance().getDatabase().isOpen()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

    #if defined(QT_DEBUG) || defined(DEBUG)

        qDebug() << "Executing SQL Query:" << queryStr;
        if(!bindValues.isEmpty()){
            qDebug() << "Bound Values:";
            for (int i = 0; i < bindValues.size(); ++i)
            {
                qDebug() << "Position" << i << ":" << bindValues[i].toString();
            }
        }

    #endif

        QSqlQuery query(MySqlDBManager::instance().getDatabase());
        query.prepare(queryStr);

        for (int i = 0; i < bindValues.size(); ++i) {
            query.bindValue(i, bindValues.at(i));
        }

        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }

        return query;
    });
}

QFuture<QSqlQuery> MySqlDBRepository::executeQueryAsync(const QString &queryStr, const QVariantMap &namedBindValues)
{
    return QtConcurrent::run([this, queryStr, namedBindValues]() {

        if(!MySqlDBManager::instance().getDatabase().isOpen()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

    #if defined(QT_DEBUG) || defined(DEBUG)
        qDebug() << "Executing SQL Query:" << queryStr;
        qDebug() << "Bound Values:";

        for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
        {
            qDebug() << "Name" << it.key() << ":" << it.value().toString();
        }
    #endif

        QSqlQuery query(MySqlDBManager::instance().getDatabase());
        query.prepare(queryStr);
        for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
        {
            query.bindValue(it.key(), it.value());
        }
        if (!query.exec())
        {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        return query;

    });
}

QFuture<QSqlQuery> MySqlDBRepository::executeQueryAsync(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues)
{
    return QtConcurrent::run([this, queryStr, namedBindValues]() {


//        qDebug() << "Starting async query: " << queryStr;
        // 异步查询实现

        if(!MySqlDBManager::instance().getDatabase().isOpen()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

    #if defined(QT_DEBUG) || defined(DEBUG)
        qDebug() << "Executing SQL Query:" << queryStr;
        qDebug() << "Bound Values:";

        for (const auto &pair : namedBindValues)
        {
            qDebug() << "Name" << pair.first << ":" << pair.second.toString();
        }
    #endif

        QSqlQuery query(MySqlDBManager::instance().getDatabase());

        query.prepare(queryStr);

        // 检查 prepare 语句是否成功
        if (query.lastError().type() != QSqlError::NoError)
        {
            qDebug() << "Error preparing SQL query:" << query.lastError().text();
            return query;
        }

        for (const auto &pair : namedBindValues)
        {
            query.bindValue(pair.first, pair.second);
        }
        if (!query.exec())
        {
            // 处理错误
            qDebug() << "Error executing query:" << query.lastError().text();
        }

        // 在查询完成时输出调试信息
//        qDebug() << "Async query completed: " << queryStr;
        return query;
    });
}
