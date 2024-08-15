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
#include <QPen>


class AlfredGraphicsScene : public QGraphicsScene
{
public:

    static const int LineItemId=1;
    static const int ItemDescription=2;

    bool isPaintLineEventOn=false;
    bool isPaintPloyLineEventOn=false;
    bool isPaintRectEventOn=false;
    bool isPaintEllipseEventOn=false;
    bool isPaintCircleEventOn=false;

    // 设置填充颜色
    QColor m_Color;

    AlfredGraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

    AlfredGraphicsScene(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void startPloyLinePaint(bool state);

private:
    SingleLineItem *currentLine;
//    PloyLineItem *currentPloyLine;
    QGraphicsRectItem *currentRectItem;
    QGraphicsEllipseItem *currentEllipseItem;
    QGraphicsEllipseItem *currentCircleItem;

    QPointF startPoint;
    QPointF endPoint;   // 折线使用
    bool flag=false;

    QPointF centerPoint;

    QPen m_SingleLinePen;
};

#endif // ALFREDGRAPHICSSCENE_H
