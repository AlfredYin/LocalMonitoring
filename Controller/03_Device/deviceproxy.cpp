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
    DeviceStateResult *deviceStateResult=new DeviceStateResult();

    // 获取数据库连接
    QSqlQuery query(MySqlDBManager::instance().getDatabase());
    query.prepare("SELECT id,device_name,connection_status FROM `AlfredDb`.`device_connection_status`;");
    if(query.exec()){
        while(query.next()){
            int id = query.value(0).toInt();
            QString device_name = query.value(1).toString();
            QString connection_status=query.value(2).toString();
//            DeviceParam deviceStateInfo;

//            deviceStateInfo.id=id;
//            deviceStateInfo.device_name=device_name;
//            deviceStateInfo.connection_status=connection_status;

//            deviceStateResult->deviceStateList.append(deviceStateInfo);
        }
    }

//    if(deviceStateResult->deviceStateList.count()==0){
    if(true){
//        GeneralResult *result = new GeneralResult();
        sendNotification("get_devicestate_error",static_cast<void *>(deviceStateResult));
    }else{
        sendNotification("get_devicestate_success",static_cast<void *>(deviceStateResult));
    }
}

void DeviceProxy::getDeviceStatesList(DeviceParam *deviceParam)
{
    m_DeviceParam=*deviceParam;
    QString queryStr="SELECT GwId,GwClientId,GwConnectedDate,GwConnectedTltDate,"
                         "GwConnectingFlag,GwType FROM `AlfredDb`.`SysGatewayConnected`;";
    queryStr=queryStr+RegisterStrFilter(deviceParam);
    QueryHandler *handler=new QueryHandler(this);

    QObject::connect(handler, &QueryHandler::queryFinished, [this](QSqlQuery query) {

        DeviceStateResult *deiveStateResult = new DeviceStateResult();
        deiveStateResult->result = false;
        if(query.first()){
            float id = query.value(0).toFloat();
            QString username = query.value(1).toString();
            QString realname = query.value(2).toString();
            QString encryptedpaswd = query.value(3).toString();
            QString salt = query.value(4).toString();

//            UserHelper* userHelper = UserHelper::instance();
            if(true){
//            if(encryptedpaswd==EncryptUserPassword(m_UserInfo.passwd,salt)){
                deiveStateResult->result = true;
//                deiveStateResult->username=username;
//                loginResult->realname=realname;
////                loginResult->passwd=userHelper->getUserInfo().passwd;
//                loginResult->passwd=m_UserInfo.passwd;
//                loginResult->encryptedpaswd=encryptedpaswd;
            }
        }else{
//            loginResult->result = false;

        }

        sendNotification("login_finished", static_cast<void *>(deiveStateResult));
    });

    handler->startQuery(queryStr,RegisterListFilter(deviceParam));
}

QList<QPair<QString, QVariant> > DeviceProxy::RegisterListFilter(DeviceParam *deviceParam)
{
    QList<QPair<QString, QVariant>> registerList;

    if(!m_DeviceParam.devicename.isEmpty()){
        QPair<QString, QVariant> devNamePair={":devicename",deviceParam->devicename};
        registerList.append(devNamePair);
    }
    return registerList;
}

QString DeviceProxy::RegisterStrFilter(DeviceParam *deviceParam)
{
    QString registerStr="where ";
    if(!m_DeviceParam.devicename.isEmpty()){
        registerStr=registerStr+"GwClientId=:devicename";
    }
    return registerStr;
}


