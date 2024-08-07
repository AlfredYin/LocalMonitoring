#include "alfredgraphicsview.h"

#include <QMouseEvent>
#include <QtDebug>

AlfredGraphicsView::AlfredGraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

void AlfredGraphicsView::keyPressEvent(QKeyEvent *event)
{
    emit keyPress(event);
    QGraphicsView::keyPressEvent(event);
}

void AlfredGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint point=event->pos();
        emit mouseDoubleClick(point);
    }
    QGraphicsView::mouseDoubleClickEvent(event);
}

void AlfredGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        QPoint point=event->pos();
        emit mouseClicked(point);
    }
    if(m_LineFlag){
        mousePressEvent_Line(event);
    }
    QGraphicsView::mousePressEvent(event);
}

void AlfredGraphicsView::mousePressEvent_Line(QMouseEvent *event)
{
    qDebug()<<"void AlfredGraphicsView::mousePressEvent_Line(QMouseEvent *event)";
    switch(event->button()) {
        case Qt::LeftButton:
        bLBtnDown = true;
        selectLineSeg = nullptr;
        selectLineSeg = getSeleled();
        if(selectLineSeg != nullptr){//选中线段
            selectLineSeg->bDraw = false;

            if(selectLineSeg->bSelStartPt) {//选中起点
                startPoint.setX(selectLineSeg->seg->endPoint.x);
                startPoint.setY(selectLineSeg->seg->endPoint.y);

                endPoint.setX(selectLineSeg->seg->startPoint.x);
                endPoint.setY(selectLineSeg->seg->startPoint.y);
            } else if(selectLineSeg->bSelEndPt) {//选中终点
                startPoint.setX(selectLineSeg->seg->startPoint.x);
                startPoint.setY(selectLineSeg->seg->startPoint.y);

                endPoint.setX(selectLineSeg->seg->endPoint.x);
                endPoint.setY(selectLineSeg->seg->endPoint.y);
            } else if(selectLineSeg->bSelLine){//选中线段
                movePoint = event->pos();

                startPoint.setX(selectLineSeg->seg->startPoint.x);
                startPoint.setY(selectLineSeg->seg->startPoint.y);

                endPoint.setX(selectLineSeg->seg->endPoint.x);
                endPoint.setY(selectLineSeg->seg->endPoint.y);
            }
            update();
        } else {//未选中
            startPoint = event->pos();
            endPoint = startPoint;

            tempLine = new LINESEG;
            tempLine->seg->startPoint.x = startPoint.x();
            tempLine->seg->startPoint.y = startPoint.y();
        }
        break;
        default:
        break;
        }
}

void AlfredGraphicsView::setPaintLineEventOn(bool flag)
{
    qDebug()<<"void AlfredGraphicsView::setPaintLineEventOn(bool flag)";
    m_LineFlag=flag;
    qDebug()<<m_LineFlag;
}
