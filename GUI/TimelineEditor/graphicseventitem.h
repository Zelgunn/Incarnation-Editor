#ifndef GRAPHICSEVENTITEM_H
#define GRAPHICSEVENTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "Projects/event.h"

#include <QDebug>

class GraphicsEventItem : public QObject, public QGraphicsItem
{
public:
    GraphicsEventItem(const QWeakPointer<Event> &event, QGraphicsItem *parent = Q_NULLPTR);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QWeakPointer<Event> event() const;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QWeakPointer<Event> m_event;
    bool m_mousePressed = false;
};

#endif // GRAPHICSEVENTITEM_H
