#ifndef SENSORHISTORYDATARESULT_H
#define SENSORHISTORYDATARESULT_H

#include "baseresult.h"
#include "sensorhistorydata.h"
#include <QList>

class SensorHistoryDataResult : public BaseResult
{
public:
    SensorHistoryDataResult();

public:
    QList<SensorHistoryData> sensorHistoryDataList;
};

#endif // SENSORHISTORYDATARESULT_H
