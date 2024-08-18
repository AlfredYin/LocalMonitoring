#include "deviceproxy.h"
#include "baseresult.h"
#include "deviceparam.h"
#include "devicestateresult.h"
#include "queryhandler.h"

#include <QDebug>

DeviceProxy::DeviceProxy()
{
    PROXY_NAME = "DeviceProxy";
}

void DeviceProxy::getDeviceState(DeviceParam *deviceParam)      // 暂时已经弃用
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
//    QString queryStr="SELECT GwId,GwClientId,GwConnectingFlag,GwType FROM SysGatewayConnected;";
    QString queryStr=QString("SELECT SysGatewayConnected.GwId,SysGatewayConnected.GwClientId,SysGatewayConnected.GwConnectingFlag,SysGatewayConnected.GwType,")+
            QString("SysGatewayRegister.GwSubTopic,SysGatewayRegister.GwPubTopic,SysGatewayRegister.GwPubStatusTopic FROM SysGatewayConnected ")+
            QString("JOIN SysGatewayRegister ON SysGatewayConnected.GwClientId=SysGatewayRegister.GwClientId;");        // 多表联合查询
    queryStr=queryStr+RegisterStrFilter(deviceParam);
    QueryHandler *handler=new QueryHandler(this);

    QObject::connect(handler, &QueryHandler::queryFinished, [this](QSqlQuery query) {

        DeviceStateListResult *deviceStateListResult = new DeviceStateListResult();
        deviceStateListResult->result = false;

        while(query.next()){
            int id = query.value(0).toInt();
            QString device_name = query.value(1).toString();
            int connection_status=query.value(2).toInt();
            int gwtype=query.value(3).toInt();
            QString gwsubtopic=query.value(4).toString();
            QString gwpubtopic=query.value(5).toString();
            QString gwpubstatustopic=query.value(6).toString();

            DeviceStateInfo deviceStateInfo;        // 网关设备
            deviceStateInfo.devicename=device_name;
            deviceStateInfo.connectingflag=connection_status;
            deviceStateInfo.gwtype=gwtype;
            deviceStateInfo.gwsubtopic=gwsubtopic;
            deviceStateInfo.gwpubtopic=gwpubtopic;
            deviceStateInfo.gwpubstatustopic=gwpubstatustopic;
            // 传感器子设备，控制子设备部分，忽略
            deviceStateListResult->resultList.append(deviceStateInfo);  // 将网关设备添加到放回结果的列表中
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

ControlDeviceListResult DeviceProxy::getControlDeviceStateList(DeviceParam *deviceParam)
{
    ControlDeviceListResult controlDeviceListResult;
    QString queryStr="SELECT Id,Device,DeviceName,DeviceCommands,DeviceState,GwType FROM DeviceRegister";
    queryStr=queryStr+RegisterStrFilter(deviceParam);
    QSqlQuery query=executeQuery(queryStr,RegisterListFilter(deviceParam));
    while(query.next()){
        ControlDeviceState controlDeviceState;
        int id=query.value(0).toInt();
        QString device=query.value(1).toString();
        QString devicename=query.value(2).toString();
        QString devicecommands=query.value(3).toString();
        QString devicestate=query.value(4).toString();
        int gwtype=query.value(5).toInt();

        controlDeviceState.id=id;
        controlDeviceState.device=device;
        controlDeviceState.devicename=devicename;
        controlDeviceState.devicecommands=devicecommands;
        controlDeviceState.devicestate=devicestate;
        controlDeviceState.gwclientid=deviceParam->devicename;
        controlDeviceState.gwtype=gwtype;
        controlDeviceListResult.resultControlDeviceStateList.append(controlDeviceState);
    }
    return controlDeviceListResult;
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


