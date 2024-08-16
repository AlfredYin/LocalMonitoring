#include <QApplication>
#include "ApplicationFacade.h"
#include "logindialog.h"

#include "mysqldbmanager.h"
#include "sqlserverdbmanager.h"

#include "readconfigjsonhelper.h"
#include "mainwindow.h"
#include "widget_homepage.h"
#include "drawmainwindow.h"
#include "alfredgraphicsscene.h"

#include "mqttclientservice.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // 注册
    ApplicationFacade *af = new ApplicationFacade();
    af->startUp();

//    MainWindow mainWindow;
//    mainWindow.show();

//    DrawMainWindow drawMainWindow;
//    drawMainWindow.show();

//    AlfredGraphicsScene scene;

//    QGraphicsView view(&scene);
//    view.setRenderHint(QPainter::Antialiasing);
//    view.show();

    MqttClientService *mqttClientService=new MqttClientService();

    return app.exec();
}
