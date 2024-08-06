#ifndef DRAWMAINWINDOW_H
#define DRAWMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class DrawMainWindow;
}

class DrawMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DrawMainWindow(QWidget *parent = nullptr);
    ~DrawMainWindow();

private:
    Ui::DrawMainWindow *ui;
};

#endif // DRAWMAINWINDOW_H
