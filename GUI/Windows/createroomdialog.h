#ifndef CREATEROOMDIALOG_H
#define CREATEROOMDIALOG_H

#include <QDialog>

#include "Projects/room.h"

namespace Ui {
class CreateRoomDialog;
}

class CreateRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRoomDialog(QWidget *parent = 0);
    ~CreateRoomDialog();

    Room getRoomValues() const;

protected:
    void updateLayoutFromClass();

private slots:
    void on_roomClassComboBox_currentIndexChanged(int index);

private:
    Ui::CreateRoomDialog *ui;
};

#endif // CREATEROOMDIALOG_H
