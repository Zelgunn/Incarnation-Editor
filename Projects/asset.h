#ifndef ASSET_H
#define ASSET_H

#include <QVariant>
#include <QDomElement>
#include <QDomDocument>
#include <QUrl>
#include <QSize>

#include "Projects/trigger.h"

#include <QDebug>

enum AssetClass
{
    None
};

class Asset
{
public:
    Asset(const QDomElement &elem);
    void toXml(QDomDocument* dom, QDomElement* assetElement) const;

    QString name() const;
    void setName(const QString &name);

    AssetClass assetClass() const;
    void setAssetClass(const AssetClass &assetClass);

    QString iconPath() const;
    void setIconPath(const QString &iconPath);

    //QSizeF size() const;
    void setSize(const QSizeF &size);

    QPointF position() const;
    void setPosition(const QPointF &position);
    void moveBy(qreal x, qreal y);
    void moveBy(const QPointF &delta);

    int getId() const;

    QSizeF scaledSize() const;
    QPointF getScale() const;
    void setScale(const QPointF &scale);

    qreal getRotation() const;
    void setRotation(const qreal &rotation);

    QList<QVariant> getParameters() const;
    void setParameters(const QList<QVariant> &parameters);

    QList<QString> getParametersNames() const;
    void setParametersNames(const QList<QString> &parametersNames);

    float getZPosition() const;
    void setZPosition(float zPosition);

    float getZSize() const;
    void setZSize(float zSize);

    float getZScale() const;
    void setZScale(float zScale);

    void copy(const Asset &other);

protected:
    static int s_nextId;
    int m_id;

    AssetClass m_assetClass;
    QString m_name;
    QString m_hash;
    QString m_iconPath;

    QPointF m_position;
    float m_zPosition = 0;

    QSizeF m_size;
    float m_zSize = 1;

    QPointF m_scale;
    float m_zScale = 1;

    qreal m_rotation = 0;

    QList<QVariant> m_parameters;
    QList<QString> m_parametersNames;

    QList<Trigger> m_triggers;
};

#endif // ASSET_H
