#ifndef ALFREDGRAPHICSVIEW_H
#define ALFREDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

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
//    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void mousePressEvent_Line(QMouseEvent *event);

public slots:
    void setPaintLineEventOn(bool flag);

signals:
    void keyPress(QKeyEvent *event);
    void mouseDoubleClick(QPoint point);
    void mouseClicked(QPoint point);

private:
    bool m_LineFlag=false;
};

#endif // ALFREDGRAPHICSVIEW_H
