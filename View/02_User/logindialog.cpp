#include "logindialog.h"
#include "ui_logindialog.h"
#include "Facade.h"
#include "loginparam.h"
#include "loginresult.h"

#include <QDebug>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    // Facade 是 PureMVC 中的中央控制点。它提供了一个简化的接口，用于访问系统中的各种功能和服务。
    // 它负责创建和管理 Model、View 和 Controller 的实例，并协调它们之间的操作。
    // 这里获取了一个名为 Facade 的单例实例。Facade 类的设计模式可能是单例模式。
    Facade *facade = Facade::getInstance();

    //
    // 从 Facade 实例中检索名为 "UserMediator" 的中介（Mediator）实例，并将其强制转换为 UserMediator 类型。
    // 这个中介对象用于协调对话框与其他系统组件的交互。
    userMediator = (UserMediator *)facade->retrieveMediator("UserMediator");
    // 将当前对话框 (this) 注册到 userMediator 中。这样 userMediator 就可以与对话框进行交互，可能用于更新用户界面或处理用户输入等操作。
    userMediator->registerViewComponent(this);

    // Controller 负责处理应用程序的控制逻辑。它通常由 Command 组成。
    // Command：Command 是封装应用程序行为的对象。
    // 当某个事件发生时，Command 被触发来执行相应的操作。Command 可以创建、更新或删除数据，改变应用程序的状态等。

    ui->lineEdit_PassWord->setEchoMode(QLineEdit::Password);  // 设置密码模式
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::update(IUpdateData *updateData)
{
    if (updateData->getName() == "LoginResult")
       {
           LoginResult *loginResult = (LoginResult *)updateData;

           if (loginResult->result)
           {
//               QMessageBox::information(nullptr, "提示", "登录成功");
               qDebug() << "Login Success";
           }
           else
           {
               QMessageBox::information(nullptr, "提示", "账号密码错误");
               qDebug() << "Login Fail";
               // 计数，超三次关闭程序
               m_Count++;
               if(m_Count>=3){
                   this->close();
               }
           }
       }
}

void LoginDialog::on_loginButton_clicked()
{
    if(ui->lineEdit_UserName->text().isEmpty() || ui->lineEdit_PassWord->text().isEmpty()){
        QMessageBox::information(nullptr, "提示", "请输入用户名密码");
        return;
    }

    LoginParam *loginParam = new LoginParam();

    loginParam->name = ui->lineEdit_UserName->text().trimmed();
    loginParam->password = ui->lineEdit_PassWord->text().trimmed();

    userMediator->doLogin(loginParam);
}
