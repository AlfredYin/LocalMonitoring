#ifndef SENSSORRECTITEM_H
#define SENSSORRECTITEM_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QObject>
#include <QRect>

#include "devicestateinfo.h"
//#include "devicestateresult.h"

class SensorRectItem : public QGraphicsRectItem
{
public:
    SensorRectItem(qreal x, qreal y, qreal w, qreal h, QGraphicsItem *parent = nullptr);
    SensorRectItem();

    SensorState getSensorState();

    void setSensorState(SensorState state);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

public:
    enum {
        Type=10020    // 传感器模板001
    };
    int type() const;

private:
    SensorState m_SensorState;
};

#endif // SENSSORRECTITEM_H
