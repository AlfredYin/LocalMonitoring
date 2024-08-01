#ifndef CHANGEPWDDIALOG_H
#define CHANGEPWDDIALOG_H

#include <QDialog>

#include "Interface/IViewComponent.h"
#include "LoginMediator.h"

namespace Ui {
class ChangePwdDialog;
}

class ChangePwdDialog : public QDialog, public IViewComponent
{
    Q_OBJECT

public:
    explicit ChangePwdDialog(QWidget *parent = nullptr);
    ~ChangePwdDialog();

    void update(IUpdateData *updateData);

private slots:
    void on_loginButton_clicked();

private:
    Ui::ChangePwdDialog *ui;
    LoginMediator *loginMediator;

};

#endif // CHANGEPWDDIALOG_H
