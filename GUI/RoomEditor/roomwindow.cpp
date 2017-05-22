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

    m_slowTimer = new QTimer();
    connect(m_slowTimer, &QTimer::timeout, this, &RoomWindow::slowUpdate);
    m_slowTimer->start(100);

    ui->listWidget->clear();
    QList<AssetModel> assetModelsDatabase = Project::assetModelsDatabase();
    for(int i = 0; i < assetModelsDatabase.length(); i++)
    {
        AssetModel assetModel = assetModelsDatabase[i];
        QIcon assetIcon(assetModel.iconPath());
        new QListWidgetItem(assetIcon, assetModel.name(), ui->listWidget);
    }
}

RoomWindow::~RoomWindow()
{
    delete ui;
}

void RoomWindow::loadRoom(const QWeakPointer<Room> &room, const QPixmap &roomRender)
{
    ui->graphicsView->loadRoom(room, roomRender);
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
    ui->graphicsView->manualUpdate();
}

void RoomWindow::slowUpdate()
{
    if(!isVisible())
    {
        return;
    }

    ui->graphicsView->scene()->update(ui->graphicsView->sceneRect());
}
