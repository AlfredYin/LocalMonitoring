#ifndef DRAWMAINWINDOW_H
#define DRAWMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColorDialog>
#include <QFontDialog>

#include "dialog_setwidth.h"

namespace Ui {
class DrawMainWindow;
}

class DrawMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *label_ItemInfo;
    QGraphicsScene *scene;

    int seqNum=0;

    static const int ItemId=1;
    static const int ItemDescription=2;

public:
    explicit DrawMainWindow(QWidget *parent = nullptr);
    ~DrawMainWindow();

public slots:
    void on_keyPress(QKeyEvent *event);
    void on_mouseDoubleClick(QPoint point);
    void on_mouseClicked(QPoint point);

    void on_action_Rectangle_triggered();

    void on_action_Ellipse_triggered();

    void on_action_Circle_triggered();

    void on_action_Triangle_triggered();

    void on_action_SingleLine_triggered();

    void on_action_Polyline_triggered();

    void on_action_Trapezium_triggered();

    void on_action_Text_triggered();

    void on_action_SetColor_triggered();

    void on_action_SetFont_triggered();

    void on_action_SetFrameSize_triggered();

    void on_action_SetLineWidth_triggered();

signals:
    void setPaintLineEvent(bool);

private slots:
    void on_action_CheckArea_triggered(bool checked);

    void on_action_SingleLine_triggered(bool checked);

private:
    Ui::DrawMainWindow *ui;

    QColor m_Color = Qt::black;
    QFont m_Font;
    int m_FrameSize=5;
    int m_LineWidth=10;
};

#endif // DRAWMAINWINDOW_H
