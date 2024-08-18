#ifndef DIALOG_HISTORYDATA_H
#define DIALOG_HISTORYDATA_H

#include <QDialog>
#include "devicestateinfo.h"

namespace Ui {
class Dialog_HistoryData;
}

class Dialog_HistoryData : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_HistoryData(QWidget *parent = nullptr);
    explicit Dialog_HistoryData(SensorState sensorState,QWidget *parent = nullptr);

    // 再添加一个参数,这个Dialog不负责获取参数

    ~Dialog_HistoryData();

private:
    SensorState m_SensorState;
    Ui::Dialog_HistoryData *ui;
};

#endif // DIALOG_HISTORYDATA_H
