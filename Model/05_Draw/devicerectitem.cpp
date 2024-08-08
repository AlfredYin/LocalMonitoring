#include "devicerectitem.h"

DeviceRectItem::DeviceRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):
    QGraphicsRectItem(x, y, w, h, parent)
{
    m_DeviceStateInfo=DeviceStateInfo();
}

DeviceRectItem::DeviceRectItem()
{
    m_DeviceStateInfo=DeviceStateInfo();
}

DeviceStateInfo DeviceRectItem::getDeviceStateInfo()
{
    return m_DeviceStateInfo;
}

void DeviceRectItem::setDeviceStateInfo(DeviceStateInfo state)
{
    m_DeviceStateInfo=state;
}

void DeviceRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    // 调用基类的绘制方法
    QGraphicsRectItem::paint(painter, option, widget);
    if(m_DeviceStateInfo.connectingflag==1){
        painter->setBrush(QBrush(Qt::green));
    }else{
        painter->setBrush(QBrush(Qt::red));
    }

    painter->setPen(Qt::NoPen); // 不需要边框
    QRectF rect = this->rect();
    qreal radius = 10; // 圆的半径
    QPointF center(rect.center().x()-25, rect.top() + radius + 5); // 圆心位置

    painter->drawEllipse(center, radius, radius);

    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);
    if(!m_DeviceStateInfo.devicename.isEmpty()){
        // 在矩形中心绘制文本
        painter->drawText(rect, Qt::AlignCenter, m_DeviceStateInfo.devicename);
    }
}
