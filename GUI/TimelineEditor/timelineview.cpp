#include "timelineview.h"

TimelineView::TimelineView(QWidget *parent)
    : QGraphicsView(parent)
{
    m_scene = new TimelineScene;
    init();
}

TimelineView::TimelineView(TimelineScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
{
    m_scene = scene;
    init();
}

TimelineScene *TimelineView::scene() const
{
    return m_scene;
}

void TimelineView::setScene(TimelineScene *scene)
{
    m_scene = scene;
}

void TimelineView::manualUpdate()
{
    m_scene->manualUpdate();
}

void TimelineView::init()
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //setViewportUpdateMode(NoViewportUpdate);
    QGraphicsView::setScene(m_scene);
}
