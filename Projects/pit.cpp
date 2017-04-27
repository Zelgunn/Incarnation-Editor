#include "pit.h"

Pit::Pit()
{

}

Pit::Pit(const QSizeF &dimensions)
    : m_dimensions(dimensions)
{

}

Pit::Pit(const QDomElement &elem)
{
    qreal width = elem.attribute("width", "5").toFloat();
    qreal depth = elem.attribute("depth", "20").toFloat();

    m_dimensions = QSizeF(width, depth);
}

void Pit::toXML(QDomElement *pitElement)
{
    pitElement->setAttribute("width", m_dimensions.width());
    pitElement->setAttribute("depth", m_dimensions.height());
}

QSizeF Pit::dimensions() const
{
    return m_dimensions;
}

void Pit::setDimensions(const QSizeF &dimensions)
{
    m_dimensions = dimensions;
}
