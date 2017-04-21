#include "roomscene.h"

RoomScene::RoomScene(QObject *parent)
    : QGraphicsScene(parent)
{
    m_scaler = addRect(QRectF());
}

RoomScene::RoomScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{
    m_scaler = addRect(QRectF());
}

RoomScene::RoomScene(qreal x, qreal y, qreal width, qreal height, QObject *parent)
    : QGraphicsScene(x, y, width, height, parent)
{
    m_scaler = addRect(QRectF());
}

void RoomScene::loadRoom(const QWeakPointer<Room> &room)
{
    unloadRoom();

    m_room = room;
    QSize roomSize = (room.data()->getSize()).toSize();
    QRect roomRect(- roomSize.width() / 2, - roomSize.height() / 2, roomSize.width(), roomSize.height());
    m_scaler->setRect(roomRect);

    QList<QWeakPointer<Asset> > roomAssets = m_room.data()->assets();
    for(int i = 0; i < roomAssets.length(); i++)
    {
        addAssetMarker(roomAssets[i]);
    }
}

void RoomScene::unloadRoom()
{
    for(int i = 0; i < m_assetMarkers.length(); i++)
    {
        AssetMarker *assetMarker = m_assetMarkers[i];
        removeItem(assetMarker);
        delete assetMarker;
    }

    m_assetMarkers.clear();
}

AssetMarker *RoomScene::addAssetMarker(const QWeakPointer<Asset> &asset)
{
    AssetMarker *assetMarker = new AssetMarker(asset, m_scaler);
    m_assetMarkers.append(assetMarker);

    return assetMarker;
}

void RoomScene::removeAssetMarker(AssetMarker *assetMarker)
{
    removeItem(assetMarker);
    m_assetMarkers.removeAll(assetMarker);
    delete assetMarker;
}

void RoomScene::updateMarkers()
{
    // Remove invalid markers
    QList<QWeakPointer<Asset> > foundAssets;
    for(int i = 0; i < m_assetMarkers.length(); i++)
    {
        if(m_assetMarkers[i]->asset().isNull())
        {
            removeAssetMarker(m_assetMarkers[i]);
            i--;
        }
        else
        {
            foundAssets.append(m_assetMarkers[i]->asset());
        }
    }

    // Add missing markers
    QList<QWeakPointer<Asset> > allAssets = m_room.data()->assets();
    for(int i = 0; i < allAssets.length(); i++)
    {
        if(!foundAssets.contains(allAssets[i]))
        {
            addAssetMarker(allAssets[i]);
        }
    }

    // Update existing markers
    for(int i = 0; i < m_assetMarkers.length(); i++)
    {
        AssetMarker *assetMarker = m_assetMarkers[i];
        QWeakPointer<Asset> asset = assetMarker->asset();

        assetMarker->setCenter(asset.data()->position());
        //assetMarker->setSize(asset.data()->size());
    }
}

void RoomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragEnterEvent(event);
    checkDragEvent(event);
}

void RoomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragMoveEvent(event);
    checkDragEvent(event);
}

void RoomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dropEvent(event);

    if(checkDragEvent(event))
    {
        QString databaseAssetIndexString = event->mimeData()->text();
        databaseAssetIndexString = databaseAssetIndexString.right(databaseAssetIndexString.length() - 13);
        int databaseAssetIndex = databaseAssetIndexString.toInt();
        QWeakPointer<Asset> asset = Project::assetDatabaseAt(databaseAssetIndex);
        asset = m_room.data()->addAsset(asset);
        asset.data()->setPosition(event->scenePos()  / m_scale);
        //AssetMarker *assetMarker = addAssetMarker(asset);
        addAssetMarker(asset);
        //assetMarker->setCenter(event->scenePos() / m_scale);
    }
}

bool RoomScene::checkDragEvent(QGraphicsSceneDragDropEvent *event)
{
    if(!event->mimeData()->hasText())
    {
        return false;
    }

    if(!m_scaler->rect().contains(event->scenePos() / m_scale))
    {
        return false;
    }

    if(!event->mimeData()->text().startsWith("databaseAsset"))
    {
        return false;
    }

    event->acceptProposedAction();
    event->accept();

    return true;
}

qreal RoomScene::scale() const
{
    return m_scale;
}

void RoomScene::setScale(const qreal &scale)
{
    m_scale = scale;
    m_scaler->setScale(scale);
    m_scaler->setPen(QPen(QBrush(Qt::black), 2.5 / m_scale));
}

QWeakPointer<Room> RoomScene::room() const
{
    return m_room;
}
