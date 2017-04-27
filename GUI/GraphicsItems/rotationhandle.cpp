#include "rotationhandle.h"

RotationHandle::RotationHandle(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent)
{
    init();
}

RotationHandle::RotationHandle(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsEllipseItem(rect, parent)
{
    init();
}

RotationHandle::RotationHandle(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    : QGraphicsEllipseItem(x, y, width, height, parent)
{
    init();
}

void RotationHandle::init()
{
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    setZValue(1);

    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::red);
    setPen(pen);
    setBrush(brush);
}

QVariant RotationHandle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if((change == ItemPositionChange) && (m_handledItem != Q_NULLPTR))
    {
        QPointF handledItemCenter = mapToScene(mapFromItem(m_handledItem, m_handledItem->transformOriginPoint()));
        QPointF delta = value.toPointF() - handledItemCenter;
        qreal angle = atan2(delta.y(), delta.x());
        angle = qRound(angle * 180 / 3.1415 / 5) * 5;
        m_handledItem->setRotation(angle);
        angle *= 3.1415 / 180;

        QPointF relativePos(cos(angle) * m_distanceToCenter, sin(angle) * m_distanceToCenter);

        return QGraphicsEllipseItem::itemChange(change, QVariant(handledItemCenter + relativePos));
    }

    return QGraphicsEllipseItem::itemChange(change, value);
}

qreal RotationHandle::distanceToCenter() const
{
    if(m_handledItem == Q_NULLPTR)
    {
        return 0;
    }

    return m_distanceToCenter / m_handledItem->boundingRect().width() * 1000 * 1.414;
}

void RotationHandle::setDistanceToCenter(const qreal &distanceToCenter)
{
    if(m_handledItem == Q_NULLPTR)
    {
        return;
    }

    m_distanceToCenter = distanceToCenter * m_handledItem->boundingRect().width() / 1000 / 1.414;
}

QGraphicsItem *RotationHandle::handledItem() const
{
    return m_handledItem;
}

void RotationHandle::setHandledItem(QGraphicsItem *handledItem)
{
    if(m_handledItem == handledItem)
    {
        return;
    }

    m_handledItem = handledItem;
    updatePos();
}

void RotationHandle::updatePos()
{
    if(m_handledItem == Q_NULLPTR)
    {
        return;
    }

    setFlag(QGraphicsItem::ItemSendsGeometryChanges, false);

    QPointF handledItemCenter = mapToScene(mapFromItem(m_handledItem, m_handledItem->transformOriginPoint()));
    qreal angle = m_handledItem->rotation() / 180 * 3.1415926;
    QPointF relativePos(cos(angle) * m_distanceToCenter, sin(angle) * m_distanceToCenter);

    setPos(handledItemCenter + relativePos);

    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}
