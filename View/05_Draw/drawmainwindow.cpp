#include "drawmainwindow.h"
#include "ui_drawmainwindow.h"
#include "devicerectitem.h"
#include "devicestateinfo.h"
#include "dialog_setdevicemodel.h"
#include "scenefilehelper.h"

#include <QTime>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>
#include <QFileInfo>

DrawMainWindow::DrawMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DrawMainWindow)
{
    ui->setupUi(this);
    label_ItemInfo=new QLabel("ItemInfo:");
    label_ItemInfo->setMinimumWidth(150);
//    scene=new QGraphicsScene(-300,-100,600,200);
    scene=new AlfredGraphicsScene(-300,-100,600,200,this);
    ui->graphicsView->setScene(scene);

    // 设置视图属性
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);     禁止全选
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);


    ui->statusBar->addWidget(label_ItemInfo);

    connect(ui->graphicsView,SIGNAL(keyPress(QKeyEvent *)),this,SLOT(on_keyPress(QKeyEvent *)));
    connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),this,SLOT(on_mouseClicked(QPoint)));
    // 左键呼出菜单
    connect(ui->graphicsView,SIGNAL(mouseRightClicked(QPoint)),this,SLOT(on_mouseRightClicked(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),this,SLOT(on_mouseClicked(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseDoubleClick(QPoint)),this,SLOT(on_mouseDoubleClick(QPoint)));

    qsrand(QTime::currentTime().msec());
}

DrawMainWindow::~DrawMainWindow()
{
    delete ui;
}

#include <QKeyEvent>
void DrawMainWindow::on_keyPress(QKeyEvent *event)
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        return;
    }

    switch(event->key()){
        case Qt::Key_Delete :{
            for(int i=0;i<cnt;i++){
                QGraphicsItem *item=scene->selectedItems().at(0);
                scene->removeItem(item);
            }
            break;
        }
        case Qt::Key_Left :{
            for(int i=0;i<cnt;i++){
                QGraphicsItem *item=scene->selectedItems().at(0);
                item->setX(item->x()-1);
            }
            break;
        }
        case Qt::Key_Right :{
            for(int i=0;i<cnt;i++){
                QGraphicsItem *item=scene->selectedItems().at(0);
                item->setX(item->x()+1);
            }
            break;
        }
        case Qt::Key_Up:{
            for(int i=0;i<cnt;i++){
                QGraphicsItem *item=scene->selectedItems().at(0);
                item->setY(item->y()-1);
            }
            break;
        }
        case Qt::Key_Down:{
            for(int i=0;i<cnt;i++){
                QGraphicsItem *item=scene->selectedItems().at(0);
                item->setY(item->y()+1);
            }
            break;
        }
    }
}

void DrawMainWindow::on_mouseDoubleClick(QPoint point)
{
    qDebug()<<"void DrawMainWindow::on_mouseDoubleClick(QPoint point)";

    QPointF pointScene=ui->graphicsView->mapToScene(point);
    QGraphicsItem *item=nullptr;
    item=scene->itemAt(pointScene,ui->graphicsView->transform());

    qDebug()<<pointScene.x()<<pointScene.y();

    if(item==nullptr){
        return;
    }
    switch (item->type()) {
        // 矩形等只需要设置填充颜色
        case QGraphicsRectItem::Type:{
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
            break;
        }

        case QGraphicsEllipseItem::Type:{
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
            break;
        }

        case QGraphicsPolygonItem::Type:{
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
            break;
        }

        case QGraphicsTextItem::Type:{
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);
            QColor color=theItem->defaultTextColor();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setDefaultTextColor(color);
            }
            break;
        }

        // 直线和折线需要设置Pen的颜色和宽度
        case 10001:{
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);

            QPen thePen=theItem->pen();

            QColor color=thePen.color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                thePen.setColor(color);
            }
//            Dialog_SetWidth *dialog= new Dialog_SetWidth(thePen.width(),this);
//            dialog->setToolTip("修改直线宽度");
//            if (dialog->exec() == QDialog::Accepted) {
//                int new_Width = dialog->getWidth();
//                if(new_Width!=thePen.width()){
//                    thePen.setWidth(new_Width);
//                }
//            }
//            theItem->setPen(thePen);
            break;
        }
    }
}

