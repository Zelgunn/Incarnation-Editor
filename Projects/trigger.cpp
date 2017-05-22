#include "trigger.h"

Trigger::Trigger(const QDomElement &triggerElem)
{
    m_id = triggerElem.attribute("id").toInt();
    m_action = triggerElem.attribute("action");
    m_category = triggerElem.attribute("category");
}

void Trigger::toXML(QDomElement *triggerElem) const
{
    triggerElem->setAttribute("id", m_id);
    triggerElem->setAttribute("action", m_action);
    triggerElem->setAttribute("category", m_category);
}

int Trigger::id() const
{
    return m_id;
}

void Trigger::setId(int id)
{
    m_id = id;
}

QString Trigger::action() const
{
    return m_action;
}

void Trigger::setAction(const QString &action)
{
    m_action = action;
}

QString Trigger::category() const
{
    return m_category;
}

void Trigger::setCategory(const QString &category)
{
    m_category = category;
}
