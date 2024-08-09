#ifndef REFRESHTEXTITEM_H
#define REFRESHTEXTITEM_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QObject>

class RefreshTextItem : public QGraphicsTextItem
{
    Q_OBJECT

public:
    explicit RefreshTextItem(const QString& text, QGraphicsItem* parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
signals:
    void refreshClicked();
};

#endif // REFRESHTEXTITEM_H
