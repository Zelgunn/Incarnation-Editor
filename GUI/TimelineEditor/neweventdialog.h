#ifndef NEWEVENTDIALOG_H
#define NEWEVENTDIALOG_H

#include <QDialog>
#include <QSpinBox>

#include "colorwidget.h"

#include <QDebug>

namespace Ui {
class NewEventDialog;
}

class NewEventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewEventDialog(QWidget *parent = 0);
    ~NewEventDialog();

    QString eventName() const;
    int start() const;
    int duration() const;
    int period() const;
    QColor color() const;
    void setColor(const QColor &color);

protected:
    void checkSecSpinBox(QSpinBox *secSpinBox, QSpinBox *minSpinBox);
    void checkPeriodMinimum();
    void updatePeriodDurationDelta();
    void updatePeriodFromDelta();

private slots:
    void on_durationCheckBox_toggled(bool checked);
    void on_periodCheckBox_toggled(bool checked);
    void on_startSecSpinBox_editingFinished();
    void on_durationSecSpinBox_editingFinished();
    void on_periodSecSpinBox_editingFinished();
    void on_durationMinSpinBox_editingFinished();
    void on_periodMinSpinBox_editingFinished();
    void on_deltaMinSpinBox_editingFinished();
    void on_deltaSecSpinBox_editingFinished();

private:
    Ui::NewEventDialog *ui;
};

#endif // NEWEVENTDIALOG_H
