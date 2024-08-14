#ifndef SQLSERVERDBMANAGER_H
#define SQLSERVERDBMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

class SqlServerDBManager
{
public:
    static SqlServerDBManager& instance(){
        static SqlServerDBManager instance; // 唯一实例
        return instance;
    }

    bool connect(const QString& host, const QString& dbName, const QString& user, const QString& password){
        QMutexLocker locker(&mutex);

        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QODBC");        // 修改使用Sql Server
            // 使用 DSN-less 连接字符串
            QString connectionString = QString("DRIVER={SQL Server};SERVER=%1;DATABASE=%2;UID=%3;PWD=%4;")
                                       .arg(host)
                                       .arg(dbName)
                                       .arg(user)
                                       .arg(password);
            db.setDatabaseName(connectionString);

            if (!db.open()) {
                qDebug() << "Failed to connect to database:" << db.lastError().text();
                return false;
            }
            qDebug() << "Connected to database successfully!";
        }
        return true;
    }

    QSqlDatabase getDatabase() {
        return db;
    }

    QString getDataBaseType(){
        return "sqlserver";
    }

private:
    QSqlDatabase db;
    QMutex mutex;

    // 私有构造函数和析构函数
    SqlServerDBManager() {}
    ~SqlServerDBManager() {
        if (db.isOpen()) {
            db.close();
        }
    }

    // 禁用复制和赋值操作
    SqlServerDBManager(const SqlServerDBManager&) = delete;
    SqlServerDBManager& operator=(const SqlServerDBManager&) = delete;

};


#endif // SQLSERVERDBMANAGER_H
