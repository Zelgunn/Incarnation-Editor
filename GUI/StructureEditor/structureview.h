#ifndef STRUCTUREVIEW_H
#define STRUCTUREVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "structurescene.h"
#include "Projects/project.h"

#include <QDebug>

class StructureView : public QGraphicsView
{
    Q_OBJECT
public:
    StructureView(QWidget *parent = Q_NULLPTR);
    StructureView(StructureScene *scene, QWidget *parent = Q_NULLPTR);

    void setUpProject(Project *project = Q_NULLPTR);
    void unloadProject();

    void update();
    void manualUpdate();

    StructureScene *scene() const;

    QPointF cursorPosition() const;

protected:
    void init();
    void mouseMoveEvent(QMouseEvent *event);

private:
    StructureScene *m_scene;
    QPointF m_sceneCursorPosition;
};

#endif // STRUCTUREVIEW_H
