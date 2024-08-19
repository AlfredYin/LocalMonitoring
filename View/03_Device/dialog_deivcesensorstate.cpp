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
//    deviceMediator->registerViewComponent(this);

    historyDataMediator=(HistoryDataMediator*)facade->retrieveMediator("HistoryDataMediator");

    scene=new QGraphicsScene(0,0,50,50,this);
    ui->graphicsView->setScene(scene);

    // 当前的网关设置的信息，没有存储子设备信息
    m_DeivceStateInfo=deivceStateInfo;
    setWindowTitle("设备"+m_DeivceStateInfo.devicename+"的所有传感器连接状态：");

    // 获取传感器连接状态，通过数据库获取
    DeviceParam *deviceParam=new DeviceParam();
    deviceParam->devicename=m_DeivceStateInfo.devicename;
    m_DeivceStateInfo.sensorstatelist=deviceMediator->getSensorStateList(deviceParam).resultSensorStateList;

    // 获取场景的边界
    QRectF sceneRect = scene->sceneRect();

    // 计算场景的中心位置
    qreal sceneCenterX = sceneRect.center().x();
    qreal currentPosY = sceneRect.center().y() - (m_DeivceStateInfo.sensorstatelist.size() * 42) / 2;

    //根据传感器个数，连接状态，往view中开始绘图
    foreach(auto sensor,m_DeivceStateInfo.sensorstatelist){
        SensorRectItem *item=new SensorRectItem(-10,-10,200,32);

//        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
//                       QGraphicsRectItem::ItemIsSelectable |
//                       QGraphicsRectItem::ItemIsMovable);

        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                       QGraphicsRectItem::ItemIsSelectable);

        item->setBrush(QBrush(QColor(79,152,230)));

        item->setSensorState(sensor);

        // 获取item的宽度和高度
        // 获取item的宽度和高度
        qreal itemWidth = item->boundingRect().width();
        qreal itemHeight = item->boundingRect().height();

        // 设置item的位置，使其中心对齐到scene的中心
        item->setPos(sceneCenterX - itemWidth / 2-30, currentPosY);
        currentPosY=currentPosY+10+itemHeight;

        scene->addItem(item);
        scene->clearSelection();
        item->setSelected(true);
    }

    // 数据展示部分
    connect(ui->graphicsView,&AlfredGraphicsView::mouseRightClicked,[this](QPoint point){
        QPointF pointScene = ui->graphicsView->mapToScene(point);
        QGraphicsItem *item = scene->itemAt(pointScene, ui->graphicsView->transform());
        if (item == nullptr  || item->type()!=SensorRectItem::Type) {
            return;
        }
        SensorRectItem *theItem = qgraphicsitem_cast<SensorRectItem*>(item);
        if (theItem == nullptr) {
            return;
        }

        SensorState sensorState=theItem->getSensorState();

        // 通过dataMeidiaor获取该网关设备下的所有数据库数据
        // 将获取到的数据传给Dialog历史数据展示
        // 由Dialog根据两个参数进行列与行的填充
        SensorParam *sensorParam=new SensorParam();
        sensorParam->devicename=m_DeivceStateInfo.devicename;
        sensorParam->sensorname=sensorState.sensor;
        QList<SensorHistoryData> list=historyDataMediator->get_HistoryDataSync(sensorParam);

        Dialog_HistoryData *dialog=new Dialog_HistoryData(list,sensorState,this);
        dialog->move(point.x(), point.y());
        dialog->show();
    });
}

Dialog_DeivceSensorState::~Dialog_DeivceSensorState()
{
    delete ui;
}
