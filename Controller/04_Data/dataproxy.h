#ifndef DATAPROXY_H
#define DATAPROXY_H

#include "databaserepository.h"
#include "Proxy.h"
#include "sensorparam.h"
#include "sensorhistorydataresult.h"

class DataProxy:public Proxy,DataBaseRepository
{
public:
    DataProxy();

    void get_HistoryData(SensorParam *sensorParam);


private:
    QList<QPair<QString, QVariant>> RegisterListFilter(SensorParam *sensorParam);

    QString RegisterStrFilter(SensorParam *sensorParam);
};

#endif // DATAPROXY_H
