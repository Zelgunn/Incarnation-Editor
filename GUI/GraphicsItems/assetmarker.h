#ifndef ASSETMARKER_H
#define ASSETMARKER_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QAction>
#include <QMenu>

#include "Projects/asset.h"
#include "Projects/project.h"
#include "User/Actions/assettransformaction.h"
#include "rotationhandle.h"
#include "GUI/Windows/asseteditiondialog.h"

class AssetMarker : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    AssetMarker(QWeakPointer<Asset> asset, QGraphicsItem *parent = Q_NULLPTR);

    QWeakPointer<Asset> asset() const;

    QPointF center() const;
    void setCenter(const QPointF &center);

    float sceneScale() const;

    bool fakeSelection() const;
    void setFakeSelection(bool fakeSelection);

    void showContextMenu(const QPoint &pos);

    void updateFromAsset();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

protected slots:
    void showEditionPanel();

private:
    QWeakPointer<Asset> m_asset;
    QPointF m_onMousePressPosition;
    bool m_fakeSelection = false;
};

#endif // ASSETMARKER_H
