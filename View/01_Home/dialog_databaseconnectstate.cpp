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

}

Dialog_DataBaseConnectState::~Dialog_DataBaseConnectState()
{
    delete ui;
}
