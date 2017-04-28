#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QGraphicsView>

#include "timelinescene.h"

class TimelineView : public QGraphicsView
{
public:
    TimelineView(QWidget *parent = Q_NULLPTR);
    TimelineView(TimelineScene *scene, QWidget *parent = Q_NULLPTR);

    TimelineScene *scene() const;
    void setScene(TimelineScene *scene);

    void manualUpdate();

protected:
    void init();

private:
    TimelineScene *m_scene;
};

#endif // TIMELINEVIEW_H
