#ifndef DIALOG_SENSORREALTIMEDATA_H
#define DIALOG_SENSORREALTIMEDATA_H

#include <QDialog>

namespace Ui {
class Dialog_SensorRealTimeData;
}

class Dialog_SensorRealTimeData : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SensorRealTimeData(QWidget *parent = nullptr);
    ~Dialog_SensorRealTimeData();

private:
    Ui::Dialog_SensorRealTimeData *ui;
};

#endif // DIALOG_SENSORREALTIMEDATA_H
