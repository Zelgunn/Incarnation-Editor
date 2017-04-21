#include "roomview.h"

RoomView::RoomView(QWidget *parent)
    : QGraphicsView(parent)
{
    m_scene = new RoomScene;
    setScene(m_scene);
    setAcceptDrops(true);
}

RoomView::RoomView(RoomScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    m_scene = scene;
    setScene(m_scene);
    setAcceptDrops(true);
}

void RoomView::loadRoom(const QWeakPointer<Room> &room)
{
    m_scene->loadRoom(room);
    m_scene->setScale(50);
}

RoomScene *RoomView::scene() const
{
    return m_scene;
}
