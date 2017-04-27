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
    m_hash = elem.attribute("hash");
    m_assetClass = (AssetClass)elem.attribute("class", "0").toInt();
    m_iconPath = elem.attribute("icon_url", "No icon URL");

    m_size.setWidth(elem.attribute("sizex", "1").toFloat());
    m_size.setHeight(elem.attribute("sizey", "1").toFloat());
    m_zSize = elem.attribute("sizez", "1").toFloat();

    m_scale.setX(elem.attribute("scalex", "1").toFloat());
    m_scale.setY(elem.attribute("scaley", "1").toFloat());
    m_zScale = elem.attribute("scalez", "1").toFloat();

    m_position.setX(elem.attribute("posx", "0").toFloat());
    m_position.setY(elem.attribute("posy", "0").toFloat());
    m_zPosition = elem.attribute("posz", "0").toFloat();

    m_rotation = elem.attribute("rotation", "0").toFloat();
}

void Asset::toXml(QDomDocument *dom, QDomElement *assetElement) const
{
    assetElement->setAttribute("class", (int)m_assetClass);
    assetElement->setAttribute("name", m_name);
    assetElement->setAttribute("hash", m_hash);
    assetElement->setAttribute("icon_url", m_iconPath);

    assetElement->setAttribute("posx", m_position.x());
    assetElement->setAttribute("posy", m_position.y());
    assetElement->setAttribute("posz", m_zPosition);

    assetElement->setAttribute("sizex", m_size.width());
    assetElement->setAttribute("sizey", m_size.height());
    assetElement->setAttribute("sizez", m_zSize);

    assetElement->setAttribute("scalex", m_scale.x());
    assetElement->setAttribute("scaley", m_scale.y());
    assetElement->setAttribute("scalez", m_zScale);

    assetElement->setAttribute("rotation", m_rotation);

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

//QSizeF Asset::size() const
//{
//    return m_size;
//}

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

QSizeF Asset::scaledSize() const
{
    return QSizeF(m_size.width() * m_scale.x(), m_size.height() * m_scale.y());
}

QPointF Asset::getScale() const
{
    return m_scale;
}

void Asset::setScale(const QPointF &scale)
{
    m_scale = scale;
}

qreal Asset::getRotation() const
{
    return m_rotation;
}

void Asset::setRotation(const qreal &rotation)
{
    m_rotation = rotation;
}

QList<QVariant> Asset::getParameters() const
{
    return m_parameters;
}

void Asset::setParameters(const QList<QVariant> &parameters)
{
    m_parameters = parameters;
}

QList<QString> Asset::getParametersNames() const
{
    return m_parametersNames;
}

void Asset::setParametersNames(const QList<QString> &parametersNames)
{
    m_parametersNames = parametersNames;
}

float Asset::getZPosition() const
{
    return m_zPosition;
}

void Asset::setZPosition(float zPosition)
{
    m_zPosition = zPosition;
}

float Asset::getZSize() const
{
    return m_zSize;
}

void Asset::setZSize(float zSize)
{
    m_zSize = zSize;
}

float Asset::getZScale() const
{
    return m_zScale;
}

void Asset::setZScale(float zScale)
{
    m_zScale = zScale;
}

void Asset::copy(const Asset &other)
{
    m_id = other.m_id;

    m_assetClass = other.m_assetClass;
    m_name = other.m_name;
    m_hash = other.m_hash;
    m_iconPath = other.m_iconPath;

    m_position = other.m_position;
    m_zPosition = other.m_zPosition;
    m_size = other.m_size;
    m_zSize = other.m_zSize;
    m_scale = other.m_scale;
    m_zScale = other.m_zScale;

    m_rotation = other.m_rotation;
    m_parameters = other.m_parameters;
    m_parametersNames = other.m_parametersNames;
}
