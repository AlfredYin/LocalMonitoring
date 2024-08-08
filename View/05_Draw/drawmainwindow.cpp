#include "drawmainwindow.h"
#include "ui_drawmainwindow.h"
#include "devicerectitem.h"
#include "devicestateinfo.h"

#include <QTime>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsSimpleTextItem>

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
            Dialog_SetWidth *dialog= new Dialog_SetWidth(thePen.width(),this);
            dialog->setToolTip("修改直线宽度");
            if (dialog->exec() == QDialog::Accepted) {
                int new_Width = dialog->getWidth();
                if(new_Width!=thePen.width()){
                    thePen.setWidth(new_Width);
                }
            }
            theItem->setPen(thePen);
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
    QString str=QInputDialog::getText(this,"请输入对话框","请输入：");
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
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setScale(0.1+item->scale());
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
        QGraphicsItem *item=scene->selectedItems().at(i);
        item->setScale(-0.1+item->scale());
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