void DrawMainWindow::on_mouseClicked(QPoint point)
{
//    qDebug()<<"void DrawMainWindow::on_mouseClicked(QPoint point)";
    QPointF pointScene=ui->graphicsView->mapToScene(point);
    QGraphicsItem *item=nullptr;
    item=scene->itemAt(pointScene,ui->graphicsView->transform());
    if(item!=nullptr){
        label_ItemInfo->setText("ItemInfo:"+item->data(ItemId).toString()+
                                ","+item->data(ItemDescription).toString()+
                                "ScenePos:"+QString::number(pointScene.x())+ "," +QString::number(pointScene.y()));
    }
}

#include <QInputDialog>
void DrawMainWindow::on_mouseRightClicked(QPoint point)
{
    // 右键，修改颜色，修改内容
    QPointF pointScene=ui->graphicsView->mapToScene(point);
    QGraphicsItem *item=nullptr;
    item=scene->itemAt(pointScene,ui->graphicsView->transform());

    if (!item){
        return;
    }

    // 根据不同的选中Item，给出不同右键菜单
    QMenu *cmenu = new QMenu();

    // 修改颜色
    QAction *actionModifyColor=new QAction("修改颜色");
    connect(actionModifyColor, &QAction::triggered, [this, item]() {
        if(item->type()==QGraphicsRectItem::Type){              // 矩形
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
        }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
        }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            QColor color=theItem->brush().color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                theItem->setBrush(QBrush(color));
            }
        }else if(item->type()==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);
            QColor color = QColorDialog::getColor(theItem->defaultTextColor(), nullptr, "选择颜色");
            if (color.isValid()){
                theItem->setDefaultTextColor(color);
            }
        }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);
            QPen thePen=theItem->pen();

            QColor color=thePen.color();
            color=QColorDialog::getColor(color,nullptr,"选择颜色");
            if(color.isValid()){
                thePen.setColor(color);
            }
            theItem->setPen(thePen);
        }/*else if(item->type()==DeviceRectItem::Type){     // 设备模型
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);

        }*/
    });

    // 修改内容
    QAction *actionModifyContent = new QAction("修改内容");
    connect(actionModifyContent, &QAction::triggered, [this, item]() {
        if(item->type()==QGraphicsRectItem::Type){              // 矩形
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

        }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);

        }else if(item->type()==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);
            QString str=QInputDialog::getText(this,"请输入文本内容","请输入：");
            if(!str.isEmpty()){
                theItem->setPlainText(str);
            }
        }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);
            QPen thePen=theItem->pen();

            Dialog_SetWidth *dialog= new Dialog_SetWidth(thePen.width(),this);
            dialog->setToolTip("修改直线宽度");
            if (dialog->exec() == QDialog::Accepted) {
                int new_Width = dialog->getWidth();
                if(new_Width!=thePen.width()){
                    thePen.setWidth(new_Width);
                }
            }
            theItem->setPen(thePen);

        }else if(item->type()==DeviceRectItem::Type){     // 设备模型
            DeviceRectItem *theItem;
            theItem=qgraphicsitem_cast<DeviceRectItem *>(item);

            Dialog_SetDeviceModel *dialog=new Dialog_SetDeviceModel(this);
//            DeviceStateInfo deviceStateInfo=
            dialog->setToolTip("初始化");
            if (dialog->exec() == QDialog::Accepted) {
                DeviceStateInfo deviceStateInfo=dialog->getDeivceStateInfo();
                theItem->setDeviceStateInfo(deviceStateInfo);
            }
        }
    });

    // 修改线段宽度
    QAction *actionModifyWidth = new QAction("修改宽度");

    // 修改字体
    QAction *actionModifyFont = new QAction("修改字体");
    connect(actionModifyFont, &QAction::triggered, [this, item]() {
        if(item->type()==QGraphicsRectItem::Type){              // 矩形
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

        }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

        }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);

        }else if(item->type()==QGraphicsTextItem::Type){     // 文字
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);

            bool flag;
            QFont new_Font=QFontDialog::getFont(&flag,theItem->font(),this,"请选择文字字体");
            if (flag) {
                theItem->setFont(new_Font);
            }
        }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
            SingleLineItem *theItem;
            theItem=qgraphicsitem_cast<SingleLineItem *>(item);

        }else if(item->type()==DeviceRectItem::Type){     // 设备模型
            DeviceRectItem *theItem;
            theItem=qgraphicsitem_cast<DeviceRectItem *>(item);
        }
    });

    if(item->type()==QGraphicsRectItem::Type){              // 矩形
        QGraphicsRectItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
        cmenu->addAction(actionModifyColor);
    }else if(item->type()==QGraphicsEllipseItem::Type){     // 圆形，椭圆
        QGraphicsEllipseItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
        cmenu->addAction(actionModifyColor);
    }else if(item->type()==QGraphicsPolygonItem::Type){     // 多边形
        QGraphicsPolygonItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        cmenu->addAction(actionModifyColor);
    }else if(item->type()==QGraphicsTextItem::Type){     // 文字
        QGraphicsPolygonItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        // 设置颜色和字号
        cmenu->addAction(actionModifyColor);
        cmenu->addAction(actionModifyContent);
        // 字体
        cmenu->addAction(actionModifyFont);
    }else if(item->type()==SingleLineItem::Type){     // 直线，折线，曲线
        QGraphicsPolygonItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        // 设置颜色和宽度
        cmenu->addAction(actionModifyColor);
        cmenu->addAction(actionModifyWidth);
    }else if(item->type()==DeviceRectItem::Type){     // 设备模型
        QGraphicsPolygonItem *theItem;
        theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
        cmenu->addAction(actionModifyContent);
    }
        // 只能设置填充颜色


    cmenu->exec(QCursor::pos());

    // 修改颜色
