#include "dialog_deivcesensorstate.h"
#include "ui_dialog_deivcesensorstate.h"
#include "sensorrectitem.h"

#include <QDebug>

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

    Facade *facade = Facade::getInstance();
    deviceMediator = (DeviceMediator *)facade->retrieveMediator("DeviceMediator");
    deviceMediator->registerViewComponent(this);

    scene=new QGraphicsScene(0,0,50,50,this);
    ui->graphicsView->setScene(scene);

    // 当前的网关设置的信息，没有存储子设备信息
    m_DeivceStateInfo=deivceStateInfo;
    setWindowTitle("设备"+m_DeivceStateInfo.devicename+"的所有传感器连接状态：");

    // 获取传感器连接状态，通过数据库获取
    DeviceParam *deviceParam=new DeviceParam();
    deviceParam->devicename=m_DeivceStateInfo.devicename;
    m_DeivceStateInfo.sensorstatelist=deviceMediator->getSensorStateList(deviceParam).resultSensorStateList;

//// 测试手动添加
//SensorState sensor1;sensor1.sensorname="温湿度传感器";sensor1.sensorstate="online";
//SensorState sensor2;sensor2.sensorname="光照传感器";sensor2.sensorstate="offline";

//m_DeivceStateInfo.sensorstatelist.append(sensor1);
//m_DeivceStateInfo.sensorstatelist.append(sensor2);

    // 获取场景的边界
    QRectF sceneRect = scene->sceneRect();

    // 计算场景的中心位置
    qreal sceneCenterX = sceneRect.center().x();
    qreal currentPosY = sceneRect.center().y() - (m_DeivceStateInfo.sensorstatelist.size() * 42) / 2;

    //根据传感器个数，连接状态，往view中开始绘图
    foreach(auto sensor,m_DeivceStateInfo.sensorstatelist){
        SensorRectItem *item=new SensorRectItem(-10,-10,180,32);

//        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
//                       QGraphicsRectItem::ItemIsSelectable |
//                       QGraphicsRectItem::ItemIsMovable);

        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                       QGraphicsRectItem::ItemIsSelectable);

        item->setBrush(QBrush(Qt::yellow));

        item->setSensorState(sensor);

        // 获取item的宽度和高度
        // 获取item的宽度和高度
        qreal itemWidth = item->boundingRect().width();
        qreal itemHeight = item->boundingRect().height();

        // 设置item的位置，使其中心对齐到scene的中心
        item->setPos(sceneCenterX - itemWidth / 2, currentPosY);
        currentPosY=currentPosY+10+itemHeight;

        scene->addItem(item);
        scene->clearSelection();
        item->setSelected(true);
    }
}

Dialog_DeivceSensorState::~Dialog_DeivceSensorState()
{
    delete ui;
}

void Dialog_DeivceSensorState::update(IUpdateData *updateData){

}
