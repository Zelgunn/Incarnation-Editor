#ifndef ROOMDELETIONACTION_H
#define ROOMDELETIONACTION_H

#include "User/useraction.h"
#include "Projects/room.h"
#include "Projects/project.h"

class RoomDeletionAction : public UserAction
{
public:
    RoomDeletionAction(int roomId);
    void revert();
    void restore();

private:
    int m_roomId;
    Room m_roomCopy = Room("");
};

#endif // ROOMDELETIONACTION_H
