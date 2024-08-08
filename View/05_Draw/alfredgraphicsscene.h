#ifndef ALFREDGRAPHICSSCENE_H
#define ALFREDGRAPHICSSCENE_H

#include "singlelineitem.h"
#include "ploylineitem.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>


class AlfredGraphicsScene : public QGraphicsScene
{
public:

    static const int LineItemId=1;
    static const int ItemDescription=2;

    bool isPaintLineEventOn=false;
    bool isPaintPloyLineEventOn=false;

    AlfredGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    AlfredGraphicsScene(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    SingleLineItem *currentLine;
    PloyLineItem *currentPloyLine;

};

#endif // ALFREDGRAPHICSSCENE_H
