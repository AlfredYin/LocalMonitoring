#ifndef DIALOG_DATABASECONNECTSTATE_H
#define DIALOG_DATABASECONNECTSTATE_H

#include "devicemediator.h"
#include "homemediator.h"

#include <QDialog>

namespace Ui {
class Dialog_DataBaseConnectState;
}

class Dialog_DataBaseConnectState : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DataBaseConnectState(QWidget *parent = nullptr);
    ~Dialog_DataBaseConnectState();

private:
    HomeMediator *homeMediator;
    Ui::Dialog_DataBaseConnectState *ui;
};

#endif // DIALOG_DATABASECONNECTSTATE_H
