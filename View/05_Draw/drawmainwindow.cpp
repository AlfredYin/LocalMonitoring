#include "drawmainwindow.h"
#include "ui_drawmainwindow.h"

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
    scene=new QGraphicsScene(-300,-100,600,200);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setCursor(Qt::CrossCursor);
    ui->graphicsView->setMouseTracking(true);
//    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);     禁止全选
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);

    ui->statusBar->addWidget(label_ItemInfo);

    connect(ui->graphicsView,SIGNAL(keyPress(QKeyEvent *)),this,SLOT(on_keyPress(QKeyEvent *)));
    connect(ui->graphicsView,SIGNAL(mouseClicked(QPoint)),this,SLOT(on_mouseClicked(QPoint)));
    connect(ui->graphicsView,SIGNAL(mouseDoubleClick(QPoint)),this,SLOT(on_mouseDoubleClick(QPoint)));

    // 通知view是否需要绘制直线状态
    connect(this,SIGNAL(setPaintLineEvent(bool)),ui->graphicsView,SLOT(setPaintLineEventOn(bool)));

    qsrand(QTime::currentTime().msec());
}

DrawMainWindow::~DrawMainWindow()
{
    delete ui;
}

void DrawMainWindow::on_keyPress(QKeyEvent *event)
{
    qDebug()<<"void DrawMainWindow::on_keyPress(QKeyEvent *event)";
}

void DrawMainWindow::on_mouseDoubleClick(QPoint point)
{
    qDebug()<<"void DrawMainWindow::on_mouseDoubleClick(QPoint point)";
}

void DrawMainWindow::on_mouseClicked(QPoint point)
{
    qDebug()<<"void DrawMainWindow::on_mouseClicked(QPoint point)";
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
    emit setPaintLineEvent(checked);
}
