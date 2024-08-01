#include "changepwddialog.h"
#include "ui_changepwddialog.h"
#include "loginparam.h"
#include "loginresult.h"
#include "Patterns/Facade.h"
#include "loginmediator.h"

#include <QMessageBox>
#include <QDebug>

ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);
    // 注册相应的Facade Mediator
    Facade *facade = Facade::getInstance();
    loginMediator = (LoginMediator *)facade->retrieveMediator("LoginMediator");
    loginMediator->registerViewComponent(this);

}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}

void ChangePwdDialog::update(IUpdateData *updateData)
{
    qDebug()<<"void ChangePwdDialog::update(IUpdateData *updateData)";

    if (updateData->getName() == "LoginResult")
    {
        LoginResult *loginResult = (LoginResult *)updateData;

        if (loginResult->result)
        {
            QMessageBox::information(nullptr, "", "修改成功");
            qDebug() << "Login Success";
        }
        else
        {
            QMessageBox::information(nullptr, "", "修改失败:"+loginResult->message);
            qDebug() << "Login Fail";
        }
    }

}

void ChangePwdDialog::on_loginButton_clicked()
{
    QString username=ui->lineEdit_UserName->text();
    // 前端判断密码是否相同
    QString pwd=ui->lineEdit_PassWord->text();
    QString pwdConfired=ui->lineEdit_PassWordConfirm->text();

    if(pwd!=pwdConfired){
        QMessageBox::information(nullptr, "", "两次输入密码不同，请修改重新输入");
        qDebug() << "Password Not Confired !";
        return ;
    }

    // 通知Md ， 判断逻辑是 与旧密码相同的话 向用户提示，数据不修改。
    // 否则修改旧密码，返回修改成功。
    LoginParam *loginInfo=new LoginParam();
    loginInfo->name=username;
    loginInfo->password=pwd;

    loginMediator->changePwd(loginInfo);
}
