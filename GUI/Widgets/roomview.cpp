#include "roomview.h"

RoomView::RoomView(QWidget *parent)
    : QGraphicsView(parent)
{
    m_scene = new RoomScene;
    init();
}

RoomView::RoomView(RoomScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    m_scene = scene;
    init();
}

void RoomView::loadRoom(const QWeakPointer<Room> &room, const QPixmap &roomRender)
{
    m_scene->loadRoom(room, roomRender);
    m_scene->setScale(50);
}

RoomScene *RoomView::scene() const
{
    return m_scene;
}

void RoomView::manualUpdate()
{
    m_scene->manualUpdate();
}

void RoomView::init()
{
    setScene(m_scene);
    setAcceptDrops(true);
    m_midButtonViewDragTimer = new QTimer(this);
    connect(m_midButtonViewDragTimer, &QTimer::timeout, this, &RoomView::updateMidButtonViewDrag);
}

void RoomView::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        m_scene->setScale(m_scene->scale() + 5);
    }
    else if(event->delta() < 0)
    {
        if(m_scene->scale() <= 6)
        {
            m_scene->setScale(1);
        }
        else
        {
            m_scene->setScale(m_scene->scale() - 5);
        }
    }
}

void RoomView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(event->button() == Qt::MidButton)
    {
        m_midButtonViewDragSnapPos = event->pos();
        m_mousePosition = event->pos();

        m_midButtonViewDragTimer->start(16);
    }
}

void RoomView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    if(event->button() == Qt::MidButton)
    {
        m_midButtonViewDragTimer->stop();
    }
}

void RoomView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    m_mousePosition = event->pos();
}

void RoomView::updateMidButtonViewDrag()
{
    QPoint deltaToSnap = m_midButtonViewDragSnapPos - m_mousePosition;
    QPointF currentCenter = mapToScene(viewport()->rect().center()) - deltaToSnap / 10;
    centerOn(currentCenter);
}
