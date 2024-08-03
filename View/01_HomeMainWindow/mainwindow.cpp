#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Patterns/Facade.h"
#include "loginmediator.h"
#include "loginparam.h"
#include "loginresult.h"
#include "mainwindow.h"
#include "changepwddialog.h"

#include <QTabWidget>
#include <QDebug>
#include <QMessageBox>
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget_HomePage=new Widget_HomePage(this);
    ui->tabWidget->addTab(widget_HomePage,"主页");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(IUpdateData *updateData)
{

}
