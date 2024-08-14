#include "sensorrectitem.h"

SensorRectItem::SensorRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):
    QGraphicsRectItem(x, y, w, h, parent)
{
    m_SensorState=SensorState();
}

SensorRectItem::SensorRectItem()
{
    m_SensorState=SensorState();
}

SensorState SensorRectItem::getSensorState()
{
    return m_SensorState;
}

void SensorRectItem::setSensorState(SensorState state)
{
    m_SensorState=state;
}

void SensorRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 调用基类的绘制方法
    if(m_SensorState.sensorflag==0){
        painter->setBrush(QBrush(Qt::gray));
        QGraphicsRectItem::paint(painter, option, widget);
        return;
    }

    QGraphicsRectItem::paint(painter, option, widget);
    painter->setPen(Qt::NoPen); // 不需要边框
    QRectF rect = this->rect();
    qreal radius = 10; // 圆的半径

    QPointF center(rect.center().x()-25, rect.top() + radius + 5);
    painter->drawEllipse(center, radius, radius);

    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);

    QFontMetrics fm(painter->font());  // 获取当前字体的字体度量
    int textHeight = 0;

    if(!m_SensorState.sensor.isEmpty()){
        // 在矩形中心绘制文本
        painter->drawText(rect, Qt::AlignLeft, m_SensorState.sensor);
        textHeight = fm.height();  // 获取第一段文字的高度
    }
    // 更新绘制矩形的位置，将其下移textHeight
    QRectF rectBelow = rect.adjusted(0, textHeight, 0, textHeight);
    if(!m_SensorState.sensorname.isEmpty()){
        // 在矩形中心绘制文本
        painter->drawText(rectBelow, Qt::AlignLeft, m_SensorState.sensorname);
    }
}

//int SensorRectItem::type(){
//    return Type;
//}
