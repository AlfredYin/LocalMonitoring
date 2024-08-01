#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Patterns/Facade.h"
#include "loginmediator.h"
#include "loginparam.h"
#include "loginresult.h"
#include "mainwindow.h"
#include "changepwddialog.h"

#include <QDebug>
#include <QMessageBox>
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //
    ui->pushButtonChangePassword->setVisible(false);

    //
    Facade *facade = Facade::getInstance();
    applicationMediator = (ApplicationMediator *)facade->retrieveMediator("ApplicationMediator");
    applicationMediator->registerViewComponent(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(IUpdateData *updateData)
{
    qDebug()<<"void MainWindow::update(IUpdateData *updateData)";
    qDebug()<<"updateData->getName()="<<updateData->getName()<<endl;

    if(updateData->getName()=="LoginResult"){
        LoginResult *loginResult = static_cast<LoginResult *>(updateData);
        if(loginResult->result){
            loginDialog->hide();
            ui->pushButtonLogin->setText("用户："+loginResult->username+" 已登录");
            ui->pushButtonChangePassword->setVisible(true);
    //        this->hide();
            showDeviceMainWindow();
        }else{
            // 计数，超三次关闭程序
            m_Count++;
            if(m_Count>=3){
                QMessageBox::warning(this,"警告","超过三次，登录失败");
                this->close();
            }
        }

    }else if(updateData->getName()=="GeneralResult"){
         QMessageBox::information(nullptr, "GeneralResult", "通用失败提示");
    }
    else{
        int a=0;
    }
}

void MainWindow::showDeviceMainWindow()
{
//    deviceMainWindow=new DeviceMainWindow(this);
//    deviceMainWindow->show();
}

void MainWindow::on_pushButtonLogin_clicked()
{
        loginDialog = new LoginDialog(this);
        loginDialog->show();
}

void MainWindow::on_pushButtonChangePassword_clicked()
{
    changePwdDialog=new ChangePwdDialog(this);
    changePwdDialog->show();
}
