#ifndef TIMELINEWINDOW_H
#define TIMELINEWINDOW_H

#include <QMainWindow>

namespace Ui {
class TimelineWindow;
}

class TimelineWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimelineWindow(QWidget *parent = 0);
    ~TimelineWindow();

private:
    Ui::TimelineWindow *ui;
};

#endif // TIMELINEWINDOW_H
