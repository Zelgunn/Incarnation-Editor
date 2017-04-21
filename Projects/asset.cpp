#include "asset.h"

int Asset::s_nextId = 0;

Asset::Asset(const QDomElement &elem)
{
    m_id = s_nextId++;

    QDomNode node = elem.firstChild();
    QDomElement nodeElem;

    while(!node.isNull())
    {
        nodeElem = node.toElement();
        if(!nodeElem.isNull())
        {
            m_parametersNames.append(nodeElem.tagName());
            int parameterType = nodeElem.attribute("type").toInt();
            QVariant parameter = nodeElem.attribute("value");
            parameter.convert(parameterType);
            m_parameters.append(parameter);
        }

        node = node.nextSibling();
    }

    m_name = elem.attribute("name", "No name");
    m_assetClass = (AssetClass)elem.attribute("class", "0").toInt();
    m_iconPath = elem.attribute("icon_url", "No icon URL");
    m_size.setWidth(elem.attribute("width", "0").toFloat());
    m_size.setHeight(elem.attribute("height", "0").toFloat());
    m_position.setX(elem.attribute("posx", "0").toFloat());
    m_position.setY(elem.attribute("posy", "0").toFloat());
}

void Asset::toXml(QDomDocument *dom, QDomElement *assetElement) const
{
    assetElement->setAttribute("class", (int)m_assetClass);
    assetElement->setAttribute("name", m_name);
    assetElement->setAttribute("icon_url", m_iconPath);
    assetElement->setAttribute("width", m_size.width());
    assetElement->setAttribute("height", m_size.height());
    assetElement->setAttribute("posx", m_position.x());
    assetElement->setAttribute("posy", m_position.y());

    for(int i = 0; i < m_parameters.length(); i++)
    {
        QDomElement elem = dom->createElement(m_parametersNames[i]);
        elem.setAttribute("type", m_parameters[i].type());
        elem.setAttribute("value", m_parameters[i].toString());
        assetElement->appendChild(elem);
    }
}

QString Asset::name() const
{
    return m_name;
}

void Asset::setName(const QString &name)
{
    m_name = name;
}

AssetClass Asset::assetClass() const
{
    return m_assetClass;
}

void Asset::setAssetClass(const AssetClass &assetClass)
{
    m_assetClass = assetClass;
}

QString Asset::iconPath() const
{
    return m_iconPath;
}

void Asset::setIconPath(const QString &iconPath)
{
    m_iconPath = iconPath;
}

QSizeF Asset::size() const
{
    return m_size;
}

void Asset::setSize(const QSizeF &size)
{
    m_size = size;
}

QPointF Asset::position() const
{
    return m_position;
}

void Asset::setPosition(const QPointF &position)
{
    m_position = position;
}

void Asset::moveBy(qreal x, qreal y)
{
    m_position += QPointF(x, y);
}

void Asset::moveBy(const QPointF &delta)
{
    m_position += delta;
}

int Asset::getId() const
{
    return m_id;
}
