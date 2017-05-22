#include "assetmarker.h"

AssetMarker::AssetMarker(QWeakPointer<Asset> asset, QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent)
{
    m_asset = asset;
    updateFromAsset();

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

    if(isSelected() || m_fakeSelection)
    {
        qreal width = qMax(boundingRect().width(), boundingRect().height()) * 1.414 / 2;

        QPen pen(Qt::green);
        pen.setWidth(3);
        painter->setPen(pen);
        painter->drawEllipse(boundingRect().center(), width, width);
    }
}

void AssetMarker::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mousePressEvent(event);

    switch (event->button())
    {
    case Qt::LeftButton:
        m_onMousePressPosition = center();
        break;
    case Qt::RightButton:

        break;
    default:
        break;
    }
}

void AssetMarker::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsPixmapItem::mouseReleaseEvent(event);

    switch (event->button())
    {
    case Qt::LeftButton:
        updateAssetPos();
        break;
    case Qt::RightButton:
        showContextMenu(event->screenPos());
        break;
    default:
        break;
    }
}

QVariant AssetMarker::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    qreal snapSize = 0.1;
    QVariant correctedValue;
    if(change == ItemPositionChange)
    {
        QPointF snappedPosition = value.toPointF();
        snappedPosition = (snappedPosition / snapSize).toPoint();
        snappedPosition *= snapSize;
        correctedValue = QVariant(snappedPosition);
    }
    else
    {
        correctedValue = value;

    }

    return QGraphicsPixmapItem::itemChange(change, correctedValue);
}

void AssetMarker::showEditionPanel()
{
    AssetEditionDialog *assetEditionDialog = new AssetEditionDialog(m_asset);
    int dialogResult = assetEditionDialog->exec();
    qDebug() << dialogResult << (dialogResult == QDialog::Accepted);
    if(dialogResult == QDialog::Accepted)
    {
        Asset dialogAsset = assetEditionDialog->getAssetValues();
        m_asset.data()->copy(dialogAsset);
        updateFromAsset();
    }
}

bool AssetMarker::fakeSelection() const
{
    return m_fakeSelection;
}

void AssetMarker::setFakeSelection(bool fakeSelection)
{
    if(!fakeSelection && m_fakeSelection)
    {

    }

    m_fakeSelection = fakeSelection;
}

void AssetMarker::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(QObject::tr("Context menu"));

    QAction *editAction = new QAction(QObject::tr("Edit asset..."));
    //connect(editAction, &QAction::triggered, this, &AssetMarker::showEditionPanel);
    contextMenu.addAction(editAction);

    QAction *result = contextMenu.exec(pos);
    if(result == editAction)
    {
        showEditionPanel();
    }

    delete editAction;
}

void AssetMarker::updateFromAsset()
{
    AssetModel assetModel = Project::modelOf(m_asset);
    QPixmap markerPixmap(assetModel.iconPath());

    qreal compensator = 1000;

    QSizeF size = m_asset.data()->scaledSize() * compensator;
    markerPixmap = markerPixmap.scaled(size.toSize());
    setPixmap(markerPixmap);

    setTransformOriginPoint(size.width() / 2, size.height() / 2);
    setScale(1 / compensator);
    setCenter(m_asset.data()->position());
    setRotation(m_asset.data()->getRotation());

    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void AssetMarker::updateAssetPos()
{
    QPointF delta = center() - m_asset.data()->position();
    m_asset.data()->setPosition(center());

    UserAction::addAction(new AssetTransformAction(m_asset.data()->getId(), delta));
}

void AssetMarker::updateAssetRotation()
{
    if(rotation() == m_asset.data()->getRotation())
    {
        return;
    }

    qreal rotationDelta = rotation() - m_asset.data()->getRotation();
    m_asset.data()->setRotation(rotation());
    UserAction::addAction(new AssetTransformAction(m_asset.data()->getId(), rotationDelta));
}
