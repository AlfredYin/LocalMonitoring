#include "dialog_sensorrealtimedata.h"
#include "ui_dialog_sensorrealtimedata.h"

Dialog_SensorRealTimeData::Dialog_SensorRealTimeData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_SensorRealTimeData)
{
    ui->setupUi(this);
}

Dialog_SensorRealTimeData::~Dialog_SensorRealTimeData()
{
    delete ui;
}
