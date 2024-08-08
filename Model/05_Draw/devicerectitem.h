#ifndef DEVICERECTITEM_H
#define DEVICERECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>

#include "devicestateinfo.h"

class DeviceRectItem : public QGraphicsRectItem
{
public:
    DeviceRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    DeviceRectItem();

    DeviceStateInfo getDeviceStateInfo();
    void setDeviceStateInfo(DeviceStateInfo state);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    DeviceStateInfo m_DeviceStateInfo;
};

#endif // DEVICERECTITEM_H
