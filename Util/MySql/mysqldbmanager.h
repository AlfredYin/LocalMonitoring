#ifndef MYSQLDBMANAGER_H
#define MYSQLDBMANAGER_H


#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QString>
#include <QMutex>
#include <QMutexLocker>

class MySqlDBManager {
public:
    static MySqlDBManager& instance() {
        static MySqlDBManager instance; // 唯一实例
        return instance;
    }

    bool connect(const QString& host, const QString& dbName, const QString& user, const QString& password) {
        QMutexLocker locker(&mutex);

        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(host);
            db.setDatabaseName(dbName);
            db.setUserName(user);
            db.setPassword(password);

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

private:
    QSqlDatabase db;
    QMutex mutex;

    // 私有构造函数和析构函数
    MySqlDBManager() {}
    ~MySqlDBManager() {
        if (db.isOpen()) {
            db.close();
        }
    }

    // 禁用复制和赋值操作
    MySqlDBManager(const MySqlDBManager&) = delete;
    MySqlDBManager& operator=(const MySqlDBManager&) = delete;
};
#endif // MYSQLDBMANAGER_H
