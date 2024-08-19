#include "dialog_databaseconnectstate.h"
#include "ui_dialog_databaseconnectstate.h"

#include "Facade.h"

Dialog_DataBaseConnectState::Dialog_DataBaseConnectState(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_DataBaseConnectState)
{
    ui->setupUi(this);
    Facade *facade = Facade::getInstance();
    homeMediator = (HomeMediator *)facade->retrieveMediator("HomeMediator");

    ui->label_DbType->setText(DataBaseStateHelper::getConnectingDBType());
    ui->label_DbState->setText(DataBaseStateHelper::isConnectedDb()?"已连接":"连接已断开");
}

Dialog_DataBaseConnectState::~Dialog_DataBaseConnectState()
{
    delete ui;
}
