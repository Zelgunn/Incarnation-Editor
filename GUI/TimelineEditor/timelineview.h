#ifndef TIMELINEVIEW_H
#define TIMELINEVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QMouseEvent>

#include "timelinescene.h"

#include <QDebug>

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
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    TimelineScene *m_scene;
};

#endif // TIMELINEVIEW_H
