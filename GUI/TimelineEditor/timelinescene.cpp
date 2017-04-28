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
    GraphicsEventItem *eventItem = new GraphicsEventItem(event);
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

void TimelineScene::init()
{
    addRect(0, 0, 1000, 20);
}
