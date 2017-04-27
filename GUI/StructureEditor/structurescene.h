#ifndef STRUCTURESCENE_H
#define STRUCTURESCENE_H

#include <QGraphicsScene>

#include "roommarker.h"
#include "Projects/project.h"

class StructureScene : public QGraphicsScene
{
    Q_OBJECT
public:
    StructureScene(QObject *parent = Q_NULLPTR);
    StructureScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);
    StructureScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);

    void setUpProject(Project *project = Q_NULLPTR);
    void addRoomMarker(RoomMarker *marker);
    void removeRoomMarker(RoomMarker *marker);
    void createRoomMarker(QWeakPointer<Room> room, bool appendAtEnd);
    void updateMarkers();
    void unloadProject();

    void update(const QRectF &rect = QRectF());
    void update(qreal x, qreal y, qreal w, qreal h);

    QList<RoomMarker *> roomMarkers() const;

    QPixmap renderSelectedRoom();

signals:
    void cursorPositionChanged(QGraphicsSceneMouseEvent *event);
    void selectionChanged(RoomMarker *roomMarker);
    void sceneGeometryChanged();

protected:
    void updateZValues();
    void updateMarkersProjection();
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

protected slots:
    void roomMarkerSelected(RoomMarker *roomMarker);
    void emitSceneGeometryChanged();

private:
    QList<RoomMarker *> m_roomMarkers;
    RoomMarker *m_selectedRoomMarker;

};

#endif // STRUCTURESCENE_H
