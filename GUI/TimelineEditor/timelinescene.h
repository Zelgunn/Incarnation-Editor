#ifndef TIMELINESCENE_H
#define TIMELINESCENE_H

#include <QGraphicsScene>

#include "Projects/event.h"
#include "Projects/project.h"
#include "graphicseventitem.h"

class TimelineScene : public QGraphicsScene
{
public:
    TimelineScene(QObject *parent = Q_NULLPTR);
    TimelineScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);
    TimelineScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);

    void addEvent(const QWeakPointer<Event> &event);

    void manualUpdate();
    void checkForObsoleteEvents();
    void checkForNewEvents();

protected:
    void init();

private:
    QList<GraphicsEventItem *> m_eventItems;
};

#endif // TIMELINESCENE_H
