#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "loginmediator.h"

#include "IViewComponent.h"

namespace Ui {
class LoginDialog;
}

class LoginMediator;

class LoginDialog : public QDialog, public IViewComponent
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void update(IUpdateData *updateData);


private slots:
    void on_loginButton_clicked();

private:
    Ui::LoginDialog *ui;
    LoginMediator *loginMediator;

};

#endif // LOGINDIALOG_H
