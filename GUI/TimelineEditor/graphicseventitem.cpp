#include "graphicseventitem.h"

GraphicsEventItem::GraphicsEventItem(const QWeakPointer<Event> &event, const qreal maxWidth, QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    m_event = event;
    m_maxWidth = maxWidth;

    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
}

QRectF GraphicsEventItem::boundingRect() const
{
    return QRect(0, 0, m_maxWidth, 20);
}

void GraphicsEventItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::black);
    painter->setBrush(m_event.data()->color());
    QRectF tmp = displayRect();

    if(m_event.data()->isPunctual())
    {
        QPointF points[4];
        points[0] = QPointF(tmp.width() / 2, 0) + tmp.topLeft();
        points[1] = QPointF(tmp.width(), tmp.height() / 2) + tmp.topLeft();
        points[2] = QPointF(tmp.width() / 2, tmp.height()) + tmp.topLeft();
        points[3] = QPointF(0, tmp.height() / 2) + tmp.topLeft();
        painter->drawPolygon(points, 4);
    }
    else
    {
        if(m_event.data()->duration() < 20)
        {
            int delta = 10 - m_event.data()->duration() / 2;
            QRectF shadow = QRectF(m_event.data()->start() - delta, 0, MIN_WIDTH, 20);

            QColor tmpColor = painter->brush().color();
            QColor shadowColor = tmpColor;
            shadowColor.setAlpha(shadowColor.alpha() / 4);
            painter->setBrush(shadowColor);

            QPen pen = painter->pen();
            painter->setPen(QColor(0, 0, 0, shadowColor.alpha()));

            painter->drawRect(tmp);

            painter->setBrush(tmpColor);
            painter->setPen(pen);
        }

        painter->drawRect(timeRect());
    }
}

QWeakPointer<Event> GraphicsEventItem::event() const
{
    return m_event;
}

QRectF GraphicsEventItem::displayRect() const
{
    qreal left = m_event.data()->start();
    qreal width = m_event.data()->duration();
    if(width < MIN_WIDTH)
    {
        left -= (MIN_WIDTH - width) / 2;
        width = MIN_WIDTH;
    }
    return QRectF(left, 0, width, 20);
}

QRectF GraphicsEventItem::timeRect() const
{
    qreal left = m_event.data()->start();
    qreal width = m_event.data()->duration();
    return QRectF(left, 0, width, 20);
}

bool GraphicsEventItem::positionIsOnEdges(const QPointF &position) const
{
    return positionIsOnRightEdge(position) || positionIsOnLeftEdge(position);
}

bool GraphicsEventItem::positionIsOnRightEdge(const QPointF &position) const
{
    bool result = false;
    if(m_event.data()->isPunctual()) return false;
    if(m_event.data()->duration() < MIN_WIDTH)
    {
        qreal centerX = m_event.data()->start() + m_event.data()->duration() / 2;
        result = (position.x() >= (centerX + MIN_WIDTH / 2 - SELECT_WIDTH)) && (position.x() <= (centerX + MIN_WIDTH / 2 + SELECT_WIDTH));
    }
    else
    {
        result = abs(position.x() - m_event.data()->start() - m_event.data()->duration()) < SELECT_WIDTH;
    }

    return result;
}

bool GraphicsEventItem::positionIsOnLeftEdge(const QPointF &position) const
{
    bool result = false;
    if(m_event.data()->isPunctual()) return false;
    if(m_event.data()->duration() < MIN_WIDTH)
    {
        qreal centerX = m_event.data()->start() + m_event.data()->duration() / 2;
        result = (position.x() <= (centerX - MIN_WIDTH / 2 + SELECT_WIDTH)) && (position.x() >= (centerX - MIN_WIDTH / 2 - SELECT_WIDTH));
    }
    else
    {
        result = abs(position.x() - m_event.data()->start()) < SELECT_WIDTH;
    }

    return result;
}

void GraphicsEventItem::showEditionPanel()
{
    EventDialog editEventDialog;
    int dialogAnswer = editEventDialog.exec(m_event);

    if(dialogAnswer == QDialog::Rejected)
    {
        return;
    }

    m_event.data()->setName(editEventDialog.eventName());
    m_event.data()->setStart(editEventDialog.start());
    m_event.data()->setDuration(editEventDialog.duration());
    m_event.data()->setPeriod(editEventDialog.period());
    m_event.data()->setColor(editEventDialog.color());
}

void GraphicsEventItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);

    switch (event->button())
    {
    case Qt::LeftButton:
        onMouseLeftPress(event);
        break;
    case Qt::RightButton:
        onMouseRightPress(event);
        break;
    }
}

void GraphicsEventItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    switch (event->button())
    {
    case Qt::LeftButton:
        onMouseLeftRelease(event);
        break;
    case Qt::RightButton:
        onMouseRightRelease(event);
        break;
    }
}

void GraphicsEventItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);

    if(positionIsOnEdges(event->pos()))
    {
        QCursor tmpCursor = cursor();
        tmpCursor.setShape(Qt::SizeHorCursor);
        setCursor(tmpCursor);
    }
    else
    {
        QCursor tmpCursor = cursor();
        tmpCursor.setShape(Qt::ArrowCursor);
        setCursor(tmpCursor);
    }
}

QVariant GraphicsEventItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if((change == ItemPositionChange) && m_mousePressed)
    {
        qreal x = value.toPointF().x();

        switch (m_eventItemDragType)
        {
        case EventItemDragType::Move:
            if(x < -m_onMousePressedStart)
            {
                x = -m_onMousePressedStart;
            }
            if((x + m_onMousePressedStart + m_onMousePressedDuration) > m_maxWidth)
            {
                x = m_maxWidth - m_onMousePressedStart - m_onMousePressedDuration;
            }
            m_event.data()->setStart(m_onMousePressedStart + x);
            prepareGeometryChange();
            break;
        case EventItemDragType::ResizeLeft:
            if(x < -m_onMousePressedStart)
            {
                x = -m_onMousePressedStart;
            }
            if(x > m_onMousePressedDuration)
            {
                x = m_onMousePressedDuration;
            }
            m_event.data()->setStart(m_onMousePressedStart + x);
            m_event.data()->setDuration(m_onMousePressedDuration - x);
            break;
        case EventItemDragType::ResizeRight:
            if(x < -m_onMousePressedDuration)
            {
                x = -m_onMousePressedDuration;
            }
            if((x + m_onMousePressedStart + m_onMousePressedDuration) > m_maxWidth)
            {
                x = m_maxWidth - m_onMousePressedStart - m_onMousePressedDuration;
            }
            m_event.data()->setDuration(m_onMousePressedDuration + x);
            break;
        case EventItemDragType::None:

            break;
        }

        return QGraphicsItem::itemChange(change, QVariant(pos()));
    }

    return QGraphicsItem::itemChange(change, value);
}

void GraphicsEventItem::onMouseLeftPress(QGraphicsSceneMouseEvent *event)
{
    if(positionIsOnLeftEdge(event->pos()))
    {
        if(positionIsOnRightEdge(event->pos()))
        {
            qreal centerX = m_event.data()->start() + m_event.data()->duration() / 2;
            if(event->pos().x() >= centerX)
            {
                m_eventItemDragType = EventItemDragType::ResizeRight;
            }
            else
            {
                m_eventItemDragType = EventItemDragType::ResizeLeft;
            }
        }
        else
        {
            m_eventItemDragType = EventItemDragType::ResizeLeft;
        }
    }
    else if(positionIsOnRightEdge(event->pos()))
    {
        m_eventItemDragType = EventItemDragType::ResizeRight;
    }
    else if(displayRect().contains(event->pos()))
    {
        m_eventItemDragType = EventItemDragType::Move;
    }
    else
    {
        m_eventItemDragType = EventItemDragType::None;
    }

    m_onMousePressedStart = m_event.data()->start();
    m_onMousePressedDuration = m_event.data()->duration();
    m_mousePressed = true;
}

void GraphicsEventItem::onMouseRightPress(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void GraphicsEventItem::onMouseLeftRelease(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    m_eventItemDragType = EventItemDragType::None;
    m_mousePressed = false;
}

void GraphicsEventItem::onMouseRightRelease(QGraphicsSceneMouseEvent *event)
{
    if(!displayRect().contains(event->pos())) return;
    QMenu contextMenu(QObject::tr("Context menu"));

    QAction *editAction = new QAction(QObject::tr("Edit event..."));
    contextMenu.addAction(editAction);

    QAction *result = contextMenu.exec(event->screenPos());
    if(result == editAction)
    {
        showEditionPanel();
    }

    delete editAction;
}
