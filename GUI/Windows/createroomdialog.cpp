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

Room CreateRoomDialog::getRoomValues() const
{
    QString name = ui->nameLineEdit->text();
    QSizeF size(ui->widthSpinBox->value(), ui->heightSpinBox->value());
    return Room(name, size);
}