//    QAction *actionModifyColor = cmenu->addAction("Modify Color");
    // 修改内容
    //    QAction *actionModifyAction = cmenu->addAction("Modify Content");
    // 修改线段宽度


//    // 连接菜单项的信号到槽函数，并传递item指针
//    connect(actionModifyColor, &QAction::triggered, [this, item]() {
//        switch (item->type()) {
//            // 矩形等只需要设置填充颜色
//            case QGraphicsRectItem::Type:{
//                QGraphicsRectItem *theItem;
//                theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
//                QColor color=theItem->brush().color();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    theItem->setBrush(QBrush(color));
//                }
//                break;
//            }

//            case QGraphicsEllipseItem::Type:{
//                QGraphicsEllipseItem *theItem;
//                theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
//                QColor color=theItem->brush().color();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    theItem->setBrush(QBrush(color));
//                }
//                break;
//            }

//            case QGraphicsPolygonItem::Type:{
//                QGraphicsPolygonItem *theItem;
//                theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
//                QColor color=theItem->brush().color();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    theItem->setBrush(QBrush(color));
//                }
//                break;
//            }

//            // 文字也可设置内容，右键
//            case QGraphicsTextItem::Type:{
//                QGraphicsTextItem *theItem;
//                theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);
//                QColor color=theItem->defaultTextColor();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    theItem->setDefaultTextColor(color);
//                }
//                break;
//            }

//            // 直线和折线需要设置Pen的颜色和宽度
//            case 10001:{
//                SingleLineItem *theItem;
//                theItem=qgraphicsitem_cast<SingleLineItem *>(item);

//                QPen thePen=theItem->pen();

//                QColor color=thePen.color();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    thePen.setColor(color);
//                }
////                Dialog_SetWidth *dialog= new Dialog_SetWidth(thePen.width(),this);
////                dialog->setToolTip("修改直线宽度");
////                if (dialog->exec() == QDialog::Accepted) {
////                    int new_Width = dialog->getWidth();
////                    if(new_Width!=thePen.width()){
////                        thePen.setWidth(new_Width);
////                    }
////                }
//                theItem->setPen(thePen);
//                break;
//            }

//            // 设备001 配置
//            case 10010:{
//                SingleLineItem *theItem;
//                theItem=qgraphicsitem_cast<SingleLineItem *>(item);

//                QPen thePen=theItem->pen();

//                QColor color=thePen.color();
//                color=QColorDialog::getColor(color,nullptr,"选择颜色");
//                if(color.isValid()){
//                    thePen.setColor(color);
//                }

//                Dialog_SetWidth *dialog= new Dialog_SetWidth(thePen.width(),this);
//                dialog->setToolTip("修改直线宽度");
//                if (dialog->exec() == QDialog::Accepted) {
//                    int new_Width = dialog->getWidth();
//                    if(new_Width!=thePen.width()){
//                        thePen.setWidth(new_Width);
//                    }
//                }
//                theItem->setPen(thePen);
//                break;
//            }
//        }
//    });
//    connect(actionModifyContent, &QAction::triggered, [this, item]() {
////        on_menu_click(2, item);

