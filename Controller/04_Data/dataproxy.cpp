#include "dataproxy.h"
#include "queryhandler.h"

#include <QDebug>

DataProxy::DataProxy()
{
    PROXY_NAME = "DataProxy";
}

void DataProxy::get_HistoryData(SensorParam *sensorParam)
{
    // 异步获取Sql
    QString queryStr=QString("SELECT TOP 10 Id, GwClientId, GwPubTopic, Humidity, Temperature, HeatIndex, CO2conc, VOCconc, Illum, GwMessDate FROM DataEsp32 ");
//    QString queryStr=QString("SELECT TOP 100 Id FROM DataEsp32 ");
//    QString queryStr=QString("SELECT Id FROM DataEsp32 Limit 100");

    queryStr=queryStr+RegisterStrFilter(sensorParam);
    QueryHandler *handler=new QueryHandler(this);

    QObject::connect(handler, &QueryHandler::queryFinished, [this](QSqlQuery query) {

        SensorHistoryDataResult *result=new SensorHistoryDataResult();
        result->result = false;

        result->sensorHistoryDataList.reserve(100); // 预分配空间（根据实际数据量调整） 测试是10条

        SensorHistoryData sensorHistoryData; // 网关设备

        QElapsedTimer timer;
        timer.start(); // 启动计时器
        int i=0;

        // 存在问题，解释query太耗时，没有找到原因
        while (query.next()) {
            i++;
            // 直接使用 query.value() 的返回值进行赋值
            sensorHistoryData.id = query.value(0).toInt();
            sensorHistoryData.devicename = query.value(1).toString();
            sensorHistoryData.gwpubtopic = query.value(2).toString();
            sensorHistoryData.humidity = query.value(3).toString();
            sensorHistoryData.temperature = query.value(4).toString();
            sensorHistoryData.heatIndex = query.value(5).toString();
            sensorHistoryData.co2conc = query.value(6).toString();
            sensorHistoryData.vocconc = query.value(7).toString();
            sensorHistoryData.illum = query.value(8).toString();
            sensorHistoryData.gwdatadate = query.value(9).toString();

            // 将网关设备添加到结果列表中
            result->sensorHistoryDataList.append(sensorHistoryData);
        }
        result->result=true;

        qDebug()<<"i="<<i;

        qint64 elapsedHandleQueryTime = timer.elapsed(); // 获取经过的时间（毫秒）
        qDebug() << "Time taken for query processing:" << elapsedHandleQueryTime << "ms";

        sendNotification("get_historydata_finished", static_cast<void *>(result));
    });

    handler->startQuery(queryStr,RegisterListFilter(sensorParam));
}

QList<SensorHistoryData> DataProxy::get_HistoryDataSync(SensorParam *sensorParam)
{
    QString queryStr=QString("SELECT TOP 10 Id, GwClientId, GwPubTopic, Humidity, Temperature, HeatIndex, CO2conc, VOCconc, Illum, GwMessDate FROM DataEsp32 ");
    queryStr=queryStr+RegisterStrFilter(sensorParam);
    QSqlQuery query=executeQuery(queryStr,RegisterListFilter(sensorParam));
    QList<SensorHistoryData> sensorHistoryDataList;
    // 存在问题，解释query太耗时，没有找到原因
    while (query.next()) {

        SensorHistoryData sensorHistoryData;

        sensorHistoryData.id = query.value(0).toInt();
        sensorHistoryData.devicename = query.value(1).toString();
        sensorHistoryData.gwpubtopic = query.value(2).toString();
        sensorHistoryData.humidity = query.value(3).toString();
        sensorHistoryData.temperature = query.value(4).toString();
        sensorHistoryData.heatIndex = query.value(5).toString();
        sensorHistoryData.co2conc = query.value(6).toString();
        sensorHistoryData.vocconc = query.value(7).toString();
        sensorHistoryData.illum = query.value(8).toString();
        sensorHistoryData.gwdatadate = query.value(9).toString().left(19);

        sensorHistoryDataList.append(sensorHistoryData);
    }
    return sensorHistoryDataList;
}

QList<QPair<QString, QVariant> > DataProxy::RegisterListFilter(SensorParam *sensorParam)
{
    QList<QPair<QString, QVariant>> registerList;

    if(!sensorParam->devicename.isEmpty()){
        QPair<QString, QVariant> devNamePair={":devicename",sensorParam->devicename};
        registerList.append(devNamePair);
    }
    return registerList;
}

QString DataProxy::RegisterStrFilter(SensorParam *sensorParam)
{
    QString registerStr=" where ";
    if(!sensorParam->devicename.isEmpty()){
        registerStr=registerStr+"GwClientId=:devicename"+" ORDER BY Id DESC;";
        return registerStr;
    }
    return QString(" ORDER BY Id DESC;");
//    return QString();
}
