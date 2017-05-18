#include "timelinescene.h"

TimelineScene::TimelineScene(QObject *parent)
    : QGraphicsScene(parent)
{
    init();
}

TimelineScene::TimelineScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{
    init();
}

TimelineScene::TimelineScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    init();
}

void TimelineScene::addEvent(const QWeakPointer<Event> &event)
{
    GraphicsEventItem *eventItem = new GraphicsEventItem(event, 1800);
    m_eventItems.append(eventItem);
    eventItem->setPos(QPointF(0, m_eventItems.length() * 20));
    addItem(eventItem);
}

void TimelineScene::manualUpdate()
{
    checkForNewEvents();
}

void TimelineScene::checkForObsoleteEvents()
{

}

void TimelineScene::checkForNewEvents()
{
    QList<QWeakPointer<Event>> displayedEvents;
    for(int i = 0; i < m_eventItems.length(); i++)
    {
        displayedEvents.append(m_eventItems[i]->event());
    }

    QList<QWeakPointer<Event>> projectEvents = Project::activeProject()->getEvents();
    for(int i = 0; i < projectEvents.length(); i++)
    {
        if(!displayedEvents.contains(projectEvents[i]))
        {
            addEvent(projectEvents[i]);
        }
    }
}

void TimelineScene::updateItemsSize(const QSizeF &sceneSize)
{
    m_header->setRect(0, 0, sceneSize.width(), 20);
    m_timeCursor->setHeight(sceneSize.height());
}

int TimelineScene::posToMin() const
{
    return posToSecsTotal() / 60;
}

int TimelineScene::posToSecsTotal() const
{
    return m_mousePosition.x();
}

int TimelineScene::posToSecsRemainder() const
{
    return posToSecsTotal() % 60;
}

void TimelineScene::init()
{
    m_header = addRect(0, 0, 100, 20);
    m_timeCursor = new TimeCursor;
    addItem(m_timeCursor);
}

void TimelineScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    m_mousePosition = event->scenePos();

    m_timeCursor->setX(event->scenePos().x());

    int minsRight = posToMin();
    int minsLeft = minsRight / 10;
    minsRight %= 10;

    int secsRight = posToSecsRemainder();
    int secsLeft = secsRight / 10;
    secsRight %= 10;

    m_timeCursor->setTimeText(QString("%1%2:%3%4").arg(minsLeft).arg(minsRight).arg(secsLeft).arg(secsRight));
}
