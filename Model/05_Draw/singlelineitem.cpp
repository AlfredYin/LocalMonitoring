#include "singlelineitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QVector>

SingleLineItem::SingleLineItem()
{
//    // 设置可选不可移动
//    setFlag(ItemIsSelectable); // 设置可选标志
//    setFlags(flags()&~ItemIsSelectable);

    setFlag(ItemIsSelectable); // 设置可选标志
    setFlag(ItemIsMovable);    // 设置可移动标志
}

QRectF SingleLineItem::boundingRect() const
{
    QPointF start = startPoint;
    QPointF end = endPoint;

    qreal left = qMin(start.x(), end.x());
    qreal right = qMax(start.x(), end.x());
    qreal top = qMin(start.y(), end.y());
    qreal bottom = qMax(start.y(), end.y());

    // 计算宽度和高度
    qreal width = right - left;
    qreal height = bottom - top;

    // 创建一个更紧凑的矩形
    return QRectF(left, top, width, height).normalized();
}

void SingleLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);

    painter->setPen(m_Pen);
    painter->drawLine(startPoint, endPoint);
}

void SingleLineItem::setStartPoint(const QPointF &point)
{
    startPoint = point;
    update();
}

void SingleLineItem::setEndPoint(const QPointF &point)
{
    endPoint = point;
    update();
}

QPen SingleLineItem::pen() const
{
    return m_Pen;
}

void SingleLineItem::setPen(const QPen &pen)
{
    m_Pen=pen;
    update(); // 通知视图重绘图形项
}

int SingleLineItem::type() const
{
    return Type;
}