//        Dialog_SetDeviceModel *dialog= new Dialog_SetDeviceModel(this);
//        dialog->setToolTip("修改直线宽度");
//        if (dialog->exec() == QDialog::Accepted) {

//            DeviceStateInfo deviceStateInfo=dialog->getDeivceStateInfo();
//            item
//        }

//    });

}

void DrawMainWindow::on_action_Rectangle_triggered()
{
    QGraphicsRectItem *item=new QGraphicsRectItem(-50,-30,100,60);
    item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                   QGraphicsRectItem::ItemIsSelectable |
                   QGraphicsRectItem::ItemIsMovable);
    item->setBrush(QBrush(m_Color));
    item->setPos(-100+qrand()%200,-60+qrand()%120);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDescription,"矩形");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void DrawMainWindow::on_action_AddDeviceModel_triggered()
{
    DeviceRectItem *item=new DeviceRectItem(-50,-30,80,40);
    item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                   QGraphicsRectItem::ItemIsSelectable |
                   QGraphicsRectItem::ItemIsMovable);
    item->setBrush(QBrush(m_Color));

    DeviceStateInfo deviceStateInfo;

    deviceStateInfo.devicename="abcd";
    deviceStateInfo.connectingflag=1;

    item->setDeviceStateInfo(deviceStateInfo);

    item->setPos(-100+qrand()%200,-60+qrand()%120);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDescription,"自定义设备模型");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void DrawMainWindow::on_action_Ellipse_triggered()
{
    auto *item=new QGraphicsEllipseItem(-50,-50,100,60);
    item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                   QGraphicsRectItem::ItemIsSelectable |
                   QGraphicsRectItem::ItemIsMovable);
    item->setBrush(QBrush(m_Color));
    item->setPos(-100+qrand()%200,-60+qrand()%120);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDescription,"椭圆");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void DrawMainWindow::on_action_Circle_triggered()
{
    auto *item=new QGraphicsEllipseItem(-50,-50,100,100);
    item->setFlags(QGraphicsRectItem::ItemIsFocusable |
                   QGraphicsRectItem::ItemIsSelectable |
                   QGraphicsRectItem::ItemIsMovable);
    item->setBrush(QBrush(m_Color));
    item->setPos(-100+qrand()%200,-60+qrand()%120);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDescription,"椭圆");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void DrawMainWindow::on_action_Triangle_triggered()
{
    QVector<QPointF> points;
    points<<QPointF(50,50)<<QPointF(-50,50)<<QPointF(0,-50);

    auto *triangle = new QGraphicsPolygonItem(QPolygonF(points));
    triangle->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    triangle->setBrush(QBrush(m_Color));

    triangle->setPos(-100+qrand()%200,-60+qrand()%120);

    static int seqNum = 0;
    triangle->setData(ItemId, ++seqNum);
    triangle->setData(ItemDescription, "三角形");
    scene->addItem(triangle);
    scene->clearSelection();
    triangle->setSelected(true);
}

void DrawMainWindow::on_action_SingleLine_triggered()
{


    // 弃用,改为使用鼠标拖拽
//    auto *item=new QGraphicsLineItem(-100,0,100,0);
//    item->setFlags(QGraphicsRectItem::ItemIsFocusable |
//                   QGraphicsRectItem::ItemIsSelectable |
//                   QGraphicsRectItem::ItemIsMovable);
//    QPen pen(m_Color);
//    pen.setWidth(10);
//    item->setPen(pen);
//    item->setPos(-100+qrand()%200,-60+qrand()%120);
//    item->setData(ItemId,++seqNum);
//    item->setData(ItemDescription,"直线");
//    scene->addItem(item);
//    scene->clearSelection();
//    item->setSelected(true);
}

void DrawMainWindow::on_action_Polyline_triggered()
{

}

void DrawMainWindow::on_action_Trapezium_triggered()
{
    QVector<QPointF> points;
    points << QPointF(-50, -50) << QPointF(50, -50) << QPointF(20, 50) << QPointF(-20, 50);

    auto *triangle = new QGraphicsPolygonItem(QPolygonF(points));
    triangle->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    triangle->setBrush(QBrush(m_Color));

    triangle->setPos(-100+qrand()%200,-60+qrand()%120);

    static int seqNum = 0;
    triangle->setData(ItemId, ++seqNum);
    triangle->setData(ItemDescription, "三角形");
    scene->addItem(triangle);
    scene->clearSelection();
    triangle->setSelected(true);
}

