#ifndef TIMELINEWINDOW_H
#define TIMELINEWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "timelineview.h"
#include "eventdialog.h"

namespace Ui {
class TimelineWindow;
}

class TimelineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimelineWindow(QWidget *parent = 0);
    ~TimelineWindow();

public slots:
    void manualUpdate();

private slots:
    void on_actionNew_event_triggered();

private:
    Ui::TimelineWindow *ui;
    QTimer *m_timer;

    qreal m_nextEventColorHue = 0;
};

#endif // TIMELINEWINDOW_H
