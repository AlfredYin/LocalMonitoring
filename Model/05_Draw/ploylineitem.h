#ifndef PLOYLINEITEM_H
#define PLOYLINEITEM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QLineF>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

class PloyLineItem : public QGraphicsItem
{
public:
    PloyLineItem();
    ~PloyLineItem();

    void setPathStartPoint(const QPointF &point);
    void setPathEndPoint(const QPointF &point);

    QPen pen() const;
    void setPen(const QPen &pen);

//    QBrush brush() const;
//    void setBrush(const QBrush &brush);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPainterPath path;

public:
    enum {
        Type = 10002
    };
    int type() const;

private:
    QPen m_Pen;
};

#endif // PLOYLINEITEM_H
