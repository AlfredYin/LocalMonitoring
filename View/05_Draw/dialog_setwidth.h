#ifndef DIALOG_SETWIDTH_H
#define DIALOG_SETWIDTH_H

#include <QDialog>

namespace Ui {
class Dialog_SetWidth;
}

class Dialog_SetWidth : public QDialog
{
    Q_OBJECT

public:
    Dialog_SetWidth(QWidget *parent = nullptr);
    Dialog_SetWidth(int size,QWidget *parent = nullptr);

    int getWidth();

    ~Dialog_SetWidth();

private:
    Ui::Dialog_SetWidth *ui;

    int m_Size;
};

#endif // DIALOG_SETWIDTH_H
