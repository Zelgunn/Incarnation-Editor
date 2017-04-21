#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QMainWindow>

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomWindow(QWidget *parent = 0);
    ~RoomWindow();

private:
    Ui::RoomWindow *ui;
};

#endif // ROOMWINDOW_H
