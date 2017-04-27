#include "structurewindow.h"
#include "ui_structurewindow.h"

StructureWindow::StructureWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StructureWindow)
{
    ui->setupUi(this);

    m_pointerStatusLabel = new QLabel();
    ui->statusbar->addWidget(m_pointerStatusLabel);
    m_pointerStatusLabel->setFixedSize(100, 25);
    m_pointerStatusLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_pointerStatusLabel->setAlignment(Qt::AlignCenter);

    ui->roomWidthSpinBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->roomHeightSpinBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

    //ui->roomInfoDockWidget->close();

    connect(ui->graphicsView->scene(), &StructureScene::selectionChanged, this, &StructureWindow::setSelectedRoom);
    connect(ui->graphicsView->scene(), &StructureScene::sceneGeometryChanged, this, &StructureWindow::updateFromView);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &StructureWindow::timedUpdate);
    m_timer->start(20);

    m_slowTimer = new QTimer(this);
    connect(m_slowTimer, &QTimer::timeout, this, &StructureWindow::slowUpdate);
    m_slowTimer->start(80);
}

StructureWindow::~StructureWindow()
{
    delete ui;
}

void StructureWindow::setUpProject(Project *project)
{
    if(project == Q_NULLPTR)
    {
        project = Project::activeProject();
    }

    ui->graphicsView->setUpProject(project);
}

void StructureWindow::unloadProject()
{
    ui->graphicsView->unloadProject();
}

QPixmap StructureWindow::renderSelectedRoom() const
{
    return ui->graphicsView->scene()->renderSelectedRoom();
}

void StructureWindow::updateFromGUI()
{
    if(m_blockGUIUpdate)
    {
        return;
    }

    qDebug() << "updateFrom : GUI";

    m_selectedRoom.data()->setName(ui->roomNameLineEdit->text());
    QSizeF size(ui->roomWidthSpinBox->value(), ui->roomHeightSpinBox->value());
    m_selectedRoom.data()->setSize(size);

    updateView();
}

void StructureWindow::updateFromView()
{
    if(m_blockViewUpdate)
    {
        return;
    }

    QList<RoomMarker *> markers = ui->graphicsView->scene()->roomMarkers();
    for(int i = 0; i < markers.length(); i++)
    {
        RoomMarker *marker = markers[i];
        QWeakPointer<Room> room = marker->getRoomData();
        room.data()->setPosition(marker->pos().x());
        room.data()->setSize(marker->getSize());
    }

    qDebug() << "updateFrom : View";

    updateGUI();
}

void StructureWindow::updateFromProjectData()
{
    qDebug() << "updateFrom : ProjectData";

    updateGUI();
    updateView();
}

void StructureWindow::updateGUI()
{
    m_blockGUIUpdate = true;

    if(!m_selectedRoom.isNull())
    {
        ui->roomNameLineEdit->setText(m_selectedRoom.data()->getName());

        QList<RoomMarker *> markers = ui->graphicsView->scene()->roomMarkers();

        for(int i = 0; i < markers.length(); i++)
        {
            if(markers[i]->getRoomData() == m_selectedRoom)
            {
                ui->roomNumberSpinBox->setValue(i);
                break;
            }
        }

        QSizeF roomSize(m_selectedRoom.data()->getSize());
        ui->roomHeightSpinBox->setValue(roomSize.height());
        ui->roomWidthSpinBox->setValue(roomSize.width());

        //ui->roomInfoDockWidget->show();
    }

    m_blockGUIUpdate = false;
}

void StructureWindow::updateView()
{
    m_blockViewUpdate = true;

    ui->graphicsView->scene()->updateMarkers();

    m_blockViewUpdate = false;
}

void StructureWindow::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);

    if(event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

void StructureWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
}

void StructureWindow::timedUpdate()
{
    if(!isVisible())
    {
        return;
    }

    ui->graphicsView->manualUpdate();

}

void StructureWindow::slowUpdate()
{
    if(!isVisible())
    {
        return;
    }

    m_pointerStatusLabel->setText(QString("%1, %2")
                                  .arg(ui->graphicsView->cursorPosition().x())
                                  .arg(ui->graphicsView->cursorPosition().y())
                                  );
}

void StructureWindow::setSelectedRoom(RoomMarker *marker)
{
    QList<QWeakPointer<Room>> rooms = Project::activeProject()->getRooms();
    QWeakPointer<Room> selectedRoom = Q_NULLPTR;

    for(int i = 0; i < rooms.length(); i++)
    {
        if(rooms[i] == marker->getRoomData())
        {
            selectedRoom = rooms[i];
            break;
        }
    }

    Q_ASSERT_X(selectedRoom != Q_NULLPTR, "StructureWindow::setSelectedRoom", "No Room linked to given marker");
    m_selectedRoom = selectedRoom;
    updateGUI();
}

void StructureWindow::on_roomNameLineEdit_editingFinished()
{
    updateFromGUI();
}

void StructureWindow::on_roomNumberSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    updateFromGUI();
}

void StructureWindow::on_roomWidthSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateFromGUI();
}

void StructureWindow::on_roomHeightSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    updateFromGUI();
}

void StructureWindow::on_actionNew_room_triggered()
{
    CreateRoomDialog *createRoomDialog = new CreateRoomDialog(this);
    int result = createRoomDialog->exec();
    if(result == QDialog::Rejected)
    {
        return;
    }

    Room roomValues = createRoomDialog->getRoomValues();
    QWeakPointer<Room> roomPtr = Project::activeProject()->addRoom(roomValues);

    RoomMarker *mostRightMarker = ui->graphicsView->scene()->roomMarkers().last();
    roomPtr.data()->setPosition(mostRightMarker->pos().x() + mostRightMarker->getSize().width() / 2);

    UserAction::addAction(new RoomCreationAction(roomPtr.data()->getId()));
    updateFromProjectData();
}

void StructureWindow::on_actiondeleteRoom_triggered()
{
    if(m_selectedRoom.isNull())
    {
        return;
    }

    UserAction::addAction(new RoomDeletionAction(m_selectedRoom.data()->getId()));
    Project::activeProject()->removeRoom(m_selectedRoom);
    updateFromProjectData();
}

void StructureWindow::on_actionEditRoom_triggered()
{
    if(m_selectedRoom.isNull())
    {
        return;
    }

    emit roomEditionModeTriggered(m_selectedRoom);
}
