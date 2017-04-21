#include "roommarker.h"

RoomMarker::RoomMarker(QWeakPointer<Room> room, QGraphicsItem *parent):
    QGraphicsItem(parent)
{
    m_room = room;
    setSize(m_room.data()->getSize()); //OK
    setPos(m_room.data()->getPosition());

    float width = m_viewSize.width();
    float height = m_viewSize.height();

    float handleWidth = 20;
    float handleHeight = 20;

    QPixmap handlePixmap(":/icons/icons/ThickSquare.png");
    handlePixmap = handlePixmap.scaled(handleWidth, handleHeight);
    QPixmap handleShadowPixmap(":/icons/icons/ThickSquare_shadow.png");
    handleShadowPixmap = handleShadowPixmap.scaled(handleWidth, handleHeight);

    float angle;
    for(int i = 0; i < 4; i++)
    {
        Handle *handle = new Handle(handlePixmap, handleShadowPixmap, (HandleAnchor)i, this);

        angle = i * 3.1415926 / 2;
        handle->setTransformOriginPoint(handleWidth / 2, handleHeight / 2);

        handle->setCenter((cos(angle) * width) / 2, (sin(angle) * height) / 2);

        handle->setFlag(ItemIsMovable, true);

        handle->setLockX((i + 1)%2 == 0);
        handle->setLockY(i%2 == 0);

        connect(handle, &Handle::handleMoved, this, &RoomMarker::updateGeometryFromHandles);
        m_handles[i] = handle;
    }

    for(int i = 0; i < 4; i++)
    {
        m_handles[i]->setTwinHandle(m_handles[(i + 2)%4]);
    }

    setFlag(ItemIsMovable, true);
    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QPointF RoomMarker::handlesCenter() const
{
    QPointF center;

    for(int i = 0; i < 4; i++)
    {
        center += m_handles[i]->center();
    }

    return center/ 4;
}

void RoomMarker::manualUpdate()
{
    updateHandles();
}

void RoomMarker::showHandles(bool show)
{
    for(int i = 0; i < 4; i++)
    {
        m_handles[i]->setVisible(show);
    }
}

void RoomMarker::updateHandles()
{
    showHandles(m_selected);
    float angle;

    for(int i = 0; i < 4; i++)
    {
        if(m_handles[i]->isMoving() || (m_handles[i]->hasTwin() && m_handles[i]->getTwinHandle()->isMoving()))
        {
            continue;
        }
        angle = i * 3.1415926 / 2;

        m_handles[i]->setCenter((cos(angle) * m_viewSize.width()) / 2, (sin(angle) * m_viewSize.height()) / 2);
    }
}

void RoomMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QPen basePen;
    basePen.setWidth(5);
    painter->setPen(basePen);

    if(m_moving)
    {
        QPen shadowPen = basePen;
        shadowPen.setColor(Qt::gray);
        painter->setPen(shadowPen);

        painter->drawRect(projectedRect());

        painter->setPen(basePen);
    }

    painter->drawRect(boundingRect());

    if(m_selected)
    {
        QRectF a(-3,-3,6,6);
        painter->setBrush(Qt::green);
        painter->setPen(Qt::blue);
        a.moveCenter(transformOriginPoint());
        painter->drawRect(a);
    }
}

QRectF RoomMarker::boundingRect() const
{
    float x = transformOriginPoint().x() - m_viewSize.width() / 2;
    float y = transformOriginPoint().y() - m_viewSize.height() / 2;

    return QRectF(x, y, m_viewSize.width(), m_viewSize.height());
}

QRectF RoomMarker::projectedRect() const
{
    if(!m_moving)
    {
        return boundingRect();
    }

    QRectF result = boundingRect();
    result.moveCenter(m_projectedPosition - pos());

    return result;
}

QPointF RoomMarker::getProjectedPosition() const
{
    return m_projectedPosition;
}

void RoomMarker::setProjectedPosition(const QPointF &position)
{
    m_projectedPosition = position;
}

void RoomMarker::setProjectedPosition(qreal x, qreal y)
{
    m_projectedPosition = QPointF(x, y);
}

void RoomMarker::setSelected(bool select)
{
    bool changedToSelected = !m_selected && select;
    m_selected = select;

    if(changedToSelected)
    {
        emit selected(this);
    }
}

bool RoomMarker::isSelected() const
{
    return m_selected;
}

bool RoomMarker::isMoving() const
{
    return m_moving;
}

QSizeF RoomMarker::getViewSize() const
{
    return m_viewSize;
}

void RoomMarker::setViewSize(const QSizeF &viewSize)
{
    m_viewSize = viewSize;
}

QSizeF RoomMarker::getSize() const
{
    return m_viewSize / UserPreferences::structureEditorZoomRatio();
}

void RoomMarker::setSize(const QSizeF &size)
{
    m_viewSize = size * UserPreferences::structureEditorZoomRatio();
}

QWeakPointer<Room> RoomMarker::getRoomData() const
{
    return m_room;
}

bool RoomMarker::compareXPos(const RoomMarker *m1, const RoomMarker *m2)
{
    return m1->pos().x() < m2->pos().x();
}

void RoomMarker::updateGeometryFromHandles()
{
    QSize size(m_handles[0]->center().x() - m_handles[2]->center().x(),
            m_handles[1]->center().y() - m_handles[3]->center().y());

    if(size != m_viewSize)
    {
        m_viewSize = size;
        emit geometryChanged();
    }
}

void RoomMarker::updateRoomGeometryFromData()
{
    //m_size = m_room.data()->getSize();
    updateHandles();
}

void RoomMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    m_onMousePressPosition = pos();
    m_moving = true;

    setSelected(true);
}

void RoomMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    m_moving = false;
    if(m_onMousePressPosition != pos())
    {
        UserAction::addAction(new RoomTransformAction(m_room.data()->getId(), pos() - m_onMousePressPosition));
        emit geometryChanged();
    }
}

QVariant RoomMarker::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    QVariant correctedValue = value;

    if(change == ItemPositionChange)
    {
        correctedValue = QVariant(QPointF(value.toPointF().x(), 0));
    }

    return QGraphicsItem::itemChange(change, correctedValue);
}
