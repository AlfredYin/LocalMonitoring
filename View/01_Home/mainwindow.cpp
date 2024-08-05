#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Patterns/Facade.h"
#include "usermediator.h"
#include "loginparam.h"
#include "loginresult.h"
#include "mainwindow.h"
#include "changepwddialog.h"
#include "mainwindowmediator.h"

#include <QTabWidget>
#include <QDebug>
#include <QMessageBox>
#include "logindialog.h"
#include "ntptimeresult.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Facade *facade = Facade::getInstance();
    mainWindowMediator=(MainWindowMediator *)facade->retrieveMediator("MainWindowMediator");
    mainWindowMediator->registerViewComponent(this);

    // 选项卡添加元素
    widget_HomePage=new Widget_HomePage(this);
    ui->tabWidget->addTab(widget_HomePage,"主页");

    mainWindowMediator->startGetNtpTime();

    label_ntp_status=new QLabel(this);
    label_ntp_status->setMinimumWidth(500);
    ui->statusBar->addWidget(label_ntp_status);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(IUpdateData *updateData)
{
    if(updateData->getName()=="NtpTimeResult"){
        NtpTimeResult *result = static_cast<NtpTimeResult *>(updateData);
        // 登录成功
        if(result->result){
            QString ntpTimeStr=result->ntpTime.toString("yyyy-MM-dd hh:mm:ss zzz");
            label_ntp_status->setText("   Ntp时间获取成功: "+ntpTimeStr+" 系统时间已校正");
        }else{
            QString messStr=result->message;
            label_ntp_status->setText(messStr);
        }

    }
}
