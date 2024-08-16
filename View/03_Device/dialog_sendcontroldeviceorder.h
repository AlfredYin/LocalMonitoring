#ifndef DIALOG_SENDCONTROLDEVICEORDER_H
#define DIALOG_SENDCONTROLDEVICEORDER_H

#include <QDialog>
#include "IViewComponent.h"

#include "Facade.h"
#include "devicemediator.h"
#include "deviceproxy.h"
#include "devicestateresult.h"
#include "devicestateinfo.h"

namespace Ui {
class Dialog_SendControlDeviceOrder;
}

class Dialog_SendControlDeviceOrder : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SendControlDeviceOrder(QWidget *parent = nullptr);

    explicit Dialog_SendControlDeviceOrder(ControlDeviceState controlDeviceState,QWidget *parent = nullptr);

    QString getSendControlCommand();

    ~Dialog_SendControlDeviceOrder();

private:
    ControlDeviceState m_ControlDeviceState;

    DeviceMediator *deviceMediator;

    Ui::Dialog_SendControlDeviceOrder *ui;
};

#endif // DIALOG_SENDCONTROLDEVICEORDER_H
