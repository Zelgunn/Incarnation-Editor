#ifndef ROOMWINDOW_H
#define ROOMWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "Projects/project.h"
#include "Projects/asset.h"
#include "Projects/room.h"

namespace Ui {
class RoomWindow;
}

class RoomWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RoomWindow(QWidget *parent = 0);
    ~RoomWindow();

    void loadRoom(const QWeakPointer<Room> &room);
    void updateFromProjectData();

protected slots:
    void manualUpdate();

private:
    Ui::RoomWindow *ui;
    QTimer *m_timer;
};

#endif // ROOMWINDOW_H
