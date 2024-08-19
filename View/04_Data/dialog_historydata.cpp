#include "dialog_historydata.h"
#include "ui_dialog_historydata.h"

Dialog_HistoryData::Dialog_HistoryData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_HistoryData)
{
    ui->setupUi(this);
}

Dialog_HistoryData::Dialog_HistoryData(QList<SensorHistoryData> sensorHistoryData,SensorState sensorState, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_HistoryData)
{
    ui->setupUi(this);
    m_SensorState=sensorState;

    setWindowTitle("传感器"+sensorState.sensorname+"历史数据如下表:");

    ui->tableWidget->setRowCount(0);
    QStringList headers;

    if(sensorState.sensor=="BH1750"){
        headers << "Id" << "数据设备来源"<<"光照强度"<<"获取时间";
        ui->tableWidget->setColumnCount(headers.count());
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        foreach(const SensorHistoryData& sensorHistoryData,sensorHistoryData){
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sensorHistoryData.id)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(sensorHistoryData.devicename));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(sensorHistoryData.illum));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(sensorHistoryData.gwdatadate));
        }

    }else if(sensorState.sensor=="SGP30"){
        headers << "Id" << "数据设备来源"<<"CO2浓度"<<"VOC浓度"<<"获取时间";
        ui->tableWidget->setColumnCount(headers.count());
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        foreach(const SensorHistoryData& sensorHistoryData,sensorHistoryData){
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sensorHistoryData.id)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(sensorHistoryData.devicename));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(sensorHistoryData.co2conc));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(sensorHistoryData.vocconc));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(sensorHistoryData.gwdatadate));
        }
    }else if(sensorState.sensor=="AHT10"){
        headers << "Id" << "数据设备来源"<<"湿度"<<"温度"<<"热点温度"<<"获取时间";
        ui->tableWidget->setColumnCount(headers.count());
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        foreach(const SensorHistoryData& sensorHistoryData,sensorHistoryData){
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sensorHistoryData.id)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(sensorHistoryData.devicename));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(sensorHistoryData.humidity));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(sensorHistoryData.temperature));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(sensorHistoryData.heatIndex));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(sensorHistoryData.gwdatadate));
        }
    }

    ui->tableWidget->resizeColumnsToContents();

    // 填充数据
//    for (int row = 0; row < data.size(); ++row) {
//        for (int column = 0; column < data[row].size(); ++column) {
//            ui->tableWidget->setItem(row, column, new QTableWidgetItem(data[row][column]));
//        }
//    }
}

Dialog_HistoryData::~Dialog_HistoryData()
{
    delete ui;
}
