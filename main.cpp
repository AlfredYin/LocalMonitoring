#include <QApplication>
#include "ApplicationFacade.h"
#include "LoginForm.h"
#include "mysqldbmanager.h"
#include "mainwindow.h"
#include "devicemainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // 注册
    ApplicationFacade *af = new ApplicationFacade();
    af->startUp();

    // 数据库连接
    MySqlDBManager& dbManager = MySqlDBManager::instance();

    if (!dbManager.connect("47.98.243.38", "AlfredDb", "root", "Yin1719934825")) {

        qDebug() << "数据库连接失败" <<endl;
        return -1;
    }

    MainWindow mainWindow;
    mainWindow.show();

//    DeviceMainWindow *mainWindow = new DeviceMainWindow();
//    mainWindow->show();

    return app.exec();
}
