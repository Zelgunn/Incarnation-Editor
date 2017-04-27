#ifndef ROOM_H
#define ROOM_H

#include <QDomElement>
#include <QSizeF>
#include <QPointF>

#include "asset.h"
#include "pit.h"

#include <QDebug>

class Room
{
public:
    Room(const QString &name, const QSizeF &size = QSizeF(), qreal position = 0);
    Room(const QDomElement &elem);
    ~Room();

    void toXml(QDomDocument *dom, QDomElement* roomElement) const;

    float getPosition() const;
    void setPosition(const float &position);
    void moveBy(qreal delta);

    QString getName() const;
    void setName(const QString &name);

    QSizeF getSize() const;
    void setSize(const QSizeF &size);

    bool hasPit() const;
    Pit *pit() const;
    QSizeF pitDim() const;
    void removePit();
    void setPitDim(const QSizeF &dimensions);

    int getId() const;

    QList<QWeakPointer<Asset> > assets() const;
    QWeakPointer<Asset> addAsset(const QWeakPointer<Asset> &baseAsset);

private:
    static int s_nextId;
    int m_id;

    QString m_name;
    QString m_hash;

    float m_position;

    QSizeF m_size;
    float m_zSize = 3;

    Pit* m_pit = Q_NULLPTR;

    QList<QSharedPointer<Asset> > m_assets;
};

#endif // ROOM_H
