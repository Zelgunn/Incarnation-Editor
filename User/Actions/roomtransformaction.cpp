#include "roomtransformaction.h"

RoomTransformAction::RoomTransformAction(int roomId, qreal delta)
{
    m_roomId = roomId;
    m_delta = delta;
}

void RoomTransformAction::revert()
{
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    room.data()->moveBy(-m_delta);
}

void RoomTransformAction::restore()
{
    QWeakPointer<Room> room = Project::activeProject()->getRoomWithID(m_roomId);
    room.data()->moveBy(m_delta);
}
