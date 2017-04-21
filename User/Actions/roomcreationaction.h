#ifndef ROOMCREATIONACTION_H
#define ROOMCREATIONACTION_H

#include "User/useraction.h"
#include "Projects/room.h"
#include "Projects/project.h"

class RoomCreationAction : public UserAction
{
public:
    RoomCreationAction(int roomId);
    void revert();
    void restore();

private:
    int m_roomId;
    Room m_roomCopy = Room("");
};

#endif // ROOMCREATIONACTION_H
