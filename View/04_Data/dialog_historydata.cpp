#include "dialog_historydata.h"
#include "ui_dialog_historydata.h"

Dialog_HistoryData::Dialog_HistoryData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_HistoryData)
{
    ui->setupUi(this);
}

Dialog_HistoryData::Dialog_HistoryData(SensorState sensorState, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_HistoryData)
{
    ui->setupUi(this);
    m_SensorState=sensorState;
    setWindowTitle("传感器"+sensorState.sensorname+"历史数据如下表:");

    // 假设表格有三列：时间、数据值、状态
    ui->tableWidget->setColumnCount(3);
    QStringList headers;
    headers << "时间" << "数据值" << "状态";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // 初始化几条数据
    QList<QList<QString>> data = {
        {"2023-08-01 12:00:00", "23.5", "正常"},
        {"2023-08-02 13:30:00", "24.1", "正常"},
        {"2023-08-03 14:15:00", "22.8", "异常"}
    };

    // 设置表格行数
    ui->tableWidget->setRowCount(data.size());

    // 填充数据
    for (int row = 0; row < data.size(); ++row) {
        for (int column = 0; column < data[row].size(); ++column) {
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(data[row][column]));
        }
    }
}

Dialog_HistoryData::~Dialog_HistoryData()
{
    delete ui;
}
