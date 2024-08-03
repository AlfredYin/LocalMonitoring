#ifndef WIDGET_HOMEPAGE_H
#define WIDGET_HOMEPAGE_H

#include "IViewComponent.h"
#include "mainwindowmediator.h"
#include "logindialog.h"
#include <QWidget>

namespace Ui {
class Widget_HomePage;
}

class Widget_HomePage : public QWidget, public IViewComponent
{
    Q_OBJECT

public:
    explicit Widget_HomePage(QWidget *parent = nullptr);
    ~Widget_HomePage();

    void update(IUpdateData *updateData);

private slots:
    void on_pushButtonLogin_clicked();

    void on_pushButtonChangePassword_clicked();

private:
    MainWindowMediator *mainWindowMediator;

    LoginDialog *loginDialog=nullptr;
//    QPointer<QDialog> loginDialog;
//    QPointer<LoginDialog> loginDialog;
    QDialog *changePwdDialog=nullptr;

    int m_Count=0;

    Ui::Widget_HomePage *ui;
};

#endif // WIDGET_HOMEPAGE_H