#include <QInputDialog>
void DrawMainWindow::on_action_Text_triggered()
{
    QString str=QInputDialog::getText(this,"请输入文本内容","请输入：");
    auto *item=new QGraphicsTextItem(str);
    item->setFlags(QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
//    QFont font;
//    font.setPointSize(20);

    item->setDefaultTextColor(Qt::black);       // 字体目前规定黑色
    item->setFont(m_Font);          // 使用预先设置的

    item->setPos(-100+qrand()%200,-60+qrand()%120);
    item->setData(ItemId,++seqNum);
    item->setData(ItemDescription,"文字");
    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void DrawMainWindow::on_action_SetColor_triggered()
{
    QColor new_Color=QColorDialog::getColor(m_Color, this, "Choose a color");

    if (new_Color.isValid()) {
        m_Color=new_Color;
        qDebug() << "Selected color:" << m_Color.name();
    } else {
        qDebug() << "Color selection cancelled.";
    }
}

//
#include <QFontDialog>
void DrawMainWindow::on_action_SetFont_triggered()
{
    bool flag;
    QFont new_Font=QFontDialog::getFont(&flag,m_Font,this,"请选择文字字体");
    if (flag) {
        m_Font=new_Font;
        qDebug() << "Selected font:" << m_Font.family() << ", Size:" << m_Font.pointSize();
    } else {
        qDebug() << "Font selection cancelled.";
    }
}

void DrawMainWindow::on_action_SetFrameSize_triggered()
{
    Dialog_SetWidth *dialog= new Dialog_SetWidth(m_FrameSize,this);
    dialog->setToolTip("请设置边框宽度");
    if (dialog->exec() == QDialog::Accepted) {
        int new_Width = dialog->getWidth();
        qDebug() << "Selected width:" << new_Width;
        if(new_Width!=m_FrameSize){
            qDebug() << "FrameSize set";
            m_FrameSize=new_Width;
        }
    }
}

void DrawMainWindow::on_action_SetLineWidth_triggered()
{
    Dialog_SetWidth dialog(m_LineWidth,this);
    dialog.setToolTip("请设置线段宽度");
    if (dialog.exec() == QDialog::Accepted) {
        int new_Width = dialog.getWidth();
        qDebug() << "Selected width:" << new_Width;
        if(new_Width!=m_LineWidth){
            qDebug() << "LineWidth set";
            m_LineWidth=new_Width;
        }
    }
}

void DrawMainWindow::on_action_CheckArea_triggered(bool checked)
{
    if(checked){
        ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    }else{
        ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    }
}

void DrawMainWindow::on_action_SingleLine_triggered(bool checked)
{
    scene->isPaintLineEventOn=checked;
}

void DrawMainWindow::on_action_Polyline_triggered(bool checked)
{
    scene->isPaintPloyLineEventOn=checked;
    // 退出折线绘制
    if(!checked){
//        emit;
    }
}

#include <QLinearGradient>
#include <QMessageBox>
void DrawMainWindow::on_action_SetGradient_triggered()
{
    // 获取选中的图形项
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }

    // 创建线性渐变
    QLinearGradient gradient(0, 0, 100, 100);

    // 定义 RGB 渐变颜色点
    // 调整 RGB 渐变颜色点
    gradient.setColorAt(0.0, QColor(255, 0, 0));  // 红色
    gradient.setColorAt(0.1, QColor(0, 255, 0));  // 绿色
    gradient.setColorAt(1, QColor(0, 0, 255));  // 蓝色

    // 使用渐变创建画刷
    QBrush brush(gradient);

    foreach (QGraphicsItem *item, selectedItems) {
        if(item->type()==QGraphicsRectItem::Type){
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);
            theItem->setBrush(brush);
        }else if(item->type()==QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
            theItem->setBrush(brush);
        }else if(item->type()==QGraphicsPolygonItem::Type){
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            theItem->setBrush(brush);
        }
        // 只能设置填充颜色
    }
}

