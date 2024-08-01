#ifndef DEVICEMAINWINDOW_H
#define DEVICEMAINWINDOW_H

#include <QMainWindow>

#include "Interface/IViewComponent.h"

#include "Patterns/Facade.h"
#include "devicemediator.h"
#include "deviceproxy.h"
#include "devicestateinfo.h"
#include "devicestateresult.h"


namespace Ui {
class DeviceMainWindow;
}

class DeviceMediator;

class DeviceMainWindow : public QMainWindow, public IViewComponent
{
    Q_OBJECT

public:
    explicit DeviceMainWindow(QWidget *parent = nullptr);
    ~DeviceMainWindow();

    void update(IUpdateData *updateData);   // 虚函数继承于IviewComponent

    void updateDeivceState(DeviceStateResult *result);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DeviceMainWindow *ui;

    DeviceMediator *deviceMediator;
};

#endif // DEVICEMAINWINDOW_H
