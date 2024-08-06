#include "drawmainwindow.h"
#include "ui_drawmainwindow.h"

DrawMainWindow::DrawMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawMainWindow)
{
    ui->setupUi(this);
}

DrawMainWindow::~DrawMainWindow()
{
    delete ui;
}
