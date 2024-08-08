#include "ploylineitem.h"
#include <QDebug>

PloyLineItem::PloyLineItem()
{
    path=QPainterPath();
    setFlag(ItemIsMovable);  // 可选：使图形项可移动，便于调试
}

PloyLineItem::~PloyLineItem()
{

}

void PloyLineItem::setPathStartPoint(const QPointF &point)
{
qDebug()<<"void PloyLineItem::setPathStartPoint(const QPointF &point)";
qDebug()<<point.x()<<point.y();
    path.moveTo(point);
    update(); // 强制重绘
}

void PloyLineItem::setPathEndPoint(const QPointF &point)
{
qDebug()<<"void PloyLineItem::setPathEndPoint(const QPointF &point)";
qDebug()<<point.x()<<point.y();
    path.lineTo(point);
    update(); // 强制重绘
}

QPen PloyLineItem::pen() const
{
    return m_Pen;
}

void PloyLineItem::setPen(const QPen &pen)
{
    m_Pen=pen;
    update(); // 通知视图重绘图形项
}

QRectF PloyLineItem::boundingRect() const
{
    if (path.isEmpty()) {
        return QRectF(); // 默认边界
    } else {
        // 计算路径的边界
        QPointF topLeft = path.boundingRect().topLeft();
        QPointF bottomRight = path.boundingRect().bottomRight();
        // 扩大边界以适应一些额外空间
        qreal xPadding = 10.0;
        qreal yPadding = 10.0;
        return QRectF(topLeft.x() - xPadding,
                      topLeft.y() - yPadding,
                      bottomRight.x() - topLeft.x() + 2 * xPadding,
                      bottomRight.y() - topLeft.y() + 2 * yPadding);
    }
}

void PloyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(m_Pen);
    painter->drawPath(path);
}

int PloyLineItem::type() const
{
    return Type;
}
