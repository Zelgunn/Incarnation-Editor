#include "eventdialog.h"
#include "ui_eventdialog.h"

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog)
{
    ui->setupUi(this);
}

EventDialog::~EventDialog()
{
    delete ui;
}

int EventDialog::exec()
{
    return QDialog::exec();
}

int EventDialog::exec(const QWeakPointer<Event> &event)
{
    setWindowTitle(tr("Edit event"));
    ui->nameLineEdit->setText(event.data()->name());

    int start = (int)event.data()->start();
    ui->startMinSpinBox->setValue(start / 60);
    ui->startSecSpinBox->setValue(start % 60);

    int duration = (int)event.data()->duration();
    if(duration > 0)
    {
        ui->durationCheckBox->setChecked(true);
        ui->durationMinSpinBox->setValue(duration / 60);
        ui->durationSecSpinBox->setValue(duration % 60);

        int period = (int)event.data()->period();
        if(period > 0)
        {
            ui->periodCheckBox->setChecked(true);
            ui->periodMinSpinBox->setValue(period / 60);
            ui->periodSecSpinBox->setValue(period % 60);
        }
    }

    setColor(event.data()->color());

    return QDialog::exec();
}

QString EventDialog::eventName() const
{
    return ui->nameLineEdit->text();
}

int EventDialog::start() const
{
    return ui->startMinSpinBox->value() * 60 + ui->startSecSpinBox->value();
}

int EventDialog::duration() const
{
    if(! ui->durationCheckBox->isChecked()) return -1;
    return ui->durationMinSpinBox->value() * 60 + ui->durationSecSpinBox->value();
}

int EventDialog::period() const
{
    if(! ui->periodCheckBox->isChecked()) return -1;
    return ui->periodMinSpinBox->value() * 60 + ui->periodSecSpinBox->value();
}

QColor EventDialog::color() const
{
    return ui->colorWidget->color();
}

void EventDialog::setColor(const QColor &color)
{
    ui->colorWidget->setColor(color);
}

void EventDialog::checkSecSpinBox(QSpinBox *secSpinBox, QSpinBox *minSpinBox)
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

void EventDialog::checkPeriodMinimum()
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

void EventDialog::updatePeriodDurationDelta()
{
    int durationSecs = duration();
    int periodSecs = period();
    int deltaSecs = periodSecs - durationSecs;
    int deltaMins = deltaSecs / 60;
    deltaSecs %= 60;

    ui->deltaMinSpinBox->setValue(deltaMins);
    ui->deltaSecSpinBox->setValue(deltaSecs);
}

void EventDialog::updatePeriodFromDelta()
{
    int deltaSecs = ui->deltaMinSpinBox->value() * 60 + ui->deltaSecSpinBox->value();
    int periodSecs = duration() + deltaSecs;
    int periodMins = periodSecs / 60;
    periodSecs %= 60;
    ui->periodMinSpinBox->setValue(periodMins);
    ui->periodSecSpinBox->setValue(periodSecs);
}

void EventDialog::on_durationCheckBox_toggled(bool checked)
{
    ui->periodCheckBox->setEnabled(checked);
    ui->durationMinSpinBox->setEnabled(checked);
    ui->durationSecSpinBox->setEnabled(checked);

    if(!checked)
    {
        ui->periodCheckBox->setChecked(false);
    }
}

void EventDialog::on_periodCheckBox_toggled(bool checked)
{
    ui->periodMinSpinBox->setEnabled(checked);
    ui->periodSecSpinBox->setEnabled(checked);
    ui->deltaLabel->setEnabled(checked);
    ui->deltaMinSpinBox->setEnabled(checked);
    ui->deltaSecSpinBox->setEnabled(checked);
}

void EventDialog::on_startSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->startSecSpinBox, ui->startMinSpinBox);
}

void EventDialog::on_durationSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->durationSecSpinBox, ui->durationMinSpinBox);

    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void EventDialog::on_periodSecSpinBox_editingFinished()
{
    checkSecSpinBox(ui->periodSecSpinBox, ui->periodMinSpinBox);

    updatePeriodDurationDelta();
}

void EventDialog::on_durationMinSpinBox_editingFinished()
{
    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void EventDialog::on_periodMinSpinBox_editingFinished()
{
    checkPeriodMinimum();
    updatePeriodDurationDelta();
}

void EventDialog::on_deltaMinSpinBox_editingFinished()
{
    updatePeriodFromDelta();
}

void EventDialog::on_deltaSecSpinBox_editingFinished()
{
    updatePeriodFromDelta();
}
