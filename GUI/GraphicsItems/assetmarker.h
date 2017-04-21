#ifndef ASSETMARKER_H
#define ASSETMARKER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

#include "Projects/asset.h"
#include "Projects/project.h"
#include "User/Actions/assettransformaction.h"

class AssetMarker : public QGraphicsPixmapItem
{
public:
    AssetMarker(QWeakPointer<Asset> asset, QGraphicsItem *parent = Q_NULLPTR);

    QWeakPointer<Asset> asset() const;

    QPointF center() const;
    void setCenter(const QPointF &center);

    float sceneScale() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QWeakPointer<Asset> m_asset;
    QPointF m_onMousePressPosition;
};

#endif // ASSETMARKER_H
