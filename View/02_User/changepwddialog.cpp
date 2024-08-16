#include "changepwddialog.h"
#include "ui_changepwddialog.h"
#include "loginparam.h"
#include "changepwdresult.h"
#include "Facade.h"
#include "usermediator.h"

#include <QMessageBox>
#include <QDebug>

ChangePwdDialog::ChangePwdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePwdDialog)
{
    ui->setupUi(this);
    // 注册相应的Facade Mediator
    Facade *facade = Facade::getInstance();
    userMediator = (UserMediator *)facade->retrieveMediator("UserMediator");
    userMediator->registerViewComponent(this);

    // 获取视图的随带的数据
    userInfo=userMediator->getUserInfo();
    ui->lineEdit_UserName->setText(userInfo.username);
}

ChangePwdDialog::~ChangePwdDialog()
{
    delete ui;
}

void ChangePwdDialog::update(IUpdateData *updateData)
{
    qDebug()<<"void ChangePwdDialog::update(IUpdateData *updateData)";

//    if (updateData->getName() == "LoginResult_ChangePwd")
    if (updateData->getName() == "ChangePwdResult")
    {
        ChangePwdResult *changePwdResult = (ChangePwdResult *)updateData;

        if (changePwdResult->result)
        {
            QMessageBox::information(nullptr, "提示", "修改成功");
            qDebug() << "ChangePwd Success";
        }
        else
        {
            QMessageBox::information(nullptr, "提示", "修改失败:"+changePwdResult->message);
            qDebug() << "ChangePwd Fail";
        }
    }

}

void ChangePwdDialog::on_loginButton_clicked()
{

    if(ui->lineEdit_UserName->text().isEmpty() || ui->lineEdit_PassWord->text().isEmpty()
            || ui->lineEdit_PassWordConfirm->text().isEmpty()){
        QMessageBox::information(nullptr, "提示", "请输入用户名密码");
        return;
    }

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

    userMediator->changePwd(loginInfo);
}
