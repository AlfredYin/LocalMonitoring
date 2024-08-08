#include "alfredgraphicsscene.h"

AlfredGraphicsScene::AlfredGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent) :
QGraphicsScene(x, y, width, height,nullptr), currentLine(nullptr),currentPloyLine(nullptr)
{

}

AlfredGraphicsScene::AlfredGraphicsScene(QObject *parent) : QGraphicsScene(parent), currentLine(nullptr),currentPloyLine(nullptr)
{

}

void AlfredGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton) {

        if(isPaintLineEventOn){     // 可以绘制直线
            currentLine = new SingleLineItem();
            currentLine->setStartPoint(event->scenePos());
            currentLine->setEndPoint(event->scenePos());

            currentLine->setData(1,0);
            currentLine->setData(2,"自定义直线");
            addItem(currentLine);
        }else if (isPaintPloyLineEventOn){  // 可以绘制折线
            currentPloyLine = new PloyLineItem();
            currentPloyLine->setPathStartPoint(event->scenePos());

            currentPloyLine->setData(1,0);
            currentPloyLine->setData(2,"自定义折线");

            addItem(currentPloyLine);
        }
    }
    update();
    QGraphicsScene::mousePressEvent(event);
}

void AlfredGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons()&Qt::LeftButton) {

        if(isPaintLineEventOn && currentLine!=nullptr){
            currentLine->setEndPoint(event->scenePos());
        }else if (isPaintPloyLineEventOn && currentPloyLine){
            currentPloyLine->setPathEndPoint(event->scenePos());
        }
    }
    update();
    QGraphicsScene::mouseMoveEvent(event);
}

void AlfredGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(isPaintLineEventOn  && currentLine){
            currentLine->setEndPoint(event->scenePos());
            currentLine = nullptr;
        }
    }
    update();
    QGraphicsScene::mouseReleaseEvent(event);
}
