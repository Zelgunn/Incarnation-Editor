#ifndef GRAPHICSEVENTITEM_H
#define GRAPHICSEVENTITEM_H

#include <QObject>
#include <QGraphicsItem>

#include "Projects/event.h"

class GraphicsEventItem : public QObject, public QGraphicsItem
{
public:
    GraphicsEventItem(QGraphicsItem *parent = Q_NULLPTR);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QWeakPointer<Event> m_event;
};

#endif // GRAPHICSEVENTITEM_H
