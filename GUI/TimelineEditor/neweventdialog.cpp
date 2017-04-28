#include "neweventdialog.h"
#include "ui_neweventdialog.h"

NewEventDialog::NewEventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEventDialog)
{
    ui->setupUi(this);
}

NewEventDialog::~NewEventDialog()
{
    delete ui;
}

QString NewEventDialog::eventName() const
{
    return ui->nameLineEdit->text();
}

int NewEventDialog::start() const
{
    return ui->startMinSpinBox->value() * 60 + ui->startSecSpinBox->value();
}

int NewEventDialog::duration() const
{
    if(! ui->durationCheckBox->isChecked()) return -1;
    return ui->durationMinSpinBox->value() * 60 + ui->durationSecSpinBox->value();
}

int NewEventDialog::period() const
{
    if(! ui->periodCheckBox->isChecked()) return -1;
    return ui->periodMinSpinBox->value() * 60 + ui->periodSecSpinBox->value();
}

QColor NewEventDialog::color() const
{
    return ui->colorWidget->color();
}

void NewEventDialog::setColor(const QColor &color)
{
    ui->colorWidget->setColor(color);
}

void NewEventDialog::checkSecSpinBox(QSpinBox *secSpinBox, QSpinBox *minSpinBox)
{
    int secs = secSpinBox->value();
    int mins = secs / 60;
    secs = secs % 60;

    if(mins > 0)
    {
        minSpinBox->setValue(minSpinBox->value() + mins);
        secSpinBox->setValue(secs);
    }
}

void NewEventDialog::checkPeriodMinimum()
{
    ui->periodMinSpinBox->setMinimum(ui->durationMinSpinBox->value());

    if(ui->periodMinSpinBox->value() > ui->durationMinSpinBox->value())
    {
        ui->periodSecSpinBox->setMinimum(0);
    }
    else
    {
        ui->periodSecSpinBox->setMinimum(ui->durationSecSpinBox->value());
    }
}

void NewEventDialog::updatePeriodDurationDelta()
{
    int durationSecs = duration();
    int periodSecs = period();
    int deltaSecs = periodSecs - durationSecs;
    int deltaMins = deltaSecs / 60;
    deltaSecs %= 60;

    ui->deltaMinSpinBox->setValue(deltaMins);
    ui->deltaSecSpinBox->setValue(deltaSecs);
}

void NewEventDialog::updatePeriodFromDelta()
{
    int deltaSecs = ui->deltaMinSpinBox->value() * 60 + ui->deltaSecSpinBox->value();
    int periodSecs = duration() + deltaSecs;
    int periodMins = periodSecs / 60;
    periodSecs %= 60;
    ui->periodMinSpinBox->setValue(periodMins);
    ui->periodSecSpinBox->setValue(periodSecs);
}

void NewEventDialog::on_durationCheckBox_toggled(bool checked)
{
    ui->periodCheckBox->setEnabled(checked);
    ui->durationMinSpinBox->setEnabled(checked);
    ui->durationSecSpinBox->setEnabled(checked);

    if(!checked)
    {
        ui->periodCheckBox->setChecked(false);
    }
}

void NewEventDialog::on_periodCheckBox_toggled(bool checked)
{
    ui->periodMinSpinBox->setEnabled(checked);
    ui->periodSecSpinBox->setEnabled(checked);
    ui->deltaLabel->setEnabled(checked);
    ui->deltaMinSpinBox->setEnabled(checked);
    ui->deltaSecSpinBox->setEnabled(checked);
}

void NewEventDialog::on_startSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->startSecSpinBox, ui->startMinSpinBox);
}

void NewEventDialog::on_durationSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->durationSecSpinBox, ui->durationMinSpinBox);

    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void NewEventDialog::on_periodSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->periodSecSpinBox, ui->periodMinSpinBox);

    updatePeriodDurationDelta();
}

void NewEventDialog::on_durationMinSpinBox_editingFinished()
{
    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void NewEventDialog::on_periodMinSpinBox_editingFinished()
{
    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void NewEventDialog::on_deltaMinSpinBox_editingFinished()
{
    updatePeriodFromDelta();
}

void NewEventDialog::on_deltaSecSpinBox_editingFinished()
{
    updatePeriodFromDelta();
}
