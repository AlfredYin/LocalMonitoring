#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Interface/IViewComponent.h"
#include "ApplicationMediator.h"

#include <QMainWindow>

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

    void showDeviceMainWindow();

private slots:
    void on_pushButtonLogin_clicked();

    void on_pushButtonChangePassword_clicked();

private:
    Ui::MainWindow *ui;
    ApplicationMediator *applicationMediator;

    QDialog *loginDialog;
    QDialog *changePwdDialog;

    QMainWindow *deviceMainWindow;

    int m_Count=0;

};

#endif // MAINWINDOW_H
