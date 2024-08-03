#ifndef CHANGEPWDDIALOG_H
#define CHANGEPWDDIALOG_H

#include <QDialog>

#include "Interface/IViewComponent.h"
#include "usermediator.h"
#include "userinfo.h"

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
    UserMediator *userMediator;

    UserInfo userInfo;

};

#endif // CHANGEPWDDIALOG_H
