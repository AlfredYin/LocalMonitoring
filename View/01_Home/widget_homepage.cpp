#include "widget_homepage.h"
#include "ui_widget_homepage.h"

#include "Facade.h"
#include "usermediator.h"
#include "loginparam.h"
#include "loginresult.h"
#include "mainwindow.h"
#include "changepwddialog.h"
#include "ntpservice.h"
#include "drawmainwindow.h"
#include "scenefilehelper.h"
#include "refreshtextitem.h"
#include "userhelper.h"

#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QDateTime>
#include "logindialog.h"

Widget_HomePage::Widget_HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_HomePage)
{
    ui->setupUi(this);
    ui->pushButtonChangePassword->setVisible(false);

    Facade *facade = Facade::getInstance();
    homeMediator = (HomeMediator *)facade->retrieveMediator("HomeMediator");
    homeMediator->registerViewComponent(this);

    time_Timer=new QTimer(this);
    connect(time_Timer, &QTimer::timeout, this, &Widget_HomePage::updateTimeLabel);
    time_Timer->start(1000);

    // 填充视图
    roadScene();

    // 设置视图属性
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);     禁止全选
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    // 设置重新加载Scene组件
    refreshItem = new RefreshTextItem("Refresh");

    QObject::connect(refreshItem, &RefreshTextItem::refreshClicked, [this]() {
        Widget_HomePage::roadScene();
        // 获取视图信息
        DeviceParam *param=new DeviceParam();
        homeMediator->getDeviceStateList(param);
    });

    scene->addItem(refreshItem);
    refreshItem->setPos(300,10);


    // 获取视图信息
    DeviceParam *param=new DeviceParam();
    homeMediator->getDeviceStateList(param);

    // 设置回调填充信息
}

Widget_HomePage::~Widget_HomePage()
{
    delete ui;
}

void Widget_HomePage::update(IUpdateData *updateData)
{
//    qDebug()<<"void MainWindow::update(IUpdateData *updateData)";
//    qDebug()<<"updateData->getName()="<<updateData->getName()<<endl;

    if(updateData->getName()=="LoginResult"){
        LoginResult *loginResult = static_cast<LoginResult *>(updateData);
        // 登录成功
        if(loginResult->result){
            loginDialog->hide();
            ui->pushButtonLogin->setText("用户："+loginResult->realname+" 已登录");
            ui->pushButtonChangePassword->setVisible(true);
            ui->pushButtonLogin->setEnabled(false);

//            showDeviceMainWindow();
        }else{
            // 计数，超三次关闭程序
            m_Count++;
            if(m_Count>=3){
                QMessageBox::warning(this,"警告","超过三次，登录失败");
                this->close();
            }
        }

    }else if(updateData->getName()=="ChangePwdResult"){

        LoginResult *loginResult = static_cast<LoginResult *>(updateData);
        if(loginResult->result){
            if(changePwdDialog!=nullptr){
                changePwdDialog->hide();
            }
        }
    }else if(updateData->getName()=="DeviceStateListResult"){
        DeviceStateListResult *result = static_cast<DeviceStateListResult *>(updateData);
        loadDeviceState(result);
    }else if(updateData->getName()=="GeneralResult"){
         QMessageBox::information(nullptr, "GeneralResult", "通用失败提示");
    }
    else{
        int a=0;
    }
}

void Widget_HomePage::roadScene()
{
    qDebug()<<"void Widget_HomePage::roadScene()";
    if(scene==nullptr){
        scene=new AlfredGraphicsScene(-300,-100,600,200,this);
        ui->graphicsView->setScene(scene);
    }else{
        QList<QGraphicsItem*> items = scene->items();
        for (QGraphicsItem* item : items) {
            if(item==refreshItem){
                continue;
            }else{
                scene->removeItem(item);
                delete item;
            }
        }
    }
    SceneFileHelper::loadItemToScene(scene,"./pattern.json");
}

void Widget_HomePage::loadDeviceState(DeviceStateListResult *result)
{
    foreach(DeviceStateInfo deviceInfo,result->resultList){
        foreach (QGraphicsItem* item, scene->items()) {
            if(item->type()==DeviceRectItem::Type){     // 设备模型
                DeviceRectItem *theItem;
                theItem=qgraphicsitem_cast<DeviceRectItem *>(item);
                DeviceStateInfo itemInfo=theItem->getDeviceStateInfo();
                if(itemInfo.devicename==deviceInfo.devicename){
                    itemInfo.connectingflag=deviceInfo.connectingflag;
                    theItem->setDeviceStateInfo(itemInfo);
                    break;
                }
            }
        }
    }
}

void Widget_HomePage::on_pushButtonLogin_clicked()
{
    if(loginDialog==nullptr){
        loginDialog = new LoginDialog(this);
    }
    loginDialog->show();
}

void Widget_HomePage::on_pushButtonChangePassword_clicked()
{
    if(changePwdDialog==nullptr){
        changePwdDialog=new ChangePwdDialog(this);
    }
    changePwdDialog->show();
}

void Widget_HomePage::updateTimeLabel()
{
    QDateTime time=QDateTime::currentDateTime();
    QString timeStr=time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_time->setText(timeStr);
}

void Widget_HomePage::on_pushButton_Draw_clicked()
{
    if(!UserHelper::instance()->isLogined()){
        QMessageBox::warning(this,"警告","请先登录");
        return;
    }


//    DrawMainWindow drawMainWindow;
//    drawMainWindow.show();
    if(drawMainWindow==nullptr){
        drawMainWindow=new DrawMainWindow(this);
    }
    drawMainWindow->show();
}
