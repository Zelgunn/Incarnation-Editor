#ifndef ASSETTRANSFORMACTION_H
#define ASSETTRANSFORMACTION_H

#include "User/useraction.h"
#include "Projects/project.h"

class AssetTransformAction : public UserAction
{
public:
    AssetTransformAction(int assetId, QPointF delta);
    AssetTransformAction(int assetId, qreal rotationDelta);
    void revert();
    void restore();

private:
    int m_assetId;
    QPointF m_delta;
    qreal m_rotationDelta;
};

#endif // ASSETTRANSFORMACTION_H
