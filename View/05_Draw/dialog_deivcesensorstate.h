#ifndef DIALOG_DEIVCESENSORSTATE_H
#define DIALOG_DEIVCESENSORSTATE_H

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

class DeviceMediator;

namespace Ui {
class Dialog_DeivceSensorState;
}

class Dialog_DeivceSensorState : public QDialog, public IViewComponent
{
    Q_OBJECT

public:
    explicit Dialog_DeivceSensorState(QWidget *parent = nullptr);
    explicit Dialog_DeivceSensorState(DeviceStateInfo deivceStateInfo,QWidget *parent = nullptr);
    ~Dialog_DeivceSensorState();

    void update(IUpdateData *updateData);   // 虚函数继承于IviewComponent

private:
    Ui::Dialog_DeivceSensorState *ui;

    DeviceMediator *deviceMediator;

    DeviceStateInfo m_DeivceStateInfo;      // 存储包括网关设备和传感器设备的所有信息

    SensorStateResult m_SensorStateResult;      // 传感器信息的结果

    QGraphicsScene *scene;
};

#endif // DIALOG_DEIVCESENSORSTATE_H
