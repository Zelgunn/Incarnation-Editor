#ifndef ASSET_H
#define ASSET_H

#include <QVariant>
#include <QDomElement>
#include <QDomDocument>
#include <QUrl>
#include <QSize>

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

    QSizeF size() const;
    void setSize(const QSizeF &size);

    QPointF position() const;
    void setPosition(const QPointF &position);
    void moveBy(qreal x, qreal y);
    void moveBy(const QPointF &delta);

    int getId() const;

protected:
    static int s_nextId;
    int m_id;

    AssetClass m_assetClass;
    QString m_name;
    QString m_iconPath;
    QSizeF m_size;
    QPointF m_position;
    QString m_hash;

    QList<QVariant> m_parameters;
    QList<QString> m_parametersNames;
};

#endif // ASSET_H
