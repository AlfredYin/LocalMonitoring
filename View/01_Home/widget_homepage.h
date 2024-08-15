#ifndef WIDGET_HOMEPAGE_H
#define WIDGET_HOMEPAGE_H

#include "IViewComponent.h"
#include "homemediator.h"
#include "devicemediator.h"
#include "logindialog.h"
#include "drawmainwindow.h"
#include "devicerectitem.h"
#include "refreshtextitem.h"
#include "dialog_databaseconnectstate.h"

#include <QMenu>
#include <QWidget>
#include <QLabel>

namespace Ui {
class Widget_HomePage;
}

class Widget_HomePage : public QWidget, public IViewComponent
{
    Q_OBJECT

public:
    explicit Widget_HomePage(QWidget *parent = nullptr);
    ~Widget_HomePage();

    void update(IUpdateData *updateData);

    void roadScene();

    void loadDeviceState(DeviceStateListResult *result);

private slots:

    void on_mouseRightClicked(QPoint point);

    void on_pushButtonLogin_clicked();

    void on_pushButtonChangePassword_clicked();

    void updateTimeLabel();
    void on_pushButton_Draw_clicked();

    void on_pushButton_DbState_clicked();

private:


    HomeMediator *homeMediator;
//    DeviceMediator *deviceMediator;

    // 画图，修改主页设备连线图
    // 主页默认展示视图
    AlfredGraphicsScene *scene=nullptr;

    // 刷新按钮
    RefreshTextItem* refreshItem=nullptr;

    DrawMainWindow *drawMainWindow=nullptr;

    LoginDialog *loginDialog=nullptr;

    Dialog_DataBaseConnectState *dataBaseConnectState_Dialog=nullptr;
//    QPointer<QDialog> loginDialog;
//    QPointer<LoginDialog> loginDialog;
    QDialog *changePwdDialog=nullptr;

    int m_Count=0;

    QTimer *time_Timer;

    Ui::Widget_HomePage *ui;
};

#endif // WIDGET_HOMEPAGE_H
