#ifndef ASSETMODEL_H
#define ASSETMODEL_H

#include <QDomElement>
#include <QString>
#include <QSizeF>
#include <QList>

#include "trigger.h"

class AssetModel
{
public:
    AssetModel(const QDomElement &elem);

    QString name() const;
    QString id() const;
    QString iconPath() const;
    QSizeF size() const;
    float zSize() const;

    QList<Trigger> triggers() const;
    QList<QString> parametersNames() const;
    QList<QVariant> parameters() const;

private:
    QString m_id;
    QString m_iconPath;

    QString m_name;
    QSizeF m_size;
    float m_zSize = 1;

    QList<QVariant> m_parameters;
    QList<QString> m_parametersNames;
    QList<Trigger> m_triggers;
};

#endif // ASSETMODEL_H
