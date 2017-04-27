#ifndef STRUCTUREWINDOW_H
#define STRUCTUREWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QLabel>

#include "Projects/room.h"
#include "structureview.h"
#include "Projects/project.h"
#include "createroomdialog.h"
#include "User/Actions/roomcreationaction.h"
#include "User/Actions/roomdeletionaction.h"

namespace Ui {
class StructureWindow;
}

class StructureWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StructureWindow(QWidget *parent = 0);
    ~StructureWindow();

    void setUpProject(Project *project = Q_NULLPTR);
    void unloadProject();
    QPixmap renderSelectedRoom() const;

public slots:
    void updateFromGUI();
    void updateFromView();
    void updateFromProjectData();
    void updateGUI();
    void updateView();

signals:
    void roomEditionModeTriggered(const QWeakPointer<Room> &room);

protected:
    void changeEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

protected slots:
    void timedUpdate();
    void slowUpdate();
    void setSelectedRoom(RoomMarker *marker);

private slots:
    void on_roomNameLineEdit_editingFinished();
    void on_roomNumberSpinBox_valueChanged(int arg1);
    void on_roomWidthSpinBox_valueChanged(double arg1);
    void on_roomHeightSpinBox_valueChanged(double arg1);

    void on_actionNew_room_triggered();
    void on_actiondeleteRoom_triggered();
    void on_actionEditRoom_triggered();

private:
    Ui::StructureWindow *ui;
    QTimer *m_timer;
    QTimer *m_slowTimer;
    QLabel *m_pointerStatusLabel;

    QWeakPointer<Room> m_selectedRoom;
    bool m_blockViewUpdate = false;
    bool m_blockGUIUpdate = false;
};

#endif // STRUCTUREWINDOW_H
