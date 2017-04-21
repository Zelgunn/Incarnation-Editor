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

private:
    Ui::CreateRoomDialog *ui;
};

#endif // CREATEROOMDIALOG_H
