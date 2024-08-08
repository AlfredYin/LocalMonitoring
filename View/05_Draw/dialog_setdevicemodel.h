#ifndef DIALOG_SETDEVICEMODEL_H
#define DIALOG_SETDEVICEMODEL_H

#include "devicestateinfo.h"

#include <QDialog>

namespace Ui {
class Dialog_SetDeviceModel;
}

class Dialog_SetDeviceModel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_SetDeviceModel(QWidget *parent = nullptr);
    ~Dialog_SetDeviceModel();

    DeviceStateInfo getDeivceStateInfo();

private:
    Ui::Dialog_SetDeviceModel *ui;

    DeviceStateInfo m_DeiveStateInfo;
};

#endif // DIALOG_SETDEVICEMODEL_H
