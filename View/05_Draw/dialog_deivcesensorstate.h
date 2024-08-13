#ifndef DIALOG_DEIVCESENSORSTATE_H
#define DIALOG_DEIVCESENSORSTATE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColorDialog>
#include <QFontDialog>
#include <QPointF>
#include <QDialog>

#include "devicestateinfo.h"

namespace Ui {
class Dialog_DeivceSensorState;
}

class Dialog_DeivceSensorState : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_DeivceSensorState(QWidget *parent = nullptr);
    explicit Dialog_DeivceSensorState(DeviceStateInfo deivceStateInfo,QWidget *parent = nullptr);
    ~Dialog_DeivceSensorState();

private:
    Ui::Dialog_DeivceSensorState *ui;
    DeviceStateInfo m_DeivceStateInfo;

    QGraphicsScene *scene;
};

#endif // DIALOG_DEIVCESENSORSTATE_H
