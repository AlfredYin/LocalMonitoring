#include "deviceproxy.h"
#include "mysqldbmanager.h"
#include "baseresult.h"
#include "deviceparam.h"
#include "devicestateresult.h"
#include "queryhandler.h"

#include <QDebug>

DeviceProxy::DeviceProxy()
{
    PROXY_NAME = "DeviceProxy";
}

void DeviceProxy::getDeviceState(DeviceParam *deviceParam)
{
    DeviceStateListResult *deviceStateListResult=new DeviceStateListResult();
    deviceStateListResult->result=false;

    // 获取数据库连接
    QSqlQuery query(MySqlDBManager::instance().getDatabase());
    query.prepare("SELECT GwId,GwClientId,GwConnectingFlag,GwType FROM SysGatewayConnected;");
    if(query.exec()){
        while(query.next()){
            int id = query.value(0).toInt();
            QString device_name = query.value(1).toString();
            int connection_status=query.value(2).toInt();

            DeviceStateInfo deviceStateInfo;
            deviceStateInfo.devicename=device_name;
            deviceStateInfo.connectingflag=connection_status;
            // 传感器部分，忽略
            deviceStateListResult->resultList.append(deviceStateInfo);
        }
    }

    if(true){
        sendNotification("get_devicestate_error",static_cast<void *>(deviceStateListResult));
    }else{
        sendNotification("get_devicestate_success",static_cast<void *>(deviceStateListResult));
    }
}

void DeviceProxy::getDeviceStatesList(DeviceParam *deviceParam)
{
    m_DeviceParam=*deviceParam;
    QString queryStr="SELECT GwId,GwClientId,GwConnectingFlag,GwType FROM SysGatewayConnected;";
    queryStr=queryStr+RegisterStrFilter(deviceParam);
    QueryHandler *handler=new QueryHandler(this);

    QObject::connect(handler, &QueryHandler::queryFinished, [this](QSqlQuery query) {

        DeviceStateListResult *deviceStateListResult = new DeviceStateListResult();
        deviceStateListResult->result = false;

        while(query.next()){
            int id = query.value(0).toInt();
            QString device_name = query.value(1).toString();
            int connection_status=query.value(2).toInt();

            DeviceStateInfo deviceStateInfo;
            deviceStateInfo.devicename=device_name;
            deviceStateInfo.connectingflag=connection_status;
            // 传感器部分，忽略
            deviceStateListResult->resultList.append(deviceStateInfo);
            deviceStateListResult->result=true;
        }

        sendNotification("get_devicestatelist_finished", static_cast<void *>(deviceStateListResult));
    });

    handler->startQuery(queryStr,RegisterListFilter(deviceParam));
}

SensorStateResult DeviceProxy::getSensorStateList(DeviceParam *deviceParam)
{
    SensorStateResult sensorStateListResult;

    QString queryStr="SELECT Id,Sensor,SensorName,SensorState,SensorProtocol,SensorFlag FROM SensorRegister";
    queryStr=queryStr+RegisterStrFilter(deviceParam);
    QSqlQuery query=executeQuery(queryStr,RegisterListFilter(deviceParam));

    while(query.next()){
        SensorState sensorState;
        int id=query.value(0).toInt();
        QString sensor=query.value(1).toString();
        QString sensorname=query.value(2).toString();
        QString sensorstate=query.value(3).toString();
        QString sensorProtocol=query.value(4).toString();
        int SensorFlag=query.value(5).toInt();
        sensorState.id=id;
        sensorState.sensor=sensor;
        sensorState.sensorname=sensorname;
        sensorState.sensorstate=sensorstate;
        sensorState.sensorprotocol=sensorProtocol;
        sensorState.sensorflag=SensorFlag;
        sensorStateListResult.resultSensorStateList.append(sensorState);
    }
    return sensorStateListResult;
}

QList<QPair<QString, QVariant> > DeviceProxy::RegisterListFilter(DeviceParam *deviceParam)
{
    QList<QPair<QString, QVariant>> registerList;

    if(!deviceParam->devicename.isEmpty()){
        QPair<QString, QVariant> devNamePair={":devicename",deviceParam->devicename};
        registerList.append(devNamePair);
    }
    return registerList;
}

QString DeviceProxy::RegisterStrFilter(DeviceParam *deviceParam)
{
    QString registerStr=" where ";
    if(!deviceParam->devicename.isEmpty()){
        registerStr=registerStr+"GwClientId=:devicename";
        return registerStr;
    }
    return QString();
}


