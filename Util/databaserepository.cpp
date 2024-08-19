#include "databaserepository.h"

DataBaseRepository::DataBaseRepository()
{
    // 判断当前数据库是否连接
    if(isDataBaseConnection()){
        // 数据库已经连接上
        qDebug()<<"DataBaseConnection";
        return;
    }

    // 读取配置文件
    QJsonObject config = ReadConfigJsonHelper::readConfig("config.json");
    if (config.isEmpty()) {
        qDebug() << "config.json Invalid configuration.";
        return;
    }
    QJsonObject dbConfig = config["database"].toObject();
    QString dbType = dbConfig["type"].toString();
    QString host = dbConfig["host"].toString();
    QString dbName = dbConfig["databaseName"].toString();
    QString user = dbConfig["user"].toString();
    QString password = dbConfig["password"].toString();

    // 判断使用何种数据库,并且开始连接
    m_DataBaseType=dbType;
    if(m_DataBaseType=="MySQL"){
        MySqlDBManager::instance().connect(host,dbName,user,password);
    }else if(m_DataBaseType=="SQLServer") {
        SqlServerDBManager::instance().connect(host,dbName,user,password);
    }
}

DataBaseRepository::~DataBaseRepository()
{

}


QSqlQuery DataBaseRepository::executeQuery(const QString &queryStr, const QVariantList &bindValues)
{

    QElapsedTimer timer;
    timer.start(); // 启动计时器

    if(!isDataBaseConnection()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

    QSqlQuery query(getDataBase());
    query.prepare(queryStr);

    for (int i = 0; i < bindValues.size(); ++i) {
        query.bindValue(i, bindValues.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!bindValues.isEmpty() && bindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (int i = 0; i < bindValues.size(); ++i)
        {
            qDebug() << "Position" << i << ":" << bindValues[i].toString();
        }
    }
    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";
#endif

    return query;
}

QSqlQuery DataBaseRepository::executeQuery(const QString &queryStr, const QVariantMap &namedBindValues)
{

    QElapsedTimer timer;
    timer.start(); // 启动计时器

    if(!isDataBaseConnection()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

    QSqlQuery query(getDataBase());
    query.prepare(queryStr);
    for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
    {
        query.bindValue(it.key(), it.value());
    }
    if (!query.exec())
    {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!namedBindValues.isEmpty() && namedBindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
        {
            qDebug() << "Name" << it.key() << ":" << it.value().toString();
        }
    }
    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";

#endif

    return query;
}

QSqlQuery DataBaseRepository::executeQuery(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues)
{
    QElapsedTimer timer;
    timer.start(); // 启动计时器
    if(!isDataBaseConnection()){
        qDebug()<<"Database is not Open !!!";
        return QSqlQuery();
    }

    QSqlQuery query(getDataBase());

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

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!namedBindValues.isEmpty() && namedBindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (const auto &pair : namedBindValues)
        {
            qDebug() << "Name" << pair.first << ":" << pair.second.toString();
        }
    }
    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";
#endif

    return query;
}

QFuture<QSqlQuery> DataBaseRepository::executeQueryAsync(const QString &queryStr, const QVariantList &bindValues)
{
    return QtConcurrent::run([this, queryStr, bindValues]() {
        QElapsedTimer timer;
        timer.start(); // 启动计时器
        if(!isDataBaseConnection()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

        QSqlQuery query(getDataBase());
        query.prepare(queryStr);

        for (int i = 0; i < bindValues.size(); ++i) {
            query.bindValue(i, bindValues.at(i));
        }

        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!bindValues.isEmpty() && bindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (int i = 0; i < bindValues.size(); ++i)
        {
            qDebug() << "Position" << i << ":" << bindValues[i].toString();
        }
    }
    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";

#endif
        return query;
    });
}

QFuture<QSqlQuery> DataBaseRepository::executeQueryAsync(const QString &queryStr, const QVariantMap &namedBindValues)
{
    return QtConcurrent::run([this, queryStr, namedBindValues]() {
        QElapsedTimer timer;
        timer.start(); // 启动计时器
        if(!isDataBaseConnection()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

        QSqlQuery query(getDataBase());
        query.prepare(queryStr);
        for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
        {
            query.bindValue(it.key(), it.value());
        }
        if (!query.exec())
        {
            qDebug() << "Error executing query:" << query.lastError().text();
        }

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!namedBindValues.isEmpty() && namedBindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (auto it = namedBindValues.begin(); it != namedBindValues.end(); ++it)
        {
            qDebug() << "Name" << it.key() << ":" << it.value().toString();
        }
    }

    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";
#endif
        return query;

    });
}

QFuture<QSqlQuery> DataBaseRepository::executeQueryAsync(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues)
{
    return QtConcurrent::run([this, queryStr, namedBindValues]() {
        QElapsedTimer timer;
        timer.start(); // 启动计时器
//        qDebug() << "Starting async query: " << queryStr;
        // 异步查询实现
        if(!isDataBaseConnection()){
            qDebug()<<"Database is not Open !!!";
            return QSqlQuery();
        }

        QSqlQuery query(getDataBase());

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

#if defined(QT_DEBUG) || defined(DEBUG)

    qDebug() << "Executing SQL Query:" << queryStr;
    if(!namedBindValues.isEmpty() && namedBindValues.count()!=0){
        qDebug() << "Bound Values:";
        for (const auto &pair : namedBindValues)
        {
            qDebug() << "Name" << pair.first << ":" << pair.second.toString();
        }
    }
    qint64 elapsedDBTime = timer.elapsed();
    qDebug() << "Time taken for Db processing:" << elapsedDBTime << "ms";

#endif
        return query;
    });
}

QSqlDatabase DataBaseRepository::getDataBase()
{
    if(m_DataBaseType=="MySQL"){
        return MySqlDBManager::instance().getDatabase();
    }else if(m_DataBaseType=="SQLServer") {
        return SqlServerDBManager::instance().getDatabase();
    }
}

bool DataBaseRepository::isDataBaseConnection()
{
    if(m_DataBaseType=="MySQL"){
        return MySqlDBManager::instance().getDatabase().isOpen();
    }else if(m_DataBaseType=="SQLServer") {
        return SqlServerDBManager::instance().getDatabase().isOpen();
    }
}

