#include "handle.h"

Handle::Handle(const QPixmap &pixmap, const QPixmap &shadowPixmap, HandleAnchor anchor, QGraphicsItem *parent):
    QGraphicsPixmapItem(pixmap, parent)
{
    m_anchor = anchor;
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    m_shadowPixmap = shadowPixmap;

    rotatePixmaps();
    m_size = pixmap.size();
}

void Handle::setLockX(bool lock)
{
    m_lockX = lock;
}

void Handle::setLockY(bool lock)
{
    m_lockY = lock;
}

void Handle::setTwinHandle(Handle *handle)
{
    m_twin = handle;
}

Handle *Handle::getTwinHandle() const
{
    return m_twin;
}

bool Handle::hasTwin() const
{
    return (m_twin != Q_NULLPTR);
}

void Handle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(hasTwin() && m_twin->isMoving())
    {
        QPointF delta = m_onMousePressPosition - center();
        painter->drawPixmap(delta, m_shadowPixmap);
    }

    if(m_moving)
    {
        QPointF delta = m_onMousePressPosition - center();
        painter->drawPixmap(delta, m_shadowPixmap);

        if(hasTwin())
        {
            m_twin->setCenter(-center());
        }
    }

    QGraphicsPixmapItem::paint(painter, option, widget);
}

QPointF Handle::center() const
{
    return pos() + transformOriginPoint();
}

void Handle::setCenter(const QPointF &point)
{
    setPos(point - transformOriginPoint());
}

void Handle::setCenter(qreal x, qreal y)
{
    setPos(QPointF(x,y) - transformOriginPoint());
}

QSizeF Handle::size() const
{
    return m_size;
}

bool Handle::isMoving() const
{
    return m_moving;
}

QPointF Handle::getShadowPosition() const
{
    if(m_moving)
    {
        return m_onMousePressPosition - center();
    }

    return pos();
}

QVariant Handle::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    QVariant correctedValue = value;

    if(change == ItemPositionChange)
    {
        float x = m_lockX ? pos().x() : value.toPointF().x();
        float y = m_lockY ? pos().y() : value.toPointF().y();
        switch (m_anchor)
        {
        case Right:
            x = (x - m_size.width() / 2) > 0 ? x : (m_size.width() / 2);
            break;
        case Bottom:
            y = (y - m_size.height() / 2) > 0 ? y : (m_size.height() / 2);
            break;
        case Left:
            x = (x + m_size.width() * 3 / 2) < 0 ? x : - (m_size.width() * 3 / 2);
            break;
        case Top:
            y = (y + m_size.height()* 3 / 2) < 0 ? y : - (m_size.height() * 3 / 2);
            break;
        }
        correctedValue = QVariant(QPointF(x, y));
    }

    return QGraphicsPixmapItem::itemChange(change, correctedValue);
}

void Handle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_onMousePressPosition = center();
    if(m_twin != Q_NULLPTR)
    {
        m_twin->m_onMousePressPosition = m_twin->center();
    }
    m_moving = true;

    QGraphicsPixmapItem::mousePressEvent(event);
}

void Handle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_moving = false;

    QGraphicsPixmapItem::mouseReleaseEvent(event);

    if(m_onMousePressPosition != center())
    {
        UserAction::addAction(new RoomHandleTransformAction(this, center() - m_onMousePressPosition));

        emit handleMoved();
    }
}

void Handle::rotatePixmaps()
{
    qreal angle = m_anchor * 90;

    QTransform pixmapRotationTransform;
    pixmapRotationTransform.rotate(angle);

    setPixmap(pixmap().transformed(pixmapRotationTransform));
    m_shadowPixmap = m_shadowPixmap.transformed(pixmapRotationTransform);
}
