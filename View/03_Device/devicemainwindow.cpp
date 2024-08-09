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

}

void DeviceMainWindow::on_pushButton_clicked()
{
//    DeviceStateInfo info;
//    deviceMediator->getDeviceState(&info);
}
