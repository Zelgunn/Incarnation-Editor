#include "createroomdialog.h"
#include "ui_createroomdialog.h"

CreateRoomDialog::CreateRoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRoomDialog)
{
    ui->setupUi(this);
}

CreateRoomDialog::~CreateRoomDialog()
{
    delete ui;
}
