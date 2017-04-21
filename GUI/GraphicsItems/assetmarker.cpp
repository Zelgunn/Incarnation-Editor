#include "assetmarker.h"

AssetMarker::AssetMarker(QWeakPointer<Asset> asset, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    m_asset = asset;

    QPixmap markerPixmap(asset.data()->iconPath());
    QSizeF size = m_asset.data()->size() * 1000;
    markerPixmap = markerPixmap.scaled(size.toSize());
    setPixmap(markerPixmap);

    setTransformOriginPoint(size.width() / 2, size.height() / 2);
    setScale(0.001);
    setCenter(asset.data()->position());

    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
}

QWeakPointer<Asset> AssetMarker::asset() const
{
    return m_asset;
}

QPointF AssetMarker::center() const
{
    return pos() + transformOriginPoint();
}

void AssetMarker::setCenter(const QPointF &center)
{
    setPos(center - transformOriginPoint());
}

float AssetMarker::sceneScale() const
{
    const QGraphicsItem *tmp = this;
    while(tmp->parentItem() != Q_NULLPTR)
    {
        tmp = tmp->parentItem();
    }
    return tmp->scale();
}

void AssetMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);
}

void AssetMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);

    m_onMousePressPosition = center();
}

void AssetMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    m_asset.data()->setPosition(center());

    QPointF delta = center() - m_onMousePressPosition;
    UserAction::addAction(new AssetTransformAction(m_asset.data()->getId(), delta));
}

QVariant AssetMarker::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    // Snapping here !
    return QGraphicsPixmapItem::itemChange(change, value);
}
