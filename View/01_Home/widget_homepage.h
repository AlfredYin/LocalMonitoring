#ifndef WIDGET_HOMEPAGE_H
#define WIDGET_HOMEPAGE_H

#include "IViewComponent.h"
#include "homemediator.h"
#include "logindialog.h"
#include <QWidget>
#include <QLabel>

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

    void updateTimeLabel();
    void on_pushButton_Draw_clicked();

private:
    HomeMediator *homeMediator;

    LoginDialog *loginDialog=nullptr;
//    QPointer<QDialog> loginDialog;
//    QPointer<LoginDialog> loginDialog;
    QDialog *changePwdDialog=nullptr;

    int m_Count=0;

    QTimer *time_Timer;

    Ui::Widget_HomePage *ui;
};

#endif // WIDGET_HOMEPAGE_H
