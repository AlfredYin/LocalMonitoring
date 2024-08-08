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
    if(event->button()==Qt::RightButton){

        qDebug()<<"event->button()==Qt::RightButton";

        QPoint point=event->pos();
        emit mouseRightClicked(point);
    }
    QGraphicsView::mousePressEvent(event);
}

void AlfredGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void AlfredGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{

    QGraphicsView::mouseReleaseEvent(event);
}
