#ifndef ROOM_H
#define ROOM_H

#include <QDomElement>
#include <QSizeF>
#include <QPointF>

#include "asset.h"

#include <QDebug>

class Room
{
public:
    Room(const QString &name, const QSizeF &size = QSizeF(), const QPointF &position = QPointF());
    Room(const QDomElement &elem);
    ~Room();

    void toXml(QDomDocument *dom, QDomElement* roomElement) const;

    QPointF getPosition() const;
    void setPosition(const QPointF &position);
    void moveBy(const QPointF &delta);
    void moveBy(float x, float y);

    QString getName() const;
    void setName(const QString &name);

    QSizeF getSize() const;
    void setSize(const QSizeF &size);

    int getId() const;

    QList<QWeakPointer<Asset> > assets() const;
    QWeakPointer<Asset> addAsset(const QWeakPointer<Asset> &baseAsset);

private:
    static int s_nextId;
    int m_id;
    QPointF m_position;
    QSizeF m_size;

    QString m_name;

    QList<QSharedPointer<Asset> > m_assets;
};

#endif // ROOM_H
