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

#include <QDebug>

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

    if(m_SensorState.sensorstate=="offline"){
        painter->setBrush(QBrush(Qt::red));
    }else if(m_SensorState.sensorstate=="online"){
        painter->setBrush(QBrush(Qt::green));
    }else {     // 未知状态
        painter->setBrush(QBrush(Qt::gray));
    }

    QRectF rect = this->rect();
    qreal radius = 10; // 圆的半径

    // 在矩形的外面的右侧绘制
    QPointF center(rect.right() + radius + 5, rect.center().y());
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

    // 在状态指示圆的后面绘制出状态的文字
    QFontMetrics fmState(painter->font());
    int textStateHeight = fmState.height();
    qreal textY = center.y() + textStateHeight / 4; // 使文字的中线和圆的中线对齐
    qreal textX = center.x() + radius + 5; // 在圆的右侧绘制文字
    painter->drawText(QPointF(textX, textY),m_SensorState.sensorstate);
}

int SensorRectItem::type() const
{
    return Type;
}
