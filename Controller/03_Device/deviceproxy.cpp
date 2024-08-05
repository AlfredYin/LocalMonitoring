#include "deviceproxy.h"
#include "mysqldbmanager.h"
#include "baseresult.h"
#include "deviceparam.h"

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

}
