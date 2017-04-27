#include "timelinewindow.h"
#include "ui_timelinewindow.h"

TimelineWindow::TimelineWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimelineWindow)
{
    ui->setupUi(this);
}

TimelineWindow::~TimelineWindow()
{
    delete ui;
}
