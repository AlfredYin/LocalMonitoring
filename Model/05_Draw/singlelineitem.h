#ifndef SINGLELINEITEM_H
#define SINGLELINEITEM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QLineF>
#include <QPen>

#include "graphbase.h"

class SingleLineItem : public QGraphicsItem
{
public:
    explicit SingleLineItem();

    // 用于计算一个图形元素的边界矩形（bounding rectangle）。
    // 这个矩形用来确定图形在场景中的占用范围，这对于图形的布局、碰撞检测以及绘制优化
    QRectF boundingRect() const override;

    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setStartPoint(const QPointF &point);

    void setEndPoint(const QPointF &point);

    QPen pen() const;
    void setPen(const QPen &pen);

    QPointF getStartPoint();
    QPointF getEndPoint();

signals:

public:
    enum {
        Type = 10001
    };
    int type() const;

public slots:

private:
    QPen m_Pen;
    QPointF startPoint,endPoint; // 绘制的起点和终点
};

#endif // SINGLELINEITEM_H
