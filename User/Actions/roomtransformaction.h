#ifndef ROOMTRANSFORMACTION_H
#define ROOMTRANSFORMACTION_H

#include <QPointF>

#include "User/useraction.h"
#include "Projects/room.h"
#include "Projects/project.h"

class RoomMarker;

class RoomTransformAction : public UserAction
{
public:
    RoomTransformAction(int roomId, QPointF delta);
    void revert();
    void restore();

private:
    int m_roomId;
    QPointF m_delta;

};

#endif // ROOMTRANSFORMACTION_H