void DrawMainWindow::on_action_ZoomIn_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        ui->graphicsView->scale(1.1,1.1);
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item = scene->selectedItems().at(i);

        QTransform currentTransform = item->transform(); // 获取当前的变换
        qreal scaleX = currentTransform.m11(); // 获取X方向的缩放系数
        qreal scaleY = currentTransform.m22(); // 获取Y方向的缩放系数

        // 调整缩放系数
        scaleX += 0.1;
        scaleY += 0.1;

        QTransform newTransform;
        newTransform.scale(scaleX, scaleY); // 设置新的缩放系数
        item->setTransform(newTransform, false); // 不叠加，直接设置新的变换
    }
}

void DrawMainWindow::on_action_ZoomOut_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        ui->graphicsView->scale(0.9,0.9);
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item = scene->selectedItems().at(i);

        QTransform currentTransform = item->transform(); // 获取当前的变换
        qreal scaleX = currentTransform.m11(); // 获取X方向的缩放系数
        qreal scaleY = currentTransform.m22(); // 获取Y方向的缩放系数

        // 调整缩放系数
        scaleX -= 0.1;
        scaleY -= 0.1;

        QTransform newTransform;
        newTransform.scale(scaleX, scaleY);
        item->setTransform(newTransform, false);
    }
}

void DrawMainWindow::on_action_Restore_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        ui->graphicsView->resetTransform();
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setScale(1);
    }
}

void DrawMainWindow::on_action_SpinLeft_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }
    int value=30;   // 要旋转的角度
    Dialog_SetWidth *dialog= new Dialog_SetWidth(30,this);
    dialog->setToolTip("请设置向左旋转的角度");
    if (dialog->exec() == QDialog::Accepted) {
        int new_Width = dialog->getWidth();
        if(new_Width!=value){
            value=new_Width;
        }
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setRotation(item->rotation()-value);
    }
}

void DrawMainWindow::on_action_SpinRight_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }
    int value=30;   // 要旋转的角度
    Dialog_SetWidth *dialog= new Dialog_SetWidth(30,this);
    dialog->setToolTip("请设置向右旋转的角度");
    if (dialog->exec() == QDialog::Accepted) {
        int new_Width = dialog->getWidth();
        if(new_Width!=value){
            value=new_Width;
        }
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setRotation(item->rotation()+value);
    }
}

void DrawMainWindow::on_action_Front_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setZValue(item->zValue()+1);
    }
}

void DrawMainWindow::on_action_Back_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setZValue(item->zValue()-1);
    }
}

void DrawMainWindow::on_action_Group_triggered()
{
    int cnt=scene->selectedItems().count();
    if(!(cnt>1)){
        QMessageBox::warning(this, "警告", "至少选中两个元素");
        return;
    }

    QGraphicsItemGroup *group=new QGraphicsItemGroup;
    scene->addItem(group);

    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(0);
        item->setSelected(false);
        group->addToGroup(item);
    }

    group->setFlags(QGraphicsItem::ItemIsFocusable|
                    QGraphicsItem::ItemIsSelectable|
                    QGraphicsItem::ItemIsMovable);
    scene->clearSelection();
    group->setSelected(true);
}

void DrawMainWindow::on_action_Delete_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        return;
    }
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(0);
        scene->removeItem(item);
    }
}

void DrawMainWindow::on_action_GroupBreak_triggered()
{
    int cnt=scene->selectedItems().count();
    if(cnt==0){
        return;
    }

    QList<QGraphicsItemGroup *> list;
    for(int i=0;i<cnt;i++){
        QGraphicsItem *item=scene->selectedItems().at(i);
        if(item->type()==QGraphicsItemGroup::Type){
            QGraphicsItemGroup *group=qgraphicsitem_cast<QGraphicsItemGroup *>(item);
            list.append(group);
        }
    }
    foreach(auto gItem,list){
        scene->destroyItemGroup(gItem);
    }
}

// 打开文件
// 另存为
// 保存文件
void DrawMainWindow::on_action_SaveFileJson_triggered()
{
    // 保存文件是存为默认位置 ./pattern.json
    bool flag=SceneFileHelper::saveSceneItemToFileJson("./pattern.json",scene);
    if(flag){
        QMessageBox::information(this,"提示","文件保存成功");
    }else{
        QMessageBox::warning(this,"警告","文件保存失败");
    }
}

