#ifndef ALFREDGRAPHICSVIEW_H
#define ALFREDGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

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
//    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

//    void paintEvent(QPaintEvent *event) override;

private:
    // 对按下鼠标的事件，对直线的操作
    void mousePressEvent_Line(QMouseEvent *event);

    void mouseReleaseEvent_Line(QMouseEvent *event);

public slots:
    void setPaintLineEventOn(bool flag);

signals:
    void keyPress(QKeyEvent *event);
    void mouseDoubleClick(QPoint point);
    void mouseClicked(QPoint point);

private:

    void drawLineSeg(QPainter* p);

    void selSeg(QPointF&pt);


    struct LINESEG {
        bool bDraw;//是否绘制

        bool bSelLine;//是否选中线
        bool bSelStartPt;//是否选中线段起点
        bool bSelEndPt;//是否选线段终点
        LineSegment* seg;
        LINESEG() {
            bDraw = false;
            bSelLine = false;
            bSelStartPt = false;
            bSelEndPt = false;
            seg = new LineSegment;
        }
    };

private:
    bool m_LineFlag=false;

    // 绘制直线属性
    bool bLBtnDown = false;//左键按下
    QPoint startPoint,endPoint; // 绘制的起点和终点
    LINESEG *tmpLine=nullptr;
    QVector<LINESEG *> lineSegs;    //线段列表
    LINESEG* selectLineSeg = nullptr;//选中的线段
    LINESEG* getSeleled();//获取选中的线段
    QPointF movePoint;

};

#endif // ALFREDGRAPHICSVIEW_H
