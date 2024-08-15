#include "dialog_sendcontroldeviceorder.h"
#include "ui_dialog_sendcontroldeviceorder.h"

Dialog_SendControlDeviceOrder::Dialog_SendControlDeviceOrder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SendControlDeviceOrder)
{
    ui->setupUi(this);
}

Dialog_SendControlDeviceOrder::Dialog_SendControlDeviceOrder(ControlDeviceState controlDeviceState, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SendControlDeviceOrder)
{
    ui->setupUi(this);

    m_ControlDeviceState=controlDeviceState;

//    Facade *facade = Facade::getInstance();
//    deviceMediator = (DeviceMediator *)facade->retrieveMediator("DeviceMediator");
//    deviceMediator->registerViewComponent(this);

    setWindowTitle("控制设备"+m_ControlDeviceState.devicename+"可以供下发的指令如下：");
    QString commands=m_ControlDeviceState.devicecommands;

    // 使用 QString::split 分割字符串
    QStringList commandList = commands.split(QRegularExpression("[/;]"));

    // 遍历每个子串，并提取第一个字符
    int i=0;
    foreach (const QString &command, commandList) {
        i++;
        if (!command.isEmpty()) {
            ui->listWidget->addItem(command);
        }
    }
}

QString Dialog_SendControlDeviceOrder::getSendControlCommand()
{
    QListWidgetItem *currentItem = ui->listWidget->currentItem();
    if (currentItem) {
        return currentItem->text();
    } else {
        return QString();
    }
}

Dialog_SendControlDeviceOrder::~Dialog_SendControlDeviceOrder()
{
    delete ui;
}
