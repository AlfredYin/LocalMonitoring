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

        m_host=host;
        m_dbName=dbName;
        m_user=user;
        m_password=password;

        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(m_host);
            db.setDatabaseName(m_dbName);
            db.setUserName(m_user);
            db.setPassword(m_password);

            if (!db.open()) {
                qDebug() << "Failed to connect to database:" << db.lastError().text();
                return false;
            }
            qDebug() << "Connected to database successfully!";
        }
        return true;
    }

    QSqlDatabase getDatabase() {
        if (!db.isOpen()) {
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(m_host);
            db.setDatabaseName(m_dbName);
            db.setUserName(m_user);
            db.setPassword(m_password);
            if (!db.open()){
                qDebug() << "Failed to connect to database:" << db.lastError().text();
                return QSqlDatabase();
            }
            qDebug() << "Reconnected to database successfully!";
        }
        return db;
    }

    QString getDataBaseType(){
        return "mysql";
    }

private:
    QSqlDatabase db;
    QMutex mutex;

    QString m_host;
    QString m_dbName;
    QString m_user;
    QString m_password;

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