void DrawMainWindow::on_action_SaveOtherFile_triggered()
{
    // 保存文件到自定义位置
    QString destPathStr=getSaveFilePath(this);
    bool flag=false;

    QFileInfo fileInfo(destPathStr); // 创建 QFileInfo 对象
    QString suffix = fileInfo.suffix().toLower(); // 获取文件后缀并转为小写

    if (suffix == "json") {
        flag=SceneFileHelper::saveSceneItemToFileJson(destPathStr,scene);
    } else if (suffix == "xml") {
        flag=SceneFileHelper::saveSceneItemToFileXml(destPathStr,scene);
    } else {
        // 其他格式或未知格式
    }

    if(flag){
        QMessageBox::information(this,"提示","文件保存成功");
    }else{
        QMessageBox::warning(this,"警告","文件保存失败");
    }
}

void DrawMainWindow::on_action_OpenFile_triggered()
{
    scene->clear();
    // 默认打开xml文件
    SceneFileHelper::loadItemXmlToScene(scene,"./pattern.xml");
}

void DrawMainWindow::on_action_OpenOtherFile_triggered()
{
    // 选择使用xml文件/json文件
    QString srcPathStr=getOpenFilePath(this);
    scene->clear();
    QFileInfo fileInfo(srcPathStr); // 创建 QFileInfo 对象
    QString suffix = fileInfo.suffix().toLower(); // 获取文件后缀并转为小写

    if (suffix == "json") {
        SceneFileHelper::loadItemJsonToScene(scene,srcPathStr);
    } else if (suffix == "xml") {
        SceneFileHelper::loadItemXmlToScene(scene,srcPathStr);
    } else {
        // 其他格式或未知格式
    }

}

#include <QFileDialog>
QString DrawMainWindow::getSaveFilePath(QWidget *parent)
{
    QString filePath = QFileDialog::getSaveFileName(
        parent,
        "保存文件",
        "",
        "XML 文件 (*.xml);;JSON 文件 (*.json)"
    );

    // 确保用户选择了文件路径
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".json", Qt::CaseInsensitive) && !filePath.endsWith(".xml", Qt::CaseInsensitive)) {
            filePath += ".xml"; // 默认使用 .xml 扩展名
        }
        return filePath;
    } else {
        return QString();
    }
}

QString DrawMainWindow::getOpenFilePath(QWidget *parent)
{
    QString filePath = QFileDialog::getOpenFileName(
        parent,
        "打开 XML/JSON 文件",
        "",
        "XML 文件 (*.xml);;JSON 文件 (*.json)"
    );

   // 确保用户选择了文件路径
   if (!filePath.isEmpty()) {
       return filePath;
   } else {
       // 用户取消了对话框
       return QString();
   }
}

void DrawMainWindow::on_action_Copy_triggered()
{
    // 获取选中的图形项
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }

    foreach (QGraphicsItem *item, selectedItems) {
        if(item->type()==QGraphicsRectItem::Type){
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

            if (theItem) {
                QGraphicsRectItem *newItem = new QGraphicsRectItem(theItem->rect());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                newItem->setBrush(theItem->brush());
                // 设置缩放
                newItem->setTransform(item->transform(), false);

                newItem->setPos(-100+qrand()%200,-60+qrand()%120);
                newItem->setData(ItemId,++seqNum);
                newItem->setData(ItemDescription,"矩形");
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

            if (theItem) {
                QGraphicsEllipseItem *newItem = new QGraphicsEllipseItem(theItem->rect());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                // 设置缩放
                newItem->setTransform(item->transform(), false);

                newItem->setPos(-100+qrand()%200,-60+qrand()%120);
                newItem->setData(ItemId,++seqNum);
                newItem->setData(ItemDescription,"圆形");
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsTextItem::Type){
            QGraphicsTextItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsTextItem *>(item);

            if (theItem) {
                // 创建一个新的 QGraphicsTextItem，使用原始 item 的文本
                QGraphicsTextItem *newItem = new QGraphicsTextItem(theItem->toPlainText());

                // 复制原 item 的样式和属性
                newItem->setFont(theItem->font());
                newItem->setTextInteractionFlags(theItem->textInteractionFlags());
                newItem->setDefaultTextColor(theItem->defaultTextColor());

                // 设置新的 item 的 flags
                newItem->setFlags(QGraphicsTextItem::ItemIsFocusable |
                                  QGraphicsTextItem::ItemIsSelectable |
                                  QGraphicsTextItem::ItemIsMovable);

                // 复制原 item 的变换
                newItem->setTransform(item->transform(), false);
                newItem->setPos(-100+qrand()%200,-60+qrand()%120);
                newItem->setData(ItemId,++seqNum);
                newItem->setData(ItemDescription,"文字");

                // 添加到场景中
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsPolygonItem::Type){
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            if (theItem) {
                QGraphicsPolygonItem *newItem = new QGraphicsPolygonItem(theItem->polygon());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);

                // 设置缩放
                newItem->setTransform(item->transform(), false);

                newItem->setPos(-100+qrand()%200,-60+qrand()%120);
                newItem->setData(ItemId,++seqNum);
                newItem->setData(ItemDescription,"多边形");
                scene->addItem(newItem);
            }
        }else if(item->type()==DeviceRectItem::Type){
            DeviceRectItem *theItem;
            theItem=qgraphicsitem_cast<DeviceRectItem *>(item);
            if (theItem) {

                QRectF rect=theItem->rect();

                qreal x =rect.x();
                qreal y =rect.y();
                qreal width =rect.width();
                qreal height =rect.height();

                DeviceRectItem *newItem = new DeviceRectItem(x,y,width,height);

//                DeviceRectItem *item=new DeviceRectItem(-50,-30,80,40);
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);

                newItem->setBrush(theItem->brush());
                newItem->setDeviceStateInfo(theItem->getDeviceStateInfo());
                newItem->setPos(-100+qrand()%200,-60+qrand()%120);
                newItem->setData(ItemId,++seqNum);
                newItem->setData(ItemDescription,"自定义设备模型");

                // 设置缩放
                newItem->setTransform(item->transform(), false);

                scene->addItem(newItem);
            }
        }

    }
}

