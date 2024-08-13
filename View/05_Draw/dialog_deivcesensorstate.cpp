#include "dialog_deivcesensorstate.h"
#include "ui_dialog_deivcesensorstate.h"
#include "devicerectitem.h"

Dialog_DeivceSensorState::Dialog_DeivceSensorState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DeivceSensorState)
{
    ui->setupUi(this);
}

Dialog_DeivceSensorState::Dialog_DeivceSensorState(DeviceStateInfo deivceStateInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DeivceSensorState)
{
    ui->setupUi(this);
    m_DeivceStateInfo=deivceStateInfo;
    scene=new QGraphicsScene(-300,-100,600,200,this);
    ui->graphicsView->setScene(scene);

    setWindowTitle("设备"+m_DeivceStateInfo.devicename+"的所有传感器连接状态：");

    // 获取传感器连接状态，通过数据库获取

    // 测试手动添加
    SensorState sensor1;sensor1.sensorname="温湿度传感器";sensor1.sensorstate="online";
    SensorState sensor2;sensor2.sensorname="光照传感器";sensor2.sensorstate="offline";

    m_DeivceStateInfo.sensorstatelist.append(sensor1);
    m_DeivceStateInfo.sensorstatelist.append(sensor2);

    //根据传感器个数，连接状态，往view中开始绘图
    foreach(auto sensor,m_DeivceStateInfo.sensorstatelist){
        DeviceRectItem *item=new DeviceRectItem(-10,-10,100,30);
        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                       QGraphicsRectItem::ItemIsSelectable |
                       QGraphicsRectItem::ItemIsMovable);
        item->setBrush(QBrush(Qt::yellow));

        DeviceStateInfo deviceStateInfo;

        deviceStateInfo.devicename=sensor.sensorname;
        deviceStateInfo.connectingflag=sensor.sensorstate=="online"?1:0;

        item->setDeviceStateInfo(deviceStateInfo);

        item->setPos(-100+qrand()%200,-60+qrand()%120);

        scene->addItem(item);
        scene->clearSelection();
        item->setSelected(true);
    }
}

Dialog_DeivceSensorState::~Dialog_DeivceSensorState()
{
    delete ui;
}
