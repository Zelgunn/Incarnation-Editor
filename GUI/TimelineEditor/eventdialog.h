#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QSpinBox>

#include "colorwidget.h"
#include "Projects/event.h"

#include <QDebug>

namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(QWidget *parent = 0);
    ~EventDialog();

    int exec();
    int exec(const QWeakPointer<Event> &event);

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
    Ui::EventDialog *ui;
};

#endif // EVENTDIALOG_H
