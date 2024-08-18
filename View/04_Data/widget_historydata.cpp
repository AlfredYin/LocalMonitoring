#include "widget_historydata.h"
#include "ui_widget_historydata.h"
#include "sensorhistorydata.h"
#include "sensorparam.h"
#include "sensorhistorydataresult.h"
#include "Facade.h"

Widget_HistoryData::Widget_HistoryData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_HistoryData)
{
    ui->setupUi(this);
    Facade *facade = Facade::getInstance();
    historyDataMediator=(HistoryDataMediator *)facade->retrieveMediator("HistoryDataMediator");
    historyDataMediator->registerViewComponent(this);

    SensorParam *sensorParam=new SensorParam();

    historyDataMediator->getSensorHistoryData(sensorParam);

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(9);

    // 设置水平表头标签
    // Id, GwClientId, GwPubTopic, Humidity, Temperature, HeatIndex, CO2conc, VOCconc, Illum, GwMessDate
    QStringList headers;
    headers << "Id" << "数据设备来源"<<"湿度"<<"温度"<<"热点温度"<<"CO2浓度"<<"VOC浓度"<<"光照强度"<<"获取时间";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

Widget_HistoryData::~Widget_HistoryData()
{
    delete ui;
}

void Widget_HistoryData::update(IUpdateData *updateData)
{
    if (updateData->getName() == "SensorHistoryDataResult")
    {
        SensorHistoryDataResult *result = (SensorHistoryDataResult *)updateData;
        if (result->result)
        {
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(0);
            foreach(const SensorHistoryData& sensorHistoryData,result->sensorHistoryDataList){
                int row = ui->tableWidget->rowCount(); // 获取当前行数
                ui->tableWidget->insertRow(row); // 插入新行

                // 添加内容到新行的各个单元格中
                ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(sensorHistoryData.id)));
                ui->tableWidget->setItem(row, 1, new QTableWidgetItem(sensorHistoryData.devicename));
                ui->tableWidget->setItem(row, 2, new QTableWidgetItem(sensorHistoryData.humidity));
                ui->tableWidget->setItem(row, 3, new QTableWidgetItem(sensorHistoryData.temperature));
                ui->tableWidget->setItem(row, 4, new QTableWidgetItem(sensorHistoryData.heatIndex));
                ui->tableWidget->setItem(row, 5, new QTableWidgetItem(sensorHistoryData.co2conc));
                ui->tableWidget->setItem(row, 6, new QTableWidgetItem(sensorHistoryData.vocconc));
                ui->tableWidget->setItem(row, 7, new QTableWidgetItem(sensorHistoryData.illum));
                ui->tableWidget->setItem(row, 8, new QTableWidgetItem(sensorHistoryData.gwdatadate));
            }
        }else{
            QMessageBox::information(nullptr, "提示", "获取历史数据失败");
        }
    }
}

void Widget_HistoryData::on_pushButton_RefreshHistoryData_clicked()
{
    SensorParam *sensorParam=new SensorParam();

    historyDataMediator->getSensorHistoryData(sensorParam);
}
