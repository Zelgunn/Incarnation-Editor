#include "timelinewindow.h"
#include "ui_timelinewindow.h"

TimelineWindow::TimelineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimelineWindow)
{
    ui->setupUi(this);
    m_timer = new QTimer;
    connect(m_timer, &QTimer::timeout, this, &TimelineWindow::manualUpdate);
    m_timer->start(16);
}

TimelineWindow::~TimelineWindow()
{
    delete ui;
}

void TimelineWindow::manualUpdate()
{
    if(!isVisible())
    {
        return;
    }

    ui->graphicsView->manualUpdate();
}

void TimelineWindow::on_actionNew_event_triggered()
{
    NewEventDialog newEventDialog;
    QColor eventColor = QColor::fromHsv(m_nextEventColorHue, 255, 255);
    newEventDialog.setColor(eventColor);

    int dialogAnswer = newEventDialog.exec();

    if(dialogAnswer == QDialog::Rejected)
    {
        return;
    }

    eventColor = newEventDialog.color();
    m_nextEventColorHue = eventColor.hsvHue() + 45;
    if(m_nextEventColorHue >= 360) m_nextEventColorHue -= 360;

    Event *newEvent = new Event(newEventDialog.eventName(),
                                newEventDialog.start(),
                                newEventDialog.duration(),
                                newEventDialog.period());
    newEvent->setColor(eventColor);

    Project::activeProject()->addEvent(newEvent);
}
