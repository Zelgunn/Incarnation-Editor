#include "room.h"

int Room::s_nextId = 0;

Room::Room(const QString &name, const QSizeF &size, qreal position)
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
    m_size = QSizeF(elem.attribute("sizex").toFloat(), elem.attribute("sizey").toFloat());
    m_zSize = elem.attribute("sizez", "3").toFloat();
    m_position = elem.attribute("posx").toFloat();
    m_hash = elem.attribute("hash", "Default room");

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

            if(nodeElem.tagName() == "Pit")
            {
                Q_ASSERT_X(m_pit == Q_NULLPTR,"Room constructor : XML", "Multiple pits where found in a single room");
                m_pit = new Pit(nodeElem);
            }
        }

        node = node.nextSibling();
    }
}

Room::~Room()
{
    if(hasPit())
    {
        delete m_pit;
    }
    qDebug() << "room" << m_name << "with id" << m_id << "has been deleted";
}

void Room::toXml(QDomDocument *dom, QDomElement *roomElement) const
{
    roomElement->setAttribute("name", m_name);
    roomElement->setAttribute("hash", m_hash);

    roomElement->setAttribute("posx", m_position);

    roomElement->setAttribute("sizex", m_size.width());
    roomElement->setAttribute("sizey", m_size.height());
    roomElement->setAttribute("sizez", m_zSize);

    for(int i = 0; i < m_assets.length(); i++)
    {
        QDomElement elem = dom->createElement("Asset");
        m_assets[i]->toXml(dom, &elem);
        roomElement->appendChild(elem);
    }

    if(hasPit())
    {
        QDomElement elem = dom->createElement("Pit");
        m_pit->toXML(&elem);
        roomElement->appendChild(elem);
    }
}

float Room::getPosition() const
{
    return m_position;
}

void Room::setPosition(const float &position)
{
    m_position = position;
}

void Room::moveBy(qreal delta)
{
    m_position += delta;
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

bool Room::hasPit() const
{
    return m_pit != Q_NULLPTR;
}

Pit *Room::pit() const
{
    return m_pit;
}

QSizeF Room::pitDim() const
{
    return m_pit->dimensions();
}

void Room::removePit()
{
    m_pit = Q_NULLPTR;
}

void Room::setPitDim(const QSizeF &dimensions)
{
    if(m_pit == Q_NULLPTR)
    {
        m_pit = new Pit(dimensions);
    }
    else
    {
        m_pit->setDimensions(dimensions);
    }
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

QWeakPointer<Asset> Room::addAsset(const Asset &baseAsset)
{
    QSharedPointer<Asset> copy = QSharedPointer<Asset>(new Asset(baseAsset));
    m_assets.append(copy);
    return copy;
}
