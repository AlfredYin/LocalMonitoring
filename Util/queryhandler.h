#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVariant>
#include <QFuture>
#include <QFutureWatcher>
#include <QThreadPool>
#include <QPair>
#include <QFutureWatcher>
#include <QObject>

#include "databaserepository.h"

class QueryHandler : public QObject
{
    Q_OBJECT
public:
    explicit QueryHandler(DataBaseRepository *repo, QObject *parent = nullptr) : QObject(parent), m_repo(repo) {
        m_watcher = new QFutureWatcher<QSqlQuery>();
        m_future = QFuture<QSqlQuery>();

        connect(m_watcher, &QFutureWatcher<QSqlQuery>::finished, this, &QueryHandler::handleResultReady);
    }

    void startQuery(const QString &queryStr, const QVariantList &bindValues = QVariantList())
    {
//        m_future = m_repo->executeQueryAsync(queryStr, bindValues);
//        m_watcher.setFuture(m_future);
    }

    void startQuery(const QString &queryStr, const QVariantMap &namedBindValues)
    {
//        m_future = m_repo->executeQueryAsync(queryStr, namedBindValues);
//        m_watcher.setFuture(m_future);
    }

    void startQuery(const QString &queryStr, const QList<QPair<QString, QVariant>> &namedBindValues)
    {
//        qDebug() << "Starting query with QList<QPair<QString, QVariant>>: " << queryStr;
        m_future = m_repo->executeQueryAsync(queryStr, namedBindValues);
        m_watcher->setFuture(m_future);
        // connect(m_watcher, &QFutureWatcher<QSqlQuery>::finished, this, &QueryHandler::handleResultReady);

//        qDebug() << "Future set for QList<QPair<QString, QVariant>> query: " << queryStr;
    }

signals:
    void queryFinished(QSqlQuery query);

public slots:
    void handleResultReady();

private:
    QFutureWatcher<QSqlQuery> *m_watcher;
    QFuture<QSqlQuery> m_future;
    DataBaseRepository *m_repo;
};

#endif // QUERYHANDLER_H
