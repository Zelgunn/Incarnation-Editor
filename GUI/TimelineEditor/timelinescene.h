#ifndef TIMELINESCENE_H
#define TIMELINESCENE_H

#include <QtGlobal>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "Projects/event.h"
#include "Projects/project.h"
#include "graphicseventitem.h"
#include "timecursor.h"

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

    void updateItemsSize(const QSizeF &sceneSize);

    int posToMin() const;
    int posToSecsTotal() const;
    int posToSecsRemainder() const;

protected:
    void init();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<GraphicsEventItem *> m_eventItems;
    QGraphicsRectItem *m_header;
    TimeCursor *m_timeCursor;
    QPointF m_mousePosition;
};

#endif // TIMELINESCENE_H
