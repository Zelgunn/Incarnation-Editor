#ifndef ASSETTRANSFORMACTION_H
#define ASSETTRANSFORMACTION_H

#include "User/useraction.h"
#include "Projects/project.h"

class AssetTransformAction : public UserAction
{
public:
    AssetTransformAction(int assetId, QPointF delta);
    void revert();
    void restore();

private:
    int m_assetId;
    QPointF m_delta;
};

#endif // ASSETTRANSFORMACTION_H
