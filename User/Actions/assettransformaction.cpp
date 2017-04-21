#include "assettransformaction.h"

AssetTransformAction::AssetTransformAction(int assetId, QPointF delta)
{
    m_assetId = assetId;
    m_delta = delta;
}

void AssetTransformAction::revert()
{
    QWeakPointer<Asset> asset = Project::activeProject()->getAssetWithID(m_assetId);
    asset.data()->moveBy(-m_delta);
}

void AssetTransformAction::restore()
{
    QWeakPointer<Asset> asset = Project::activeProject()->getAssetWithID(m_assetId);
    asset.data()->moveBy(m_delta);
}
