#include "assettransformaction.h"

AssetTransformAction::AssetTransformAction(int assetId, QPointF delta)
{
    m_assetId = assetId;
    m_delta = delta;
    m_rotationDelta = 0;
}

AssetTransformAction::AssetTransformAction(int assetId, qreal rotationDelta)
{
    m_assetId = assetId;
    m_delta = QPointF(0,0);
    m_rotationDelta = rotationDelta;
}

void AssetTransformAction::revert()
{
    QWeakPointer<Asset> asset = Project::activeProject()->getAssetWithID(m_assetId);
    asset.data()->moveBy(-m_delta);
    asset.data()->setRotation(asset.data()->getRotation() - m_rotationDelta);
}

void AssetTransformAction::restore()
{
    QWeakPointer<Asset> asset = Project::activeProject()->getAssetWithID(m_assetId);
    asset.data()->moveBy(m_delta);
    asset.data()->setRotation(asset.data()->getRotation() + m_rotationDelta);
}
