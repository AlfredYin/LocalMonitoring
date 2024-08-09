#include "refreshtextitem.h"

#include <QGraphicsSceneMouseEvent>

RefreshTextItem::RefreshTextItem(const QString &text, QGraphicsItem *parent) : QGraphicsTextItem(text, parent)
{
    // 设置可移动
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setDefaultTextColor(Qt::blue);
    setFont(QFont("Arial", 14));
}

void RefreshTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit refreshClicked();
    }
    QGraphicsTextItem::mousePressEvent(event);
}
