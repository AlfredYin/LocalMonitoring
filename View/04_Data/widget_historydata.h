#ifndef WIDGET_HISTORYDATA_H
#define WIDGET_HISTORYDATA_H

#include <QtDebug>
#include <QWidget>
#include <QMessageBox>
#include "IViewComponent.h"
#include "historydatamediator.h"

namespace Ui {
class Widget_HistoryData;
}

class Widget_HistoryData : public QWidget, public IViewComponent
{
    Q_OBJECT

public:
    explicit Widget_HistoryData(QWidget *parent = nullptr);
    ~Widget_HistoryData();

    void update(IUpdateData *updateData);

private slots:
    void on_pushButton_RefreshHistoryData_clicked();

private:
    Ui::Widget_HistoryData *ui;

    HistoryDataMediator *historyDataMediator;
};

#endif // WIDGET_HISTORYDATA_H
