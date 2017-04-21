#include "roomhandletransformaction.h"

RoomHandleTransformAction::RoomHandleTransformAction(Handle *handle, QPointF delta)
{
    m_handle = handle;
    m_delta = delta;
}

void RoomHandleTransformAction::revert()
{
    m_handle->moveBy(-m_delta.x(), -m_delta.y());
}

void RoomHandleTransformAction::restore()
{
    m_handle->moveBy(m_delta.x(), m_delta.y());
}
