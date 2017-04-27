#ifndef ROOMSCENE_H
#define ROOMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QFile>


#include "Projects/asset.h"
#include "Projects/project.h"
#include "GUI/GraphicsItems/assetmarker.h"
#include "Projects/room.h"
#include "GUI/GraphicsItems/roommarker.h"
#include "GUI/GraphicsItems/rotationhandle.h"

#include <QDebug>

class RoomScene : public QGraphicsScene
{
public:
    RoomScene(QObject *parent = Q_NULLPTR);
    RoomScene(const QRectF &sceneRect, QObject *parent = Q_NULLPTR);
    RoomScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = Q_NULLPTR);

    void loadRoom(const QWeakPointer<Room> &room, const QPixmap &roomRender);
    void unloadRoom();

    AssetMarker * addAssetMarker(const QWeakPointer<Asset> &asset);
    void removeAssetMarker(AssetMarker *assetMarker);
    void updateMarkers();

    QWeakPointer<Room> room() const;

    qreal scale() const;
    void setScale(const qreal &scale);

    QGraphicsItem *getSelectedItem() const;

    void manualUpdate();

protected:
    void init();
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    bool checkDragEvent(QGraphicsSceneDragDropEvent *event);

private:
    QList<AssetMarker *> m_assetMarkers;
    QWeakPointer<Room> m_room;
    QGraphicsRectItem *m_scaler;
    QGraphicsPixmapItem *m_roomRenderItem;
    qreal m_scale = 1;
    RotationHandle *m_rotationHandle;
};

#endif // ROOMSCENE_H
