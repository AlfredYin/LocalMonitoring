#ifndef CONTROLDEVICERECTITEM_H
#define CONTROLDEVICERECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QRect>
#include <QIcon>
#include <QRectF>

#include "devicestateinfo.h"

class ControlDeviceRectItem : public QGraphicsRectItem
{
public:
    ControlDeviceRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    ControlDeviceRectItem();

    ControlDeviceState getControlDeviceState();

    void setControlDeviceState(ControlDeviceState state);

protected:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public:
    enum {
        Type=10030    // 控制子设备模板
    };

    int type() const override;

private:
    ControlDeviceState m_ControlDeviceState;
};

#endif // CONTROLDEVICERECTITEM_H
