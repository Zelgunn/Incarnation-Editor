#include "createroomdialog.h"
#include "ui_createroomdialog.h"

CreateRoomDialog::CreateRoomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRoomDialog)
{
    ui->setupUi(this);
    updateLayoutFromClass();
}

CreateRoomDialog::~CreateRoomDialog()
{
    delete ui;
}

Room CreateRoomDialog::getRoomValues() const
{
    QString name = ui->nameLineEdit->text();
    QSizeF size(ui->widthSpinBox->value(), ui->heightSpinBox->value());
    Room room(name, size);
    if(ui->roomClassComboBox->currentIndex() == 1)
    {
        QSizeF pitDim(ui->pitLengthSpinBox->value(), ui->pitDepthSpinBox->value());
        room.setPitDim(pitDim);
    }
    return room;
}

void CreateRoomDialog::updateLayoutFromClass()
{
    ui->pitParametersGroupBox->setVisible(ui->roomClassComboBox->currentIndex() == 1);
}

void CreateRoomDialog::on_roomClassComboBox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    updateLayoutFromClass();
}
