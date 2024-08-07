#include "alfredgraphicsview.h"

#include <QMouseEvent>
#include <QtDebug>

AlfredGraphicsView::AlfredGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
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

    // 在这里添加一个 update() 调用来确保视图被重绘
    update();
    QGraphicsView::mousePressEvent(event);
}

void AlfredGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_LineFlag){
        mouseReleaseEvent_Line(event);
    }

    QGraphicsView::mouseReleaseEvent(event);

    if(m_LineFlag){
        QPainter p;
        p.setRenderHint(QPainter::Antialiasing);

        drawLineSeg(&p);//绘制线段

        QPen pen;
        pen.setColor(QColor(255, 0, 0));
        pen.setWidth(2);
        p.setPen(pen);
        p.drawLine(startPoint, endPoint);
    }

    // 在这里添加一个 update() 调用来确保视图被重绘
    update();

}

//void AlfredGraphicsView::paintEvent(QPaintEvent *event)
//{
//    if(m_LineFlag){
//        QPainter p(this);
//        p.setRenderHint(QPainter::Antialiasing);

//        drawLineSeg(&p);//绘制线段

//        QPen pen;
//        pen.setColor(QColor(255, 0, 0));
//        pen.setWidth(2);
//        p.setPen(pen);
//        p.drawLine(startPoint, endPoint);
//    }
//}

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
                startPoint.setX(int(selectLineSeg->seg->endPoint.x));
                startPoint.setY(int(selectLineSeg->seg->endPoint.y));

                endPoint.setX(int(selectLineSeg->seg->startPoint.x));
                endPoint.setY(int(selectLineSeg->seg->startPoint.y));
            } else if(selectLineSeg->bSelEndPt) {//选中终点
                startPoint.setX(int(selectLineSeg->seg->startPoint.x));
                startPoint.setY(int(selectLineSeg->seg->startPoint.y));

                endPoint.setX(int(selectLineSeg->seg->endPoint.x));
                endPoint.setY(int(selectLineSeg->seg->endPoint.y));
            } else if(selectLineSeg->bSelLine){//选中线段
                movePoint = event->pos();

                startPoint.setX(int(selectLineSeg->seg->startPoint.x));
                startPoint.setY(int(selectLineSeg->seg->startPoint.y));

                endPoint.setX(int(selectLineSeg->seg->endPoint.x));
                endPoint.setY(int(selectLineSeg->seg->endPoint.y));
            }
            update();
        } else {//未选中
            startPoint = event->pos();
            endPoint = startPoint;

            tmpLine = new LINESEG;
            tmpLine->seg->startPoint.x = startPoint.x();
            tmpLine->seg->startPoint.y = startPoint.y();
        }
        break;
        default:
        break;
    }
}

void AlfredGraphicsView::mouseReleaseEvent_Line(QMouseEvent *event)
{
    qDebug()<<"void AlfredGraphicsView::mouseReleaseEvent_Line(QMouseEvent *event)";
    switch(event->button()) {
        case Qt::LeftButton:
        bLBtnDown = false;
        if(selectLineSeg != nullptr){
            if(selectLineSeg->bSelStartPt) {//选中起点
                selectLineSeg->seg->startPoint.x = event->pos().x();
                selectLineSeg->seg->startPoint.y = event->pos().y();

            } else if(selectLineSeg->bSelEndPt) {//选中终点
                selectLineSeg->seg->endPoint.x = event->pos().x();
                selectLineSeg->seg->endPoint.y = event->pos().y();
            } else if(selectLineSeg->bSelLine) {//选中线段
                selectLineSeg->seg->startPoint.x = startPoint.x();
                selectLineSeg->seg->startPoint.y = startPoint.y();

                selectLineSeg->seg->endPoint.x = endPoint.x();
                selectLineSeg->seg->endPoint.y = endPoint.y();
            }
            selectLineSeg->bDraw = true;

            selectLineSeg->bSelStartPt = false;
            selectLineSeg->bSelEndPt = false;
            selectLineSeg->bSelLine = false;
            selectLineSeg = nullptr;
        } else {
            tmpLine->seg->endPoint.x = event->pos().x();
            tmpLine->seg->endPoint.y = event->pos().y();
            tmpLine->bDraw = true;
            lineSegs.push_back(tmpLine);
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

void AlfredGraphicsView::selSeg(QPointF&pt){
    int num = lineSegs.size();
    for(int i = 0; i < num; i++) {
        LINESEG* oneLine = lineSegs.at(i);
        LineSegment* oneLineDeg = oneLine->seg;

        PointEx ptEx(pt.x(), pt.y());
        PointEx np;//线段上的点
        double dis = pToLinesegDist(ptEx, *oneLineDeg, np);
        if(dis < 5 && dis >= 0.0) {
            double l = relation(np, *oneLineDeg);
            if(abs(l)< EP) {//起点
                oneLine->bSelStartPt = true;
                oneLine->bSelLine = false;
                oneLine->bSelEndPt = false;
            } else if(abs(l - 1.0) < EP) {//终点
                oneLine->bSelEndPt = true;
                oneLine->bSelLine = false;
                oneLine->bSelStartPt = false;
            } else if(l < 1 && l > 0) {//整条线
                oneLine->bSelLine = true;
                oneLine->bSelEndPt = false;
                oneLine->bSelStartPt = false;
            }
        } else {
            oneLine->bSelLine = false;
            oneLine->bSelEndPt = false;
            oneLine->bSelStartPt = false;
        }
    }
}

void AlfredGraphicsView::drawLineSeg(QPainter* p){
    QPen pen;
    pen.setColor(QColor(255, 0, 0));
    int num = lineSegs.size();
    QPointF pt1, pt2;
    for(int i = 0; i < num; i++) {
        LINESEG* oneLine = lineSegs.at(i);
        if (oneLine->bDraw){//是否绘制
            pt1.setX(oneLine->seg->startPoint.x);
            pt1.setY(oneLine->seg->startPoint.y);

            pt2.setX(oneLine->seg->endPoint.x);
            pt2.setY(oneLine->seg->endPoint.y);

            if(oneLine->bSelLine||oneLine->bSelStartPt||oneLine->bSelEndPt) {//选中
                pen.setWidth(4);
                p->setPen(pen);
                if(oneLine->bSelLine){
                    p->drawLine(pt1, pt2);
                }
                if(oneLine->bSelStartPt) {
                    p->drawEllipse(pt1, 5, 5);
                    pen.setWidth(2);
                    p->setPen(pen);
                    p->drawLine(pt1, pt2);
                }
                if(oneLine->bSelEndPt){
                    p->drawEllipse(pt2, 5, 5);
                    pen.setWidth(2);
                    p->setPen(pen);
                    p->drawLine(pt1, pt2);
                }
            } else if(oneLine->bSelLine == false && oneLine->bSelStartPt == false && oneLine->bSelEndPt == false) {
                pen.setWidth(2);
                p->setPen(pen);
                p->drawLine(pt1, pt2);
            }
        }
    }

}

AlfredGraphicsView::LINESEG* AlfredGraphicsView::getSeleled(){
    int num = lineSegs.size();

    for(int i = 0; i < num; i++) {
        LINESEG* oneLine = lineSegs.at(i);
        if(oneLine->bSelLine || oneLine->bSelStartPt || oneLine->bSelEndPt) {//选中
            return oneLine;
        }
    }
    return nullptr;
}