void DrawMainWindow::on_action_Paste_triggered()
{
    // 获取选中的图形项
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }

    foreach (QGraphicsItem *item, selectedItems) {
        if(item->type()==QGraphicsRectItem::Type){
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

            if (theItem) {
                QGraphicsRectItem *newItem = new QGraphicsRectItem(theItem->rect());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                newItem->setBrush(theItem->brush());
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

            if (theItem) {
                QGraphicsEllipseItem *newItem = new QGraphicsEllipseItem(theItem->rect());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsPolygonItem::Type){
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            if (theItem) {
                QGraphicsPolygonItem *newItem = new QGraphicsPolygonItem(theItem->polygon());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                scene->addItem(newItem);
            }
        }

    }
}

void DrawMainWindow::on_action_Cut_triggered()
{
    // 获取选中的图形项
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "警告", "没有选中的图形项");
        return;
    }

    foreach (QGraphicsItem *item, selectedItems) {
        if(item->type()==QGraphicsRectItem::Type){
            QGraphicsRectItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsRectItem *>(item);

            if (theItem) {
                QGraphicsRectItem *newItem = new QGraphicsRectItem(theItem->rect());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                newItem->setBrush(theItem->brush());
                scene->removeItem(theItem);
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsEllipseItem::Type){
            QGraphicsEllipseItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsEllipseItem *>(item);

            if (theItem) {
                QGraphicsEllipseItem *newItem = new QGraphicsEllipseItem(theItem->rect());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                scene->removeItem(theItem);
                scene->addItem(newItem);
            }

        }else if(item->type()==QGraphicsPolygonItem::Type){
            QGraphicsPolygonItem *theItem;
            theItem=qgraphicsitem_cast<QGraphicsPolygonItem *>(item);
            if (theItem) {
                QGraphicsPolygonItem *newItem = new QGraphicsPolygonItem(theItem->polygon());
                newItem->setBrush(theItem->brush());
                newItem->setFlags(QGraphicsRectItem::ItemIsFocusable |
                               QGraphicsRectItem::ItemIsSelectable |
                               QGraphicsRectItem::ItemIsMovable);
                scene->removeItem(theItem);
                scene->addItem(newItem);
            }
        }

    }
}

void DrawMainWindow::on_action_SaveFileXml_triggered()
{
    // 保存文件是存为默认位置，系统默认打开这个 ./pattern.xml
    bool flag=SceneFileHelper::saveSceneItemToFileXml("./pattern.xml",scene);
    if(flag){
        QMessageBox::information(this,"提示","文件保存成功");
    }else{
        QMessageBox::warning(this,"警告","文件保存失败");
    }
}
