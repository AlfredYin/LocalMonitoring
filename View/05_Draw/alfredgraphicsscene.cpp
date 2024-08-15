#include "alfredgraphicsscene.h"

AlfredGraphicsScene::AlfredGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
QGraphicsScene(x, y, width, height,nullptr), currentLine(nullptr)
{
    m_SingleLinePen=QPen();
    m_SingleLinePen.setWidth(3);
}

AlfredGraphicsScene::AlfredGraphicsScene(QObject *parent) : QGraphicsScene(parent), currentLine(nullptr)
{

}

void AlfredGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {

        if(isPaintLineEventOn){     // 可以绘制直线
            currentLine = new SingleLineItem();
            currentLine->setPen(m_SingleLinePen);

            currentLine->setStartPoint(event->scenePos());
            currentLine->setEndPoint(event->scenePos());

            currentLine->setData(1,0);
            currentLine->setData(2,"自定义直线");
            addItem(currentLine);
        }else if (isPaintPloyLineEventOn){  // 可以绘制折线

            // 获取第一个直线开始绘制的点 ， 要判断是否已经有了起始点

            if(currentLine==nullptr){    // 第一次点击
                if(startPoint.rx()==0 && startPoint.ry()==0){
                    startPoint=event->scenePos();
                    flag=true;
                }
                // startPoint=event->scenePos();
                currentLine = new SingleLineItem();
                currentLine->setPen(m_SingleLinePen);
                currentLine->setStartPoint(startPoint);
                if(flag){
                    currentLine->setEndPoint(event->scenePos());    // 第三次点击，把第二条直线的终点设置为鼠标点击的位置
                    startPoint=event->scenePos();
                }else{
                    currentLine->setEndPoint(startPoint);  // 第一个点击绘制出了起始点和终止点
                }
                currentLine->setData(1,0);
                currentLine->setData(2,"自定义直线");
                addItem(currentLine);

                if(flag){
                    currentLine=nullptr;    // 置空，准备绘制第三条直线
                }

            }else{      // 第二次点击把终止点的位置移动到鼠标点击的位置
                // currentLine!=nullptr
                // 判断是否选定的是终止点, 是终止点就连接起来了
                endPoint=event->scenePos();
                currentLine->setEndPoint(endPoint);     // 重新设置该条直线的终点
                startPoint=endPoint;        // 为下一个条直线提前预备起始点
                currentLine=nullptr;        // 清空，准备绘制下一条直线
            }




        }else if (isPaintRectEventOn){  // 可以绘制矩形
            startPoint = event->scenePos();
            currentRectItem = new QGraphicsRectItem(QRectF(startPoint, startPoint));
            currentRectItem->setFlags(QGraphicsRectItem::ItemIsFocusable|QGraphicsRectItem::ItemIsSelectable|QGraphicsRectItem::ItemIsMovable);
            currentRectItem->setData(1,3);
            currentRectItem->setData(2,"自由绘制矩形");
            currentRectItem->setBrush(QBrush(m_Color));
            addItem(currentRectItem);
        }else if(isPaintEllipseEventOn){    // 绘制椭圆
            startPoint = event->scenePos();
            currentEllipseItem = new QGraphicsEllipseItem(QRectF(startPoint, startPoint));
            currentEllipseItem->setFlags(QGraphicsRectItem::ItemIsFocusable|QGraphicsRectItem::ItemIsSelectable|QGraphicsRectItem::ItemIsMovable);
            currentEllipseItem->setData(1,4);
            currentEllipseItem->setData(2,"自由绘制椭圆");
            currentEllipseItem->setBrush(QBrush(m_Color));
            addItem(currentEllipseItem);
        }else if(isPaintCircleEventOn){  // 绘制正圆

            centerPoint = event->scenePos();
            currentCircleItem = new QGraphicsEllipseItem(QRectF(centerPoint, QSizeF(0, 0)));
            currentCircleItem->setFlags(QGraphicsRectItem::ItemIsFocusable|QGraphicsRectItem::ItemIsSelectable|QGraphicsRectItem::ItemIsMovable);
            currentCircleItem->setData(1,4);
            currentCircleItem->setData(2,"自由绘制正圆");
            currentCircleItem->setBrush(QBrush(m_Color));
            addItem(currentCircleItem);
        }

        update();
    }
    QGraphicsScene::mousePressEvent(event);
}

void AlfredGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons()&Qt::LeftButton) {

        if(isPaintLineEventOn && currentLine!=nullptr){
            currentLine->setEndPoint(event->scenePos());
        }else if (isPaintPloyLineEventOn){
//            currentPloyLine->setPathEndPoint(event->scenePos());
        }else if (isPaintRectEventOn && currentRectItem){  // 可以绘制矩形
            QRectF newRect(startPoint, event->scenePos());
            currentRectItem->setRect(newRect.normalized());
        }else if (isPaintEllipseEventOn && currentEllipseItem){  // 椭圆
            QRectF newRect(startPoint, event->scenePos());
            currentEllipseItem->setRect(newRect.normalized());
        }else if (isPaintCircleEventOn && currentCircleItem){  // 圆
            QPointF currentPoint = event->scenePos();       // 获取当前的中心点
            qreal radius = QLineF(centerPoint, currentPoint).length();
            QRectF newRect(centerPoint.x() - radius, centerPoint.y() - radius, 2 * radius, 2 * radius);
            currentCircleItem->setRect(newRect);
        }
        update();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void AlfredGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(isPaintLineEventOn  && currentLine){     // 直线的绘制
            currentLine->setEndPoint(event->scenePos());
            currentLine = nullptr;
        }else if(isPaintPloyLineEventOn  && currentLine){     // 直线的绘制
//            startPoint=endPoint;    // 把新的起点设置为上一条直线的终点
//            currentLine->setEndPoint(startPoint);
//            currentLine = nullptr;
        }else if (isPaintRectEventOn && currentRectItem){  // 可以绘制矩形
            QRectF finalRect = currentRectItem->rect();
            if (finalRect.width() == 0 || finalRect.height() == 0) {
                // 如果矩形大小为0，则移除它
                removeItem(currentRectItem);
                delete currentRectItem;
            }
            currentRectItem = nullptr;
        }else if (isPaintEllipseEventOn && currentEllipseItem){  // 绘制椭圆
            QRectF finalRect = currentEllipseItem->rect();
            if (finalRect.width() == 0 || finalRect.height() == 0) {
                removeItem(currentEllipseItem);
                delete currentEllipseItem;
            }
            currentEllipseItem = nullptr;
        }else if (isPaintCircleEventOn && currentCircleItem){  // 绘制圆
            QRectF finalRect = currentCircleItem->rect();
            if (finalRect.width() == 0 || finalRect.height() == 0) {
                // 如果圆的大小为0，则移除它
                removeItem(currentCircleItem);
                delete currentCircleItem;
            }
            currentCircleItem = nullptr;
        }
        update();
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void AlfredGraphicsScene::startPloyLinePaint(bool state)
{
    if(state){  // 开始绘制
        isPaintPloyLineEventOn=true;
        startPoint=QPointF();
        endPoint=QPointF();
        currentLine=nullptr;
    }else{
        isPaintPloyLineEventOn=false;
        startPoint=QPointF();
        endPoint=QPointF();
        currentLine=nullptr;
    }
}
