#include "room.h"

int Room::s_nextId = 0;

Room::Room(const QString &name, const QSizeF &size, const QPointF &position)
{
    m_id = s_nextId++;
    m_name = name;
    m_position = position;
    m_size = size;
}

Room::Room(const QDomElement &elem)
{
    m_id = s_nextId++;
    m_name = elem.attribute("name");
    m_size = QSizeF(elem.attribute("width").toFloat(), elem.attribute("height").toFloat());
    m_position = QPointF(elem.attribute("posx").toFloat(), elem.attribute("posy").toFloat());

    QDomNode node = elem.firstChild();
    QDomElement nodeElem;

    while(!node.isNull())
    {
        nodeElem = node.toElement();
        if(!nodeElem.isNull())
        {
            if(nodeElem.tagName() == "Asset")
            {
                m_assets.append(QSharedPointer<Asset>(new Asset(nodeElem)));
            }
        }

        node = node.nextSibling();
    }
}

Room::~Room()
{
    qDebug() << "room" << m_name << "with id" << m_id << "has been deleted";
}

void Room::toXml(QDomDocument *dom, QDomElement *roomElement) const
{
    roomElement->setAttribute("name", m_name);

    roomElement->setAttribute("posx", m_position.x());
    roomElement->setAttribute("posy", m_position.y());

    roomElement->setAttribute("width", m_size.width());
    roomElement->setAttribute("height", m_size.height());

    for(int i = 0; i < m_assets.length(); i++)
    {
        QDomElement elem = dom->createElement("Asset");
        m_assets[i]->toXml(dom, &elem);
        roomElement->appendChild(elem);
    }
}

QPointF Room::getPosition() const
{
    return m_position;
}

void Room::setPosition(const QPointF &position)
{
    m_position = position;
}

void Room::moveBy(const QPointF &delta)
{
    m_position += delta;
}

void Room::moveBy(float x, float y)
{
    m_position += QPointF(x, y);
}

QString Room::getName() const
{
    return m_name;
}

void Room::setName(const QString &name)
{
    m_name = name;
}

QSizeF Room::getSize() const
{
    return m_size;
}

void Room::setSize(const QSizeF &size)
{
    m_size = size;
}

int Room::getId() const
{
    return m_id;
}

QList<QWeakPointer<Asset> > Room::assets() const
{
    QList<QWeakPointer<Asset> > tmp;
    foreach (QSharedPointer<Asset> asset, m_assets)
    {
        tmp.append(asset.toWeakRef());
    }
    return tmp;
}

QWeakPointer<Asset> Room::addAsset(const QWeakPointer<Asset> &baseAsset)
{
    QSharedPointer<Asset> copy = QSharedPointer<Asset>(new Asset(*baseAsset.data()));
    m_assets.append(copy);
    return copy;
}
