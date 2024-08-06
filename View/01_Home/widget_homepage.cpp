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
    }else if(updateData->getName()=="GeneralResult"){
         QMessageBox::information(nullptr, "GeneralResult", "通用失败提示");
    }
    else{
        int a=0;
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
//    DrawMainWindow drawMainWindow;
//    drawMainWindow.show();
}
