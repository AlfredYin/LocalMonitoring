#include "queryhandler.h"

void QueryHandler::handleResultReady()
{
    QSqlQuery result = m_future.result();
    emit queryFinished(result);
}
