#ifndef GRAPHICSEVENTITEM_H
#define GRAPHICSEVENTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QMenu>
#include <QAction>

#include "Projects/event.h"
#include "eventdialog.h"
#include "triggerdialog.h"

#include <QDebug>

#define SELECT_WIDTH 5
#define MIN_WIDTH 20

class GraphicsEventItem : public QObject, public QGraphicsItem
{
public:
    enum EventItemDragType
    {
        Move,
        ResizeLeft,
        ResizeRight,
        None
    };

    GraphicsEventItem(const QWeakPointer<Event> &event, const qreal maxWidth, QGraphicsItem *parent = Q_NULLPTR);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QWeakPointer<Event> event() const;
    QRectF displayRect() const;
    QRectF timeRect() const;

    bool positionIsOnEdges(const QPointF &position) const;
    bool positionIsOnRightEdge(const QPointF &position) const;
    bool positionIsOnLeftEdge(const QPointF &position) const;

    void showEventEditionPanel();
    void showAddTriggerPanel();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void onMouseLeftPress(QGraphicsSceneMouseEvent *event);
    void onMouseRightPress(QGraphicsSceneMouseEvent *event);
    void onMouseLeftRelease(QGraphicsSceneMouseEvent *event);
    void onMouseRightRelease(QGraphicsSceneMouseEvent *event);

private:
    QWeakPointer<Event> m_event;
    bool m_mousePressed = false;
    EventItemDragType m_eventItemDragType = EventItemDragType::None;
    qreal m_onMousePressedStart;
    qreal m_onMousePressedDuration;
    qreal m_maxWidth = 2000;
};

#endif // GRAPHICSEVENTITEM_H
