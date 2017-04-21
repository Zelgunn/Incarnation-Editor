#include "roomcreationaction.h"

RoomCreationAction::RoomCreationAction(int roomId)
{
    m_roomId = roomId;
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    m_roomCopy = Room(*room.data());
}

void RoomCreationAction::revert()
{
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    Project::activeProject()->removeRoom(room);
}

void RoomCreationAction::restore()
{
    Project::activeProject()->addRoom(m_roomCopy);
}
