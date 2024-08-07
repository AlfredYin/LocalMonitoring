#ifndef ALFREDGRAPHICSSCENE_H
#define ALFREDGRAPHICSSCENE_H

#include "singlelineitem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

class AlfredGraphicsScene : public QGraphicsScene
{
public:
    AlfredGraphicsScene(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override{
        if (event->buttons() == Qt::LeftButton) {
            currentLine = new SingleLineItem();
            currentLine->setStartPoint(event->scenePos());
            currentLine->setEndPoint(event->scenePos());
            addItem(currentLine);
        }
        QGraphicsScene::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (currentLine && event->buttons()&Qt::LeftButton) {
            currentLine->setEndPoint(event->scenePos());
        }
        QGraphicsScene::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton && currentLine) {
            currentLine = nullptr;
        }
        QGraphicsScene::mouseReleaseEvent(event);
    }

private:
    SingleLineItem *currentLine;

};

#endif // ALFREDGRAPHICSSCENE_H
