#ifndef DIALOG_CONTROLDEVICESTATE_H
#define DIALOG_CONTROLDEVICESTATE_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColorDialog>
#include <QFontDialog>
#include <QPointF>
#include <QDialog>

#include "Interface/IViewComponent.h"

#include "Patterns/Facade.h"
#include "devicemediator.h"
#include "deviceproxy.h"
#include "devicestateresult.h"

#include "devicestateinfo.h"
#include "sensorstateresult.h"
#include "sensorrectitem.h"
#include "controldevicerectitem.h"
#include "alfredgraphicsview.h"
#include "dialog_sendcontroldeviceorder.h"

namespace Ui {
class Dialog_ControlDeviceState;
}

class Dialog_ControlDeviceState : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ControlDeviceState(QWidget *parent = nullptr);
    explicit Dialog_ControlDeviceState(DeviceStateInfo deivceStateInfo,QWidget *parent = nullptr);

    ~Dialog_ControlDeviceState();

private:
    Ui::Dialog_ControlDeviceState *ui;

    DeviceMediator *deviceMediator;

    DeviceStateInfo m_DeivceStateInfo;      // 存储包括网关设备和传感器设备的所有信息

    SensorStateResult m_SensorStateResult;      // 传感器信息的结果

    QGraphicsScene *scene;
};

#endif // DIALOG_CONTROLDEVICESTATE_H
