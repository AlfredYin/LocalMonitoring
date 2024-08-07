#include "dialog_setwidth.h"
#include "ui_dialog_setwidth.h"

Dialog_SetWidth::Dialog_SetWidth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SetWidth)
{
    ui->setupUi(this);
}

Dialog_SetWidth::Dialog_SetWidth(int size, QWidget *parent) :
    QDialog(parent),m_Size(size),ui(new Ui::Dialog_SetWidth)
{
    ui->setupUi(this);
    ui->spinBox_Width->setRange(0,100);
    ui->spinBox_Width->setValue(m_Size);
}

int Dialog_SetWidth::getWidth()
{
    return ui->spinBox_Width->value();
}

Dialog_SetWidth::~Dialog_SetWidth()
{
    delete ui;
}
