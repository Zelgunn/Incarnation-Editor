#ifndef ROOMHANDLETRANSFORMACTION_H
#define ROOMHANDLETRANSFORMACTION_H

#include "User/useraction.h"
#include "GUI/StructureEditor/handle.h"

class Handle;

class RoomHandleTransformAction : public UserAction
{
public:
    RoomHandleTransformAction(Handle *handle, QPointF delta);
    void revert();
    void restore();

private:
    Handle* m_handle;
    QPointF m_delta;
};

#endif // ROOMHANDLETRANSFORMACTION_H
