#ifndef ALFREDGRAPHICSVIEW_H
#define ALFREDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

#include "singlelineitem.h"
#include "ploylineitem.h"
#include "GraphBase.h"

class AlfredGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AlfredGraphicsView(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
//    void keyReleaseEvent(QKeyEvent *event) override;

    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void keyPress(QKeyEvent *event);
    void mouseDoubleClick(QPoint point);
    void mouseClicked(QPoint point);
    void mouseRightClicked(QPoint point);

private:
};

#endif // ALFREDGRAPHICSVIEW_H
