#include "roomwindow.h"
#include "ui_roomwindow.h"

RoomWindow::RoomWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RoomWindow)
{
    ui->setupUi(this);

    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &RoomWindow::manualUpdate);
    m_timer->start(16);

    ui->listWidget->clear();
    QList<QWeakPointer<Asset> > assetDatabase = Project::assetDatabase();
    for(int i = 0; i < assetDatabase.length(); i++)
    {
        QWeakPointer<Asset> asset = assetDatabase[i];
        QIcon assetIcon(asset.data()->iconPath());
        new QListWidgetItem(assetIcon, asset.data()->name(), ui->listWidget);
    }
}

RoomWindow::~RoomWindow()
{
    delete ui;
}

void RoomWindow::loadRoom(const QWeakPointer<Room> &room)
{
    ui->graphicsView->loadRoom(room);
}

void RoomWindow::updateFromProjectData()
{
    ui->graphicsView->scene()->updateMarkers();
}

void RoomWindow::manualUpdate()
{
    if(!isVisible())
    {
        return;
    }

    ui->listWidget->sortItems();
}
