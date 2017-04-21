#include "roomdeletionaction.h"

RoomDeletionAction::RoomDeletionAction(int roomId)
{
    m_roomId = roomId;
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    m_roomCopy = Room(*room.data());
}

void RoomDeletionAction::revert()
{
    Project::activeProject()->addRoom(m_roomCopy);
}

void RoomDeletionAction::restore()
{
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    Project::activeProject()->removeRoom(room);
}
