#include "trigger.h"

Trigger::Trigger(const QDomElement &triggerElem)
{
    m_id = triggerElem.attribute("id");
    m_usesDuration = triggerElem.attribute("usesDuration") == "true";
}

void Trigger::toXML(QDomElement *triggerElem) const
{
    triggerElem->setAttribute("id", m_id);
    triggerElem->setAttribute("usesDuration", m_usesDuration ? "true" : "false");
}

QString Trigger::id() const
{
    return m_id;
}

void Trigger::setId(const QString &id)
{
    m_id = id;
}
