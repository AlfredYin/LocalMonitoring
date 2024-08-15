#include "controldevicerectitem.h"

ControlDeviceRectItem::ControlDeviceRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent):
    QGraphicsRectItem(x, y, w, h, parent)
{
    m_ControlDeviceState=ControlDeviceState();
}

ControlDeviceRectItem::ControlDeviceRectItem()
{
    m_ControlDeviceState=ControlDeviceState();
}

ControlDeviceState ControlDeviceRectItem::getControlDeviceState()
{
    return m_ControlDeviceState;
}

void ControlDeviceRectItem::setControlDeviceState(ControlDeviceState state)
{
    m_ControlDeviceState=state;
}

void ControlDeviceRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // 调用基类的绘制方法

//    if(m_ControlDeviceState.baseDelete==0){
//        painter->setBrush(QBrush(Qt::gray));
//        QGraphicsRectItem::paint(painter, option, widget);
//        return;
//    }

    QGraphicsRectItem::paint(painter, option, widget);
    painter->setPen(Qt::NoPen); // 不需要边框

    QRectF rect = this->rect();     // 获取绘制的边界矩形
    // 绘制一个Icon
    // 使用资源文件中的图标
    // 根据设备的不同类型，选择不同的icon
    QIcon icon;
    if(m_ControlDeviceState.device.indexOf("trigger")!=-1){ // 继电器
         icon.addFile(":/controldevice/icons/trigger.jpg");
    }else if(m_ControlDeviceState.device.indexOf("beep")!=-1){   // 蜂鸣器
        icon.addFile(":/controldevice/icons/beep.jpg");
    }else if(m_ControlDeviceState.device.indexOf("rgb")!=-1){   // rgb
        icon.addFile(":/controldevice/icons/rgb.jpg");
    }else if(m_ControlDeviceState.device.indexOf("led")!=-1){   // led
        icon.addFile(":/controldevice/icons/led.jpg");
    }else if(m_ControlDeviceState.device.indexOf("servo")!=-1){   // 舵机
        icon.addFile(":/controldevice/icons/servo.jpg");
    }

    // 定义图标的绘制区域（确保图标位于矩形内部）
    int iconSize = qMin(rect.width(), rect.height()) - 10; // 图标大小
    QRectF iconRect(rect.left()-iconSize/2-20, rect.center().y() - iconSize / 2, iconSize, iconSize);
    // 绘制图标
    if(!icon.isNull()){
        icon.paint(painter, iconRect.toRect());
    }

    // 绘制外部的状态圆形
    if(m_ControlDeviceState.devicestate=="off"){
        painter->setBrush(QBrush(Qt::red));
    }else if(m_ControlDeviceState.devicestate=="on"){
        painter->setBrush(QBrush(Qt::green));
    }else {     // 未知状态
        painter->setBrush(QBrush(Qt::gray));
    }
    // 在矩形的外面的右侧绘制
    qreal radius = 10; // 圆的半径
    QPointF center(rect.right() + radius + 5, rect.center().y());
    painter->drawEllipse(center, radius, radius);

    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);
    QFontMetrics fm(painter->font());  // 获取当前字体的字体度量
    int textHeight = 0;
    if(!m_ControlDeviceState.device.isEmpty()){
        // 在矩形中心绘制文本
        painter->drawText(rect, Qt::AlignLeft, m_ControlDeviceState.device);
        textHeight = fm.height();  // 获取第一段文字的高度
    }
    // 更新绘制矩形的位置，将其下移textHeight
    QRectF rectBelow = rect.adjusted(0, textHeight, 0, textHeight);
    if(!m_ControlDeviceState.devicename.isEmpty()){
        // 在矩形中心绘制文本
        painter->drawText(rectBelow, Qt::AlignLeft, m_ControlDeviceState.devicename);
    }


    // 在状态指示圆的后面绘制出状态的文字
    QFontMetrics fmState(painter->font());
    int textStateHeight = fmState.height();
    qreal textY = center.y() + textStateHeight / 4; // 使文字的中线和圆的中线对齐
    qreal textX = center.x() + radius + 5; // 在圆的右侧绘制文字
    painter->drawText(QPointF(textX, textY),m_ControlDeviceState.devicestate);
}

int ControlDeviceRectItem::type() const
{
    return Type;
}
