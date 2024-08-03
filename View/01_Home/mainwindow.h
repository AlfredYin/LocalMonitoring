#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Interface/IViewComponent.h"
#include "homemediator.h"
#include "logindialog.h"
#include "widget_homepage.h"

#include <QMainWindow>
#include <QPointer>

namespace Ui {
class MainWindow;
}

class HomeMediator;

class MainWindow : public QMainWindow, public IViewComponent
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void update(IUpdateData *updateData);



private:
    Ui::MainWindow *ui;
    HomeMediator *homeMediator;

    QWidget *widget_HomePage;
};

#endif // MAINWINDOW_H
