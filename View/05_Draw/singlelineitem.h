#ifndef SINGLELINEITEM_H
#define SINGLELINEITEM_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QLineF>

class SingleLineItem : public QGraphicsItem
{
public:
    explicit SingleLineItem(){
        setFlag(ItemIsSelectable); // 设置可选标志
        setFlag(ItemIsMovable);    // 设置可移动标志
    }

    QRectF boundingRect() const override{
        return QRectF(startPoint, endPoint).normalized();
    }

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option, QWidget *widget) override{
        QPen pen(Qt::blue, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter->setPen(pen);
        painter->drawLine(startPoint, endPoint);
    }

    void setStartPoint(const QPointF &point){
        startPoint = point;
        update();
    }

    void setEndPoint(const QPointF &point){
        endPoint = point;
        update();
    }

signals:

public slots:

private:
    QPointF startPoint, endPoint;
};

#endif // SINGLELINEITEM_H
