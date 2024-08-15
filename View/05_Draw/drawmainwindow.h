#ifndef DRAWMAINWINDOW_H
#define DRAWMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColorDialog>
#include <QFontDialog>
#include <QPointF>

#include "alfredgraphicsscene.h"
#include "singlelineitem.h"
#include "dialog_setwidth.h"

namespace Ui {
class DrawMainWindow;
}

class DrawMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel *label_ItemInfo;
    AlfredGraphicsScene *scene;

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
    void on_mouseRightClicked(QPoint point);

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

private slots:
    void on_action_CheckArea_triggered(bool checked);

    void on_action_SingleLine_triggered(bool checked);

    void on_action_Polyline_triggered(bool checked);

    void on_action_SetGradient_triggered();

    void on_action_ZoomIn_triggered();

    void on_action_ZoomOut_triggered();

    void on_action_Restore_triggered();

    void on_action_SpinLeft_triggered();

    void on_action_SpinRight_triggered();

    void on_action_Front_triggered();

    void on_action_Back_triggered();

    void on_action_Group_triggered();

    void on_action_Delete_triggered();

    void on_action_GroupBreak_triggered();

    void on_action_AddDeviceModel_triggered();

    void on_action_SaveOtherFile_triggered();

    void on_action_OpenFile_triggered();

    QString getSaveFilePath(QWidget *parent = nullptr);

    QString getOpenFilePath(QWidget *parent = nullptr);

    void on_action_OpenOtherFile_triggered();

    void on_action_Copy_triggered();

    void on_action_Paste_triggered();

    void on_action_Cut_triggered();

    void on_action_SaveFileXml_triggered();

    void on_action_SaveFileJson_triggered();

    void on_action_RectangleFree_triggered(bool checked);

    void on_action_EllipseFree_triggered(bool checked);

    void on_action_CircleFree_triggered(bool checked);

private:
    Ui::DrawMainWindow *ui;

    QColor m_Color =  QColor(173, 216, 230);
    QFont m_Font;
    int m_FrameSize=5;
    int m_LineWidth=10;
};

#endif // DRAWMAINWINDOW_H
