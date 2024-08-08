#include "dialog_setdevicemodel.h"
#include "ui_dialog_setdevicemodel.h"

Dialog_SetDeviceModel::Dialog_SetDeviceModel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SetDeviceModel)
{
    ui->setupUi(this);
}

Dialog_SetDeviceModel::~Dialog_SetDeviceModel()
{
    delete ui;
}

DeviceStateInfo Dialog_SetDeviceModel::getDeivceStateInfo()
{
    m_DeiveStateInfo.devicename=ui->lineEdit_DeviceName->text();
    m_DeiveStateInfo.connectingflag=ui->checkBox->checkState()?1:0;
    return m_DeiveStateInfo;
}
