#include "devicemainwindow.h"
#include "ui_devicemainwindow.h"
#include "Patterns/Facade.h"

#include <QDebug>
#include <QMessageBox>

DeviceMainWindow::DeviceMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeviceMainWindow)
{
    ui->setupUi(this);
    Facade *facade = Facade::getInstance();
    deviceMediator = (DeviceMediator *)facade->retrieveMediator("DeviceMediator");
    deviceMediator->registerViewComponent(this);
}

DeviceMainWindow::~DeviceMainWindow()
{
    delete ui;
}

void DeviceMainWindow::update(IUpdateData *updateData)
{
    qDebug()<<"updateData->getName()="<<updateData->getName()<<endl;
    if(updateData->getName()=="DeviceStateResult"){
        DeviceStateResult *result=static_cast<DeviceStateResult *>(updateData);
        updateDeivceState(result);
    }else if(updateData->getName()=="GeneralResult"){
         QMessageBox::information(nullptr, "", "通用失败提示");
    }
    else{

    }
}

void DeviceMainWindow::updateDeivceState(DeviceStateResult *result)
{
    foreach(auto deivceStateInfo,result->deviceStateList){
        QString str=QString::asprintf("id:%d",deivceStateInfo.id)+
                ",devicename:"+deivceStateInfo.device_name+
                ",connection:"+deivceStateInfo.connection_status;

        ui->plainTextEdit->appendPlainText(str);
    }
}

void DeviceMainWindow::on_pushButton_clicked()
{
    DeviceStateInfo info;
    deviceMediator->getDeviceState(&info);
}
