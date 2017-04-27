#include "structureview.h"

StructureView::StructureView(QWidget *parent):
    QGraphicsView(parent)
{
    m_scene = new StructureScene;
    init();
}

StructureView::StructureView(StructureScene *scene, QWidget *parent):
    QGraphicsView(scene, parent)
{
    m_scene = scene;
    init();
}

void StructureView::setUpProject(Project *project)
{
    if(project == Q_NULLPTR)
    {
        project = Project::activeProject();
    }

    m_scene->setUpProject(project);
}

void StructureView::unloadProject()
{
    m_scene->unloadProject();
}

void StructureView::update()
{
    qDebug() << "Block update";
}

void StructureView::manualUpdate()
{
    m_scene->update();
}

StructureScene *StructureView::scene() const
{
    return m_scene;
}

QPointF StructureView::cursorPosition() const
{
    return m_sceneCursorPosition;
}

void StructureView::init()
{
    setScene(m_scene);
    setViewportUpdateMode(NoViewportUpdate);
    setMouseTracking(true);
}

void StructureView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    m_sceneCursorPosition = mapToScene(event->pos());
}
