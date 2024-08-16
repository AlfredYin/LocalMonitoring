#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "IViewComponent.h"
#include "homemediator.h"
#include "logindialog.h"
#include "widget_homepage.h"
#include "mainwindowmediator.h"
#include "mqttclientservice.h"

#include <QMainWindow>
#include <QPointer>

class MainWindowMediator;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public IViewComponent
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update(IUpdateData *updateData);



private:
    Ui::MainWindow *ui;



    MainWindowMediator *mainWindowMediator;

    QWidget *widget_HomePage;

    // 状态栏 QLabel
    QLabel *label_ntp_status;
};

#endif // MAINWINDOW_H
