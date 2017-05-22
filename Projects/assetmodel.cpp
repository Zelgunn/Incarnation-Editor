#include "assetmodel.h"

AssetModel::AssetModel(const QDomElement &elem)
{
    m_id = elem.attribute("id");
    m_iconPath = elem.attribute("icon_url", "No icon URL");

    m_name = elem.attribute("name", "No name");
    m_size.setWidth(elem.attribute("sizex", "1").toFloat());
    m_size.setHeight(elem.attribute("sizey", "1").toFloat());
    m_zSize = elem.attribute("sizez", "1").toFloat();

    QDomNode node = elem.firstChild();
    QDomElement nodeElem;

    while(!node.isNull())
    {
        nodeElem = node.toElement();
        if(!nodeElem.isNull())
        {
            if(nodeElem.tagName() == "Trigger")
            {
                m_triggers.append(Trigger(nodeElem));
            }
            else
            {
                m_parametersNames.append(nodeElem.tagName());
                int parameterType = nodeElem.attribute("type").toInt();
                QVariant parameter = nodeElem.attribute("value");
                parameter.convert(parameterType);
                m_parameters.append(parameter);
            }
        }

        node = node.nextSibling();
    }
}

QString AssetModel::name() const
{
    return m_name;
}

QString AssetModel::id() const
{
    return m_id;
}

QString AssetModel::iconPath() const
{
    return m_iconPath;
}

QSizeF AssetModel::size() const
{
    return m_size;
}

float AssetModel::zSize() const
{
    return m_zSize;
}

QList<Trigger> AssetModel::triggers() const
{
    return m_triggers;
}

QList<QString> AssetModel::parametersNames() const
{
    return m_parametersNames;
}

QList<QVariant> AssetModel::parameters() const
{
    return m_parameters;
}
