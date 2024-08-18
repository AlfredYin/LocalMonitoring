#include "dialog_controldevicestate.h"
#include "ui_dialog_controldevicestate.h"

Dialog_ControlDeviceState::Dialog_ControlDeviceState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ControlDeviceState)
{
    ui->setupUi(this);
}

Dialog_ControlDeviceState::Dialog_ControlDeviceState(DeviceStateInfo deivceStateInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ControlDeviceState)
{
    ui->setupUi(this);

    scene=new QGraphicsScene(0,0,50,50,this);
    ui->graphicsView->setScene(scene);

    // 当前的网关设置的信息，存储子设备信息
    m_DeivceStateInfo=deivceStateInfo;
    setWindowTitle("设备"+m_DeivceStateInfo.devicename+"的控制设备连接状态：");

    DeviceParam *deviceParam=new DeviceParam();
    deviceParam->devicename=m_DeivceStateInfo.devicename;

    Facade *facade = Facade::getInstance();
    deviceMediator = (DeviceMediator *)facade->retrieveMediator("DeviceMediator");
    m_DeivceStateInfo.controldevicestatelist=deviceMediator->getControlDeviceStateList(deviceParam).resultControlDeviceStateList;

    deviceControlMediator=(DeviceControlMediator *)facade->retrieveMediator("DeviceControlMediator");
    deviceControlMediator->registerViewComponent(this);

    QRectF sceneRect = scene->sceneRect();
    qreal sceneCenterX = sceneRect.center().x();
    qreal currentPosY = sceneRect.center().y() - (m_DeivceStateInfo.controldevicestatelist.size() * 42) / 2;

    foreach(auto controldevice,m_DeivceStateInfo.controldevicestatelist){
        ControlDeviceRectItem *item=new ControlDeviceRectItem(-10,-10,210,32);

        item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                       QGraphicsRectItem::ItemIsSelectable);

        item->setBrush(QBrush(QColor(230,128,222)));

        item->setControlDeviceState(controldevice);

        qreal itemWidth = item->boundingRect().width();
        qreal itemHeight = item->boundingRect().height();
        item->setPos(sceneCenterX - itemWidth / 2, currentPosY);
        currentPosY=currentPosY+10+itemHeight;

        scene->addItem(item);
        scene->clearSelection();
        item->setSelected(true);
    }

    // 控制设备部分
    // 右键点击，展开选择指令
    connect(ui->graphicsView,&AlfredGraphicsView::mouseRightClicked,[this](QPoint point){
        QPointF pointScene = ui->graphicsView->mapToScene(point);
        QGraphicsItem *item = scene->itemAt(pointScene, ui->graphicsView->transform());
        if (item == nullptr  || item->type()!=ControlDeviceRectItem::Type) {
            return;
        }
        ControlDeviceRectItem *theItem = qgraphicsitem_cast<ControlDeviceRectItem*>(item);
        if (theItem == nullptr) {
            return;
        }
        ControlDeviceState controlDeviceState = theItem->getControlDeviceState();
        Dialog_SendControlDeviceOrder *dialog = new Dialog_SendControlDeviceOrder(controlDeviceState);
        dialog->move(point.x(), point.y());
        if (dialog->exec() == QDialog::Accepted) {
            QString selectedCommand=dialog->getSendControlCommand();
            qDebug() << "SelectedCommand:" << selectedCommand;
            if(!selectedCommand.isEmpty()){
//                deviceMediator->
                controlDeviceState.devicecommands=selectedCommand;
                deviceMediator->sendMqttControlDeviceCommand(&controlDeviceState);
                sendCommandFlag=true;
                qDebug() << "MQTTClientService Had Send Command:"+selectedCommand+" GwClientId:"+controlDeviceState.gwclientid+"  Done!";
            }
        }
    });
}

Dialog_ControlDeviceState::~Dialog_ControlDeviceState()
{
    delete ui;
}

void Dialog_ControlDeviceState::update(IUpdateData *updateData)
{
    if (sendCommandFlag && updateData->getName() == "ControlDeviceCommandSendResult")
       {
           ControlDeviceCommandSendResult *result = (ControlDeviceCommandSendResult *)updateData;

           if (result->result)
           {
               QMessageBox::information(nullptr, "提示", "远程控制成功 "+result->publishTopic+" !");
               // 跟新状态
               foreach(auto item,scene->items()){
                   ControlDeviceRectItem *theItem = qgraphicsitem_cast<ControlDeviceRectItem*>(item);
                   ControlDeviceState theControlDeviceState=theItem->getControlDeviceState();
                   foreach(auto controlDeviceState,result->resultControlDeviceStateList){
                       if(theControlDeviceState.device==controlDeviceState.device){
                           theControlDeviceState.devicestate=controlDeviceState.devicestate;
                       }
                   }
                   theItem->setControlDeviceState(theControlDeviceState);
               }
               sendCommandFlag=false;
           }
           else
           {
               QMessageBox::information(nullptr, "提示", "远程控制失败");
               sendCommandFlag=false;
           }
       }
}
