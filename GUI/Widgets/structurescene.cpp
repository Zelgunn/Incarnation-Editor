#include "structurescene.h"

StructureScene::StructureScene(QObject *parent):
    QGraphicsScene(parent)
{

}

StructureScene::StructureScene(const QRectF &sceneRect, QObject *parent):
    QGraphicsScene(sceneRect, parent)

{

}

StructureScene::StructureScene(qreal x, qreal y, qreal width, qreal height, QObject *parent):
    QGraphicsScene(x, y, width, height, parent)
{

}

void StructureScene::setUpProject(Project *project)
{
    if(project == Q_NULLPTR)
    {
        project = Project::activeProject();
    }

    QList<QWeakPointer<Room> > rooms = project->getRooms();
    for(int i = 0; i < rooms.length(); i++)
    {
        addRoomMarker(new RoomMarker(rooms[i]));
    }
}

void StructureScene::addRoomMarker(RoomMarker *marker)
{
    addItem(marker);
    m_roomMarkers.append(marker);
    connect(marker, &RoomMarker::selected, this, &StructureScene::roomMarkerSelected);
    connect(marker, &RoomMarker::geometryChanged, this, &StructureScene::emitSceneGeometryChanged);
}

void StructureScene::removeRoomMarker(RoomMarker *marker)
{
    removeItem(marker);
    m_roomMarkers.removeAll(marker);
    disconnect(marker, &RoomMarker::selected, this, &StructureScene::roomMarkerSelected);
    disconnect(marker, &RoomMarker::geometryChanged, this, &StructureScene::emitSceneGeometryChanged);
    delete marker;
}

void StructureScene::createRoomMarker(QWeakPointer<Room> room, bool appendAtEnd)
{
    if(appendAtEnd)
    {
        if(m_roomMarkers.empty())
        {
            room.data()->setPosition(QPointF(0,0));
        }
        else
        {
            RoomMarker *mostRightMarker = m_roomMarkers.last();
            room.data()->setPosition(mostRightMarker->pos() + QPointF(mostRightMarker->getSize().width() / 2, 0));
        }
    }

    addRoomMarker(new RoomMarker(room));
}

void StructureScene::updateMarkers()
{
    // Remove invalid markers
    QList<QWeakPointer<Room> > foundRooms;
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        if(m_roomMarkers[i]->getRoomData().isNull())
        {
            removeRoomMarker(m_roomMarkers[i]);
            i--;
        }
        else
        {
            foundRooms.append(m_roomMarkers[i]->getRoomData());
        }
    }

    // Add missing markers
    QList<QWeakPointer<Room> > allRooms = Project::activeProject()->getRooms();
    for(int i = 0; i < allRooms.length(); i++)
    {
        if(!foundRooms.contains(allRooms[i]))
        {
            createRoomMarker(allRooms[i], false);
        }
    }

    // Update existing markers
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        RoomMarker *marker = m_roomMarkers[i];
        QWeakPointer<Room> room = marker->getRoomData();

        marker->setPos(room.data()->getPosition());
        marker->setSize(room.data()->getSize());
    }
}

void StructureScene::unloadProject()
{
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        disconnect(m_roomMarkers[i], &RoomMarker::selected, this, &StructureScene::roomMarkerSelected);
        disconnect(m_roomMarkers[i], &RoomMarker::geometryChanged, this, &StructureScene::emitSceneGeometryChanged);
        delete m_roomMarkers[i];
    }
    m_roomMarkers.clear();
}

void StructureScene::update(const QRectF &rect)
{
    QGraphicsScene::update(rect);

    updateZValues();
    updateMarkersProjection();
}

void StructureScene::update(qreal x, qreal y, qreal w, qreal h)
{
    QGraphicsScene::update(QRectF(x, y, w, h));
}

void StructureScene::updateZValues()
{
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        if(m_roomMarkers[i]->isSelected())
        {
            m_roomMarkers[i]->setZValue(1);
        }
        else
        {
            m_roomMarkers[i]->setZValue(0);
        }
    }
}

void StructureScene::updateMarkersProjection()
{
    qreal totalWidth = 0;
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        totalWidth += m_roomMarkers[i]->getViewSize().width();
    }

    std::sort(m_roomMarkers.begin(), m_roomMarkers.end(), RoomMarker::compareXPos);

    qreal x = - totalWidth / 2;
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        RoomMarker *marker = m_roomMarkers[i];
        x += marker->getViewSize().width() / 2;
        if(marker->isMoving())
        {
            marker->setProjectedPosition(x, 0);
        }
        else
        {
            marker->setPos(x, 0);
        }
        x += marker->getViewSize().width() / 2;

        m_roomMarkers[i]->manualUpdate();
    }
}

void StructureScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    emit cursorPositionChanged(event);
}

void StructureScene::roomMarkerSelected(RoomMarker *roomMarker)
{
    if(roomMarker == m_selectedRoomMarker)
    {
        return;
    }

    m_selectedRoomMarker = roomMarker;
    for(int i = 0; i < m_roomMarkers.length(); i++)
    {
        m_roomMarkers[i]->setSelected(roomMarker == m_roomMarkers[i]);
    }

    emit selectionChanged(roomMarker);
}

void StructureScene::emitSceneGeometryChanged()
{
    emit sceneGeometryChanged();
}

QList<RoomMarker *> StructureScene::roomMarkers() const
{
    return m_roomMarkers;
}
