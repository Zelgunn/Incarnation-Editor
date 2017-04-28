#include "trigger.h"

Trigger::Trigger(const QDomElement &triggerElem)
{
    m_id = triggerElem.attribute("id");
}

void Trigger::toXML(QDomElement *triggerElem)
{

}

QString Trigger::id() const
{
    return m_id;
}

void Trigger::setId(const QString &id)
{
    m_id = id;
}
