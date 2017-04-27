#ifndef ROOMMARKER_H
#define ROOMMARKER_H

#include <QGraphicsItem>
#include <QGraphicsSceneDragDropEvent>
#include <QPainter>
#include <QApplication>

#include "handle.h"
#include "User/useraction.h"
#include "User/Actions/roomtransformaction.h"
#include "Projects/room.h"
#include "User/userpreferences.h"

#include <QDebug>

class Room;

class RoomMarker : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    RoomMarker(QWeakPointer<Room> room, QGraphicsItem *parent = Q_NULLPTR);
    QPointF handlesCenter() const;
    void manualUpdate();

    void showHandles(bool show);
    void updateHandles();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paintWalls(QPainter *painter);
    void paintShadow(QPainter *painter);
    void paintCenter(QPainter *painter);
    void paintPit(QPainter *painter);
    QRectF boundingRect() const;
    QRectF projectedRect() const;

    QPointF getProjectedPosition() const;
    void setProjectedPosition(const QPointF &position);
    void setProjectedPosition(qreal x, qreal y);

    void setSelected(bool select);
    bool isSelected() const;

    bool isMoving() const;

    QSizeF getViewSize() const;
    void setViewSize(const QSizeF &viewSize);
    QSizeF getSize() const;
    void setSize(const QSizeF &size);

    QWeakPointer<Room> getRoomData() const;

    static bool compareXPos(const RoomMarker *m1, const RoomMarker *m2);

public slots:
    void updateGeometryFromHandles();
    void updateRoomGeometryFromData();

signals:
    void selected(RoomMarker* source);
    void geometryChanged();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    Handle* m_handles[4];
    QSizeF m_viewSize;
    bool m_selected = false;

    QPointF m_onMousePressPosition;
    QPointF m_projectedPosition;
    bool m_moving = false;
    QWeakPointer<Room> m_room;
};

#endif // ROOMMARKER_H
