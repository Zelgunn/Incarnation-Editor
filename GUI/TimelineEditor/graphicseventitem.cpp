#include "graphicseventitem.h"

GraphicsEventItem::GraphicsEventItem(const QWeakPointer<Event> &event, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    m_event = event;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
}

QRectF GraphicsEventItem::boundingRect() const
{
    qreal left = m_event.data()->start();
    qreal width = m_event.data()->duration();
    if(width < 0) width = 15;
    return QRectF(left, 0, width, 20);
}

void GraphicsEventItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(m_event.data()->color());
    painter->drawRect(boundingRect());
}

QWeakPointer<Event> GraphicsEventItem::event() const
{
    return m_event;
}

void GraphicsEventItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    m_mousePressed = true;
}

void GraphicsEventItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    m_mousePressed = false;
}

QVariant GraphicsEventItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange)
    {
        if(m_mousePressed)
        {
            QPointF position = value.toPointF();
            position.setY(pos().y());

            return QGraphicsItem::itemChange(change, QVariant(position));
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
