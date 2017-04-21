#ifndef ROOMVIEW_H
#define ROOMVIEW_H

#include <QGraphicsView>
#include <QPaintEvent>

#include "roomscene.h"

class RoomView : public QGraphicsView
{
public:
    RoomView(QWidget *parent = Q_NULLPTR);
    RoomView(RoomScene *scene, QWidget *parent = Q_NULLPTR);

    void loadRoom(const QWeakPointer<Room> &room);

    RoomScene *scene() const;

private:
    RoomScene *m_scene;
};

#endif // ROOMVIEW_H
